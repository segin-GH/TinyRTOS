#include <lk.h>
#include <stdint.h>
#include <sys/types.h>

uint32_t lk(void)
{
    uint32_t old_mask;
    asm volatile("mrs %0, primask\n"
                 "cpsid i"
                 : "=r"(old_mask)
                 :
                 : "memory");

    return old_mask;
}

void unlk(uint32_t old_mask)
{
    asm volatile("msr primask, %0" : : "r"(old_mask) : "memory");
}
