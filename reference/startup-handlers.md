# Understanding the startup handlers

This note describes the current implementation in `rtos/src/startup.S` and `rtos/src/main.c`.

## How the CPU finds the handlers: the vector table

The vector table contains addresses. Its position in the table gives each entry its meaning; the handler's name alone does not connect it to an exception.

From `startup.S`:

```asm
.section .isr_vector, "a", %progbits

.word _estack          /* 0: initial MSP value, not a handler address */
.word Reset_Handler    /* 1: reset entry */
.word Default_Handler  /* 2: NMI */
.word Default_Handler  /* 3: HardFault */
.word Default_Handler  /* 4: MemManage */
.word Default_Handler  /* 5: BusFault */
.word Default_Handler  /* 6: UsageFault */
.word Default_Handler  /* 7: reserved */
.word Default_Handler  /* 8: reserved */
.word Default_Handler  /* 9: reserved */
.word Default_Handler  /* 10: reserved */
.word SVC_Handler      /* 11: SVC */
.word Default_Handler  /* 12: DebugMonitor */
.word Default_Handler  /* 13: reserved */
.word PendSV_Handler   /* 14: PendSV */
.word SysTick_Handler  /* 15: SysTick */
```

Each `.word` occupies four bytes. For example, SysTick's vector is at `vector_table_base + 15 * 4`, or offset `0x3C`.

When the CPU accepts a SysTick exception, it uses entry 15 to find the handler's address and begins executing there. There is no C function call to `SysTick_Handler()` in this program.

## SVC_Handler: enter the kernel through an instruction

Executing `svc #0` triggers the SVC exception. The CPU finds `SVC_Handler` through the vector table and enters it.

The `#0` is an immediate value carried by the instruction. It does **not** select handler number zero. This implementation does not inspect that value.

In `main.c`, the first task is selected before executing SVC:

```c
current_task = &task_b_record;

/* Other setup occurs here. */
asm("svc #0");
```

The connection is:

```text
execute svc #0 → CPU accepts SVC exception → vector entry 11 → SVC_Handler
```

The handler begins with:

```asm
SVC_Handler:
    tst lr, #4
    beq restore_task
    mrs r0, psp
    stmdb r0!, {r4-r11}
    ldr r1, =current_task
    ldr r1, [r1]
    str r0, [r1]
    bl schedule_next
```

Here LR contains **EXC_RETURN**, a special exception-return value, rather than an ordinary function return address. `tst lr, #4` tests bit 2. `beq` branches when that bit is zero, meaning the interrupted code used MSP.

The handler checks bit 2 of the exception-return value in LR to distinguish two paths:

- **First launch from `main()`, using MSP:** there is no outgoing task to save. Jump directly to `restore_task` and start the task selected by `current_task`. Currently, this is task B.
- **SVC from a running task, using PSP:** save the outgoing task's `r4–r11`, record its stack pointer, call `schedule_next()`, and restore the selected task.

SVC therefore supports both starting the first task and switching from an already running task. The current task loops use `task_sleep()` rather than SVC to request switches.

## SysTick_Handler: a timer tick happened

When the configured SysTick counter reaches zero, it requests the SysTick exception, provided its interrupt is enabled. Interrupt masking and priorities determine when the handler can run.

### Configuring and enabling the timer

The pointers in `main.c` refer to memory-mapped hardware registers:

```c
volatile uint32_t *systick_ctrl = (volatile uint32_t *)0xE000E010;
volatile uint32_t *systick_reload = (volatile uint32_t *)0xE000E014;
volatile uint32_t *systick_current = (volatile uint32_t *)0xE000E018;
```

Writing through these pointers configures the timer hardware. In `main()`:

```c
*pendsv_priority = 0xFFu;
*systick_reload = 999u;
*systick_current = 0u;
```

`999` sets a period of 1,000 selected clock cycles. Writing the current-value register clears the current count. This code alone does not enable the timer.

Task B enables it when it first starts:

```c
void task_b(void)
{
    volatile uint32_t count_b = 0;
    *systick_ctrl = 7u;
    while (1)
    {
        count_b++;
        task_sleep(5);
    }
}
```

`7u` is binary `111`, enabling three control bits:

| Bit | Name | Effect when set |
| --- | --- | --- |
| 0 | ENABLE | Run the counter |
| 1 | TICKINT | Request an exception when the counter reaches zero |
| 2 | CLKSOURCE | Use the processor clock |

The period is therefore 1,000 processor-clock cycles, not necessarily 1,000 milliseconds.

```text
task B writes CTRL = 7
  → hardware counter runs and periodically reaches zero
  → SysTick exception becomes pending
  → CPU accepts it when allowed
  → CPU uses vector entry 15
  → SysTick_Handler executes
```

### Inside the timer handler

```asm
SysTick_Handler:
    mov r0, lr
    push {r0}

    mrs r0, primask
    push {r0}
    cpsid i
    bl task_countdown_processing
    pop {r0}
    msr primask, r0

    ldr r0, =0xE000ED04
    ldr r1, =0x10000000
    str r1, [r0]
    pop {r3}
    bx r3
```

The first push preserves EXC_RETURN because `bl task_countdown_processing` overwrites LR. The handler also preserves PRIMASK, masks configurable interrupts while updating task countdowns, and then restores the previous mask.

The write to `0xE000ED04` sets bit 28 (`PENDSVSET`) in ICSR. Finally, `bx r3` uses the preserved EXC_RETURN to leave the handler. If PendSV is eligible, the CPU can transition directly into it through **tail-chaining**, without restoring and immediately re-saving the task's hardware frame.

The handler:

1. Calls `task_countdown_processing()` to decrement sleeping tasks' tick counts.
2. Marks a sleeping task `READY` when its count reaches zero.
3. Writes the `PENDSVSET` bit in ICSR to request PendSV.

Setting that bit **requests PendSV**; it is not a normal function call such as `bl PendSV_Handler`. The CPU runs PendSV when priorities and interrupt masking allow it. This implementation configures PendSV to the lowest priority.

SysTick requests a context switch **every tick**, whether or not a sleeping task wakes. It does not perform the actual context switch itself.

For example, this is the task A portion of `task_countdown_processing()`:

```c
if (task_a_record.state == SLEEPING)
{
    if (task_a_record.sleep_tick_count > 0)
    {
        --task_a_record.sleep_tick_count;
    }

    if (task_a_record.sleep_tick_count == 0)
    {
        task_a_record.state = READY;
    }
}
```

Becoming `READY` makes task A eligible for selection. It does not immediately start executing task A inside this function.

## PendSV_Handler: perform the context switch

Saving a task's context is shared between the CPU and the assembly handler:

| Who saves it? | Registers |
| --- | --- |
| CPU automatically on exception entry | `r0–r3`, `r12`, task `LR`, `PC`, `xPSR` |
| PendSV assembly | `r4–r11` |

For an interrupted task using PSP, the hardware frame is on that task's stack. The handlers themselves execute using MSP.

```asm
PendSV_Handler:
    mrs r0, psp
    stmdb r0!, {r4-r11}
    ldr r1, =current_task
    ldr r1, [r1]
    str r0, [r1]
    bl schedule_next
    b restore_task
```

`mrs r0, psp` copies PSP into `r0`. `stmdb r0!, {r4-r11}` saves eight registers below the hardware frame and updates **r0**, not PSP. `str r0, [r1]` records that combined frame's address in `saved_sp`, the first field of the task record.

PendSV performs these steps:

1. Reads PSP to find the outgoing task's hardware frame.
2. Saves `r4–r11` below that frame using `stmdb`.
3. Stores the resulting address in the outgoing task's `saved_sp`.
4. Calls `schedule_next()` to select a runnable task through `current_task`.
5. Branches to the shared `restore_task` code.

The shared restore code:

```asm
restore_task:
    ldr r0, =current_task
    ldr r0, [r0]
    ldr r0, [r0]
    ldmia r0!, {r4-r11}
    msr psp, r0
    ldr lr, =0xfffffffd
    bx lr
```

The three loads follow this chain:

```text
address of current_task → selected task record → selected task's saved_sp
```

Restoring then proceeds as follows:

1. Loads the selected task's `saved_sp`.
2. Restores `r4–r11` using `ldmia`.
3. Sets PSP to the selected task's hardware frame.
4. Loads LR with `0xFFFFFFFD` and executes `bx lr`.

That value tells the CPU to return to Thread mode using PSP. The CPU restores the hardware frame, including **PC**, so the selected task resumes where it stopped.

On the first launch, the frame was prepared by `task_stack_init()`, so restoring PC starts the task's entry function.

The scheduler can select the same task again if the other tasks are sleeping. If both application tasks are sleeping, it selects the idle task.

## The three execution flows

### Starting the first task

```text
main()
  → svc #0
  → SVC_Handler
  → restore current_task
  → task B starts
```

### Switching after a timer tick

```text
SysTick counter reaches zero
  → SysTick_Handler
  → update sleep countdowns and READY states
  → mark PendSV pending
  → PendSV_Handler runs when allowed
  → save outgoing context
  → select next task
  → restore selected context
```

### Switching when a task sleeps

```text
task_sleep(n), where n > 0
  → mark current task SLEEPING
  → set its sleep countdown
  → mark PendSV pending
  → PendSV_Handler runs when allowed
  → switch to a runnable task
```

`task_sleep()` requests PendSV itself: the task does **not** need to wait for the next SysTick to switch away. Later SysTick interrupts count down its sleep and make it eligible to run again.

For `task_sleep(0)`, the task remains ready and requests PendSV to yield its turn.

The nonzero-sleep path in `task_sleep()` contains:

```c
current_task->state = SLEEPING;
current_task->sleep_tick_count = ticks;
*pendsv_set = 0x10000000;
```

These lines execute with configurable interrupts masked. The function then restores the previous PRIMASK value, allowing the pending switch to run if interrupts were previously enabled. `pendsv_set` points to ICSR, so this requests the same PendSV exception that SysTick requests.

## Quick recall

- **SVC:** an instruction requests entry into the handler; here it starts the first task and also supports switching.
- **SysTick:** a timer tick updates sleep countdowns and requests a switch.
- **PendSV:** saves the outgoing task, selects a runnable task, and restores its context with help from the CPU.
