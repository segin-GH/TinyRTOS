#ifndef SEM_H
#define SEM_H

#include <stdint.h>

typedef struct
{
    uint32_t count;
    uint32_t *wait_task;
} sem_t;

void sem_init(sem_t *sem);
void sem_deinit(sem_t *sem);
void sem_take(sem_t *sem);
void sem_give(sem_t *sem);

#endif
