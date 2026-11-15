#ifndef MUT_H
#define MUT_H

#include "tsk.h"
#include <stdbool.h>

typedef struct
{
    task_t *owner;
    task_t *waiter;
} mut_t;

void mut_init(mut_t *mut);
int mut_lock(mut_t *mut);
bool mut_try_lock(mut_t *mut);
bool mut_unlock(mut_t *mut);

#endif
