.syntax unified                 /* Use unified Arm/Thumb assembly syntax. */
.cpu cortex-m3                  /* Assemble for the Cortex-M3 instruction set. */
.thumb                          /* Generate Thumb instructions. */

.global Reset_Handler
.global Default_Handler

.section .isr_vector, "a", %progbits

/* Vector index 0 supplies the initial MSP; index 1 supplies the reset entry. */
/* Remaining entries are handler addresses, indexed by exception number. */
.word _estack
.word Reset_Handler
.word Default_Handler           /* 2: NMI (non-maskable interrupt). */
.word Default_Handler           /* 3: HardFault. */
.word Default_Handler           /* 4: MemManage fault. */
.word Default_Handler           /* 5: BusFault. */
.word Default_Handler           /* 6: UsageFault. */
.word Default_Handler           /* 7: Reserved slot; existing placeholder. */
.word Default_Handler           /* 8: Reserved slot; existing placeholder. */
.word Default_Handler           /* 9: Reserved slot; existing placeholder. */
.word Default_Handler           /* 10: Reserved slot; existing placeholder. */
.word SVC_Handler               /* 11: Supervisor call, requested with SVC. */
.word Default_Handler           /* 12: DebugMonitor. */
.word Default_Handler           /* 13: Reserved slot; existing placeholder. */
.word PendSV_Handler            /* 14: Deferred context-switch exception. */
.word SysTick_Handler           /* 15: System timer exception. */


.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:

    /* Linker symbols describe .data's initial image and runtime destination. */
    /* LDR =symbol loads an address here, not the word stored at that address. */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

copy_data:
    /* Copy while destination < end (unsigned); the end address is excluded. */
    cmp r1, r2
    bcc copy_data_loop
    b clear_bss

copy_data_loop:
    ldr r3, [r0]                /* Read one initialized 32-bit word from FLASH. */
    str r3, [r1]                /* Write that word to its runtime address in RAM. */

    /* Plain LDR/STR above do not advance the address registers. */
    adds r0, r0, #4
    adds r1, r1, #4

    b copy_data


clear_bss:

    /* Zero the RAM range reserved for zero-initialized static/global objects. */
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0

clear_bss_loop:

    /* An empty range needs no stores; stop when r1 reaches _ebss. */
    cmp r1, r2
    bcc clear_bss_do

    b call_main

clear_bss_do:

    str r3, [r1]                /* r3 still holds zero. */

    adds r1, r1, #4

    b clear_bss_loop


call_main:

    bl main                     /* Call C after .data/.bss initialization; set LR. */

hang:

    b hang                      /* Stay here if main returns. */


.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:
    b Default_Handler           /* Unhandled exception: remain here for debugging. */


.section .text.SVC_Handler
.type SVC_Handler, %function

SVC_Handler:
    /* Handler LR contains EXC_RETURN. Bit 2 identifies the return stack: */
    /* 0 = MSP (main's initial launch), 1 = PSP (an already running task). */
    tst lr, #4
    beq restore_task            /* First launch: no outgoing task to save. */
    /* Hardware already stacked r0-r3, r12, LR, PC, xPSR on the task stack. */
    mrs r0, psp                 /* Copy its hardware-frame address into r0. */
    stmdb r0!, {r4-r11}          /* Save 8 more words below it; update r0 only. */
    ldr r1, =current_task        /* Address of the global pointer variable. */
    ldr r1, [r1]                /* Address of the outgoing task record. */
    str r0, [r1]                /* Store combined-frame base in saved_sp (offset 0). */
    bl schedule_next            /* Select incoming task; BL overwrites live LR. */

restore_task:
    /* Shared by first launch and both switching paths. */
    ldr r0, =current_task        /* Address of the global pointer variable. */
    ldr r0, [r0]                /* Address of the selected task record. */
    ldr r0, [r0]                /* Selected task's saved_sp: address of saved r4. */

    ldmia r0!, {r4-r11}          /* Restore software frame; advance r0 by 32 bytes. */
    msr psp, r0                 /* PSP now points at the hardware frame's r0 slot. */
    /* Construct a fresh EXC_RETURN, so the earlier BL's LR is not used. */
    ldr lr, =0xfffffffd          /* Return to Thread mode using PSP (basic frame). */
    bx lr                       /* Hardware restores its frame and resumes saved PC. */



.section .text.SysTick_Handler
.type SysTick_Handler, %function

SysTick_Handler:
    /* Request a context switch; PendSV performs the actual save/select/restore. */
    ldr r0, =0xE000ED04          /* Interrupt Control and State Register (ICSR). */
    ldr r1, =0x10000000          /* Bit 28: PENDSVSET. */
    str r1, [r0]                /* Write 1 to mark PendSV pending. */
    bx lr                       /* Exception return; pending PendSV may run next. */

.section .text.PendSV_Handler
.type PendSV_Handler, %function

PendSV_Handler:
    /* Assumes a task using PSP was interrupted; handlers themselves use MSP. */
    /* Hardware has already saved the interrupted task's hardware frame. */
    mrs r0, psp                 /* Read PSP without changing it. */
    stmdb r0!, {r4-r11}          /* Save software frame; r0 becomes combined base. */
    ldr r1, =current_task
    ldr r1, [r1]
    str r0, [r1]                /* Persist outgoing saved_sp before selecting next. */
    bl schedule_next            /* Change current_task; restore code replaces LR. */
    b restore_task              /* Restore selected task, possibly the same task. */
