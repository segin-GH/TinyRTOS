#include <stdint.h>
#include <sys/types.h>

// Task stack
_Alignas(8) uint32_t task_a_stack[64] = {0};
_Alignas(8) uint32_t task_b_stack[64] = {0};

void task_a(void)
{
    while (1)
    {
        asm("svc #0");
    }
}

void task_b(void)
{
    while (1)
    {
        asm("svc #0");
    }
}

void task_exit(void)
{
    while (1)
    {
    }
}

struct task
{
    uint32_t *saved_sp;
};

struct task task_a_record;
struct task task_b_record;
struct task *current_task;

void schedule_next(void)
{
    current_task = (current_task == &task_a_record) ? &task_b_record : &task_a_record;
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

int main(void)
{
    task_a_record.saved_sp = task_stack_init(&task_a_stack[64], task_a);
    task_b_record.saved_sp = task_stack_init(&task_b_stack[64], task_b);

    current_task = &task_b_record;
    asm("svc #0");

    while (1)
    {
        int var = 1;
    }

    return 0;
}
