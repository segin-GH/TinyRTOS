#include <lk.h>
#include <sem.h>
#include <tsk.h>

void sem_init(sem_t *sem)
{
    uint32_t msk = lk();
    sem->count = 0;
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
    uint32_t msk = lk();

    if (sem->count == 0)
    {
        unlk(msk);
        return;
    }

    --sem->count;
    unlk(msk);
    return;
}

void sem_give(sem_t *sem)
{
    uint32_t msk = lk();
    ++sem->count;
    unlk(msk);
    return;
}
