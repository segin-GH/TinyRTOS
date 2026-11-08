#include <lk.h>
#include <sem.h>
#include <tsk.h>

#include <stdint.h>
#include <sys/types.h>

// Task stack
_Alignas(8) uint32_t task_idle_stack[64] = {0};
_Alignas(8) uint32_t task_a_stack[64] = {0};
_Alignas(8) uint32_t task_b_stack[64] = {0};

volatile uint32_t *systick_ctrl = (volatile uint32_t *)0xE000E010;
volatile uint32_t *systick_reload = (volatile uint32_t *)0xE000E014;
volatile uint32_t *systick_current = (volatile uint32_t *)0xE000E018;

task_t task_a_record;
task_t task_b_record;
task_t task_idle_record;

void task_schedule_next(void)
{
    task_t *current_task = task_get_current_running_task();
    // switch to a new task
    current_task = (current_task == &task_a_record) ? &task_b_record : &task_a_record;

    // Check if the new task is sleeping
    if (current_task->sleep_state == SLEEPING || current_task->sem_state == BLOCKED)
    {
        // switch to the other task
        current_task = (current_task == &task_a_record) ? &task_b_record : &task_a_record;

        if (current_task->sleep_state == SLEEPING || current_task->sem_state == BLOCKED)
        {
            current_task = &task_idle_record;
        }
    }

    task_set_current_running_task(current_task);
}

void task_countdown_processing(void)
{
    // this we can make it into a array and loop it for dynamic handling of all the task

    if (task_a_record.sleep_state == SLEEPING)
    {
        if (task_a_record.sleep_tick_count > 0)
        {
            --task_a_record.sleep_tick_count;
        }

        if (task_a_record.sleep_tick_count == 0)
        {
            task_a_record.sleep_state = READY;
        }
    }

    if (task_b_record.sleep_state == SLEEPING)
    {
        if (task_b_record.sleep_tick_count > 0)
        {
            --task_b_record.sleep_tick_count;
        }
        if (task_b_record.sleep_tick_count == 0)
        {
            task_b_record.sleep_state = READY;
        }
    }
}

void task_sleep(uint32_t ticks)
{
    uint32_t old_mask = lk();

    if (ticks == 0)
    {
        task_switch();
        unlk(old_mask);
        return;
    }

    task_t *current_task = task_get_current_running_task();
    current_task->sleep_state = SLEEPING;
    current_task->sleep_tick_count = ticks;
    task_switch();

    unlk(old_mask);
    return;
}

void task_idle(void)
{
    while (1)
    {
    }
}

sem_t my_sem;

void task_a(void)
{
    *systick_ctrl = 7u;
    while (1)
    {
        sem_give(&my_sem);
        task_sleep(3);
    }
}

void task_b(void)
{
    while (1)
    {
        sem_take(&my_sem);
        task_sleep(5);
    }
}

int main(void)
{
    init();

    task_idle_record.saved_sp = task_stack_init(&task_idle_stack[64], task_idle);
    task_idle_record.sleep_state = READY;
    task_idle_record.sem_state = READY;
    task_idle_record.sleep_tick_count = 0;

    task_a_record.saved_sp = task_stack_init(&task_a_stack[64], task_a);
    task_a_record.sleep_state = READY;
    task_a_record.sem_state = READY;
    task_a_record.sleep_tick_count = 0;

    task_b_record.saved_sp = task_stack_init(&task_b_stack[64], task_b);
    task_b_record.sleep_state = READY;
    task_b_record.sem_state = READY;
    task_b_record.sleep_tick_count = 0;

    sem_init(&my_sem, 1);
    task_set_current_running_task(&task_a_record);

    *systick_reload = 999u;
    *systick_current = 0u;

    asm("svc #0");

    while (1)
    {
        int var = 1;
    }

    return 0;
}
