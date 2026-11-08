#ifndef TSK_H
#define TSK_H

#include <stdint.h>

typedef enum
{
    SLEEPING,
    READY,
    BLOCKED,
} task_state_t;

typedef struct
{
    uint32_t *saved_sp;
    task_state_t sleep_state;
    task_state_t sem_state;
    uint32_t sleep_tick_count;
} task_t;

// FIX: is this a good idea ?;
extern task_t *current_task;

void init(void);
void task_switch(void);

uint32_t *task_stack_init(uint32_t *stack_top, void (*entry)(void));

void task_set_current_running_task(task_t *curr_task);
task_t *task_get_current_running_task(void);

#endif
