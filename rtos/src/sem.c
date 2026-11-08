#include <lk.h>
#include <sem.h>
#include <tsk.h>

void sem_init(sem_t *sem, uint32_t max_count)
{

    if (max_count == UINT32_MAX)
    {
        max_count = UINT32_MAX - 1;
    }

    uint32_t msk = lk();
    sem->count = 0;
    sem->max_count = max_count;
    sem->wait_task = 0;
    unlk(msk);
    return;
}

void sem_deinit(sem_t *sem)
{
    uint32_t msk = lk();
    sem->count = 0;
    unlk(msk);
    return;
}

void sem_take(sem_t *sem)
{
    for (;;)
    {
        uint32_t mask = lk();

        if (sem->count > 0)
        {
            --sem->count;
            unlk(mask);
            return;
        }

        task_t *self = task_get_current_running_task();
        sem->wait_task = self;
        sem->wait_task->sem_state = BLOCKED;
        task_switch();
        unlk(mask);
    }

    return;
}

void sem_give(sem_t *sem)
{
    uint32_t msk = lk();
    ++sem->count;

    if (sem->count > sem->max_count)
    {
        sem->count = sem->max_count;
    }

    if (sem->wait_task != 0)
    {
        sem->wait_task->sem_state = READY;
        sem->wait_task = 0;

        task_switch();
    }

    unlk(msk);
    return;
}
