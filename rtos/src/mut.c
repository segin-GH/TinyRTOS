#include "tsk.h"
#include <lk.h>
#include <mut.h>
#include <stdbool.h>

void mut_init(mut_t *mut)
{
    mut->owner = (void *)0;
    mut->waiter = (void *)0;
    return;
}

bool mut_try_lock(mut_t *mut)
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

int mut_lock(mut_t *mut)
{
    for (;;)
    {
        uint32_t reg = lk();

        if (mut->owner == (void *)0)
        {
            // There is no owner we can break;
            mut->owner = task_get_current_running_task();
            unlk(reg);
            return 0;
        }

        task_t *self = task_get_current_running_task();
        if (mut->owner == self)
        {
            unlk(reg);
            return 1;
        }

        mut->waiter = self;
        mut->waiter->mut_state = BLOCKED;
        task_switch();
        unlk(reg);
    }

    return 0;
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

    if (mut->waiter != (void *)0)
    {
        mut->waiter->mut_state = READY;
        mut->waiter = (void *)0;

        task_switch();
    }

    unlk(reg);
    return true;
}
