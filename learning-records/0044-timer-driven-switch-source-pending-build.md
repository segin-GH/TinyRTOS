# Timer-driven switch source pending build

On 2026-10-21, learner shared GDB output stopping in PendSV_Handler, then stepping into SysTick_Handler. PendSV delivery is observed. They requested moving on from further return tracing; no additional return experiment was completed.

Through guided incremental edits, PendSV now reads PSP, saves r4–r11, updates current_task->saved_sp, calls schedule_next, and branches to the existing restore_task code. Learner initially proposed MSR to read PSP; teacher supplied MRS and explained direction. Source reviewed; independent integrated implementation remains unverified.

Timer enable was moved from main to task_b before its loop, because main initially uses MSP and PSP is not initialized until launch. Both task-loop SVCs were removed; main retains launch SVC. Initial current_task remains B, which must run to enable SysTick in this temporary startup arrangement. SysTick requests PendSV; its lowest priority write precedes launch.

Next learner rebuilds and restarts QEMU/GDB. Observe repeated task selection and task execution with no voluntary yields before calling preemption verified. No new build or timer-driven task switching evidence yet. Learner runs builds. Current reload is 999, which previously made single stepping encounter frequent timer handlers.
