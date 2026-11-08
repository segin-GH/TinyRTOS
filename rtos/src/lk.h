#ifndef LK_H
#define LK_H

#include <stdint.h>

// Use this functions for entering into critical execution;

uint32_t lk(void);
void unlk(uint32_t old_mask);

#endif
