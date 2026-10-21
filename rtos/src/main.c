#include <stdint.h>
#include <sys/types.h>

// Task stack
_Alignas(8) uint32_t task_idle_stack[64] = {0};
_Alignas(8) uint32_t task_a_stack[64] = {0};
_Alignas(8) uint32_t task_b_stack[64] = {0};

volatile uint32_t *systick_ctrl = (volatile uint32_t *)0xE000E010;
volatile uint32_t *systick_reload = (volatile uint32_t *)0xE000E014;
volatile uint32_t *systick_current = (volatile uint32_t *)0xE000E018;

volatile uint32_t *pendsv_set = (volatile uint32_t *)0xE000ED04;
volatile uint8_t *pendsv_priority = (volatile uint8_t *)0xE000ED22;

enum task_state
{
    SLEEPING,
    READY,
};

struct task
{
    uint32_t *saved_sp;
    enum task_state state;
    uint32_t sleep_tick_count;
};

struct task task_a_record;
struct task task_b_record;
struct task task_idle_record;
struct task *current_task;

void task_exit(void)
{
    while (1)
    {
    }
}

void schedule_next(void)
{
    // switch to a new task
    current_task = (current_task == &task_a_record) ? &task_b_record : &task_a_record;

    // Check if the new task is sleeping
    if (current_task->state == SLEEPING)
    {
        // switch to the other task
        current_task = (current_task == &task_a_record) ? &task_b_record : &task_a_record;

        if (current_task->state == SLEEPING)
        {
            current_task = &task_idle_record;
        }
    }
}

uint32_t *task_stack_init(uint32_t *stack_top, void (*entry)(void))
{

    // stack for the function
    // at the end we are going to populate the register that we need
    uint32_t *sp = stack_top;

    // xspr register we are setting it to the thumb instructions
    uint32_t *xspr = --sp;
    *xspr = 0x1000000;

    // function pointer we need to execute
    uint32_t *pc = --sp;
    *pc = (uint32_t)(uintptr_t)entry;

    // this is so that we can unset the thumb instruction bcz we already set it to  thumb instruction at xspr
    // eg: Actual instruction address:  0x100
    //     C function pointer:          0x101
    *pc = *pc & ~1u;

    // Starting task_a: Exception return restores PC and xPSR together. PC supplies the instruction address; xPSR says
    // “execute Thumb instructions.”
    // If task_a later returns: A normal function return branches to the address in LR. That operation uses LR’s bit 0
    // to select Thumb state. So task_exit’s function pointer must keep its Thumb marker.

    uint32_t *lr = --sp;
    *lr = (uint32_t)(uintptr_t)&task_exit;

    *--sp = 0; // r12
    *--sp = 0; // r3
    *--sp = 0; // r2
    *--sp = 0; // r1
    *--sp = 0; // r0

    *--sp = 0; // r11
    *--sp = 0; // r10
    *--sp = 0; // r9
    *--sp = 0; // r8
    *--sp = 0; // r7
    *--sp = 0; // r6
    *--sp = 0; // r5
    *--sp = 0; // r4

    return sp;
}

void task_countdown_processing(void)
{
    // this we can make it into a array and loop it for dynamic handling of all the task

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

    if (task_b_record.state == SLEEPING)
    {
        if (task_b_record.sleep_tick_count > 0)
        {
            --task_b_record.sleep_tick_count;
        }
        if (task_b_record.sleep_tick_count == 0)
        {
            task_b_record.state = READY;
        }
    }
}

void task_sleep(uint32_t ticks)
{
    uint32_t old_mask;

    asm volatile("mrs %0, primask\n"
                 "cpsid i"
                 : "=r"(old_mask)
                 :
                 : "memory");

    if (ticks == 0)
    {
        *pendsv_set = 0x10000000;
        asm volatile("msr primask, %0" : : "r"(old_mask) : "memory");
        return;
    }

    current_task->state = SLEEPING;
    current_task->sleep_tick_count = ticks;
    *pendsv_set = 0x10000000;

    asm volatile("msr primask, %0" : : "r"(old_mask) : "memory");
    return;
}

void task_idle(void)
{
    while (1)
    {
    }
}

void task_a(void)
{
    volatile uint32_t count_a = 0;
    while (1)
    {
        count_a++;
        task_sleep(3);
    }
}

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

int main(void)
{
    task_idle_record.saved_sp = task_stack_init(&task_idle_stack[64], task_idle);
    task_idle_record.state = READY;
    task_idle_record.sleep_tick_count = 0;

    task_a_record.saved_sp = task_stack_init(&task_a_stack[64], task_a);
    task_a_record.state = READY;
    task_a_record.sleep_tick_count = 0;

    task_b_record.saved_sp = task_stack_init(&task_b_stack[64], task_b);
    task_b_record.state = READY;
    task_b_record.sleep_tick_count = 0;

    current_task = &task_b_record;

    *pendsv_priority = 0xFFu;
    *systick_reload = 999u;
    *systick_current = 0u;

    asm("svc #0");

    while (1)
    {
        int var = 1;
    }

    return 0;
}
