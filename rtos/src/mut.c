#include "tsk.h"
#include <lk.h>
#include <mut.h>
#include <stdbool.h>

void mut_init(mut_t *mut)
{
    mut->owner = (void *)0;
    return;
}

bool mut_lock(mut_t *mut)
{
    uint32_t reg = lk();
    if (mut->owner != (void *)0)
    {
        // There is already a owner
        unlk(reg);
        return false;
    }

    mut->owner = task_get_current_running_task();
    unlk(reg);
    return true;
}

bool mut_unlock(mut_t *mut)
{
    uint32_t reg = lk();
    task_t *curr_task = task_get_current_running_task();
    if (curr_task != mut->owner)
    {
        // Not the owner of the task
        unlk(reg);
        return false;
    }

    mut->owner = (void *)0;
    unlk(reg);
    return true;
}
