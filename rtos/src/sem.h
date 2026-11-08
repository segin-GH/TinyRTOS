#ifndef SEM_H
#define SEM_H

#include <stdint.h>
#include <tsk.h>

typedef struct
{
    uint32_t count;
    uint32_t max_count;
    task_t *wait_task;
} sem_t;

void sem_init(sem_t *sem, uint32_t max_count);
void sem_deinit(sem_t *sem);
void sem_take(sem_t *sem);
void sem_give(sem_t *sem);

#endif
