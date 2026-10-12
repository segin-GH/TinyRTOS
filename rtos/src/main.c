#include <stdint.h>
#include <sys/types.h>

uint32_t task_a_stack[64] = {0};

int varx = 7;
int vary;

void task_a(void)
{
    while (1)
    {
    }
}

void task_exit(void)
{
    while (1)
    {
    }
}

int main(void)
{
    // stack for the function
    // at the end we are going to populate the register that we need
    uint32_t *sp = &task_a_stack[64];

    // xspr register we are setting it to the thumb instructions
    uint32_t *xspr = --sp;
    *xspr = 0x1000000;

    // function pointer we need to execute
    uint32_t *pc = --sp;
    *pc = (uint32_t)(uintptr_t)&task_a;

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

    asm("svc #0");
    while (1)
    {
        int var = 1;
    }

    return 0;
}
