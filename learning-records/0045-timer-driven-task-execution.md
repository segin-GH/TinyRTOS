# Timer-driven task execution

On 2026-10-21, after rebuilding and restarting QEMU/GDB, the learner supplied PendSV entry output with current_task == &task_b_record equal to 1, followed by another entry with current_task == &task_a_record equal to 1. A later B-selection check was answered only with done, so its result is not independently established.

Shared disassembly showed A looping at 0xe8 and B at 0xf6, with no task SVC instructions. GDB output directly confirmed repeated task_b loop stops at 0xf6. After guidance to disable existing breakpoints and break only at 0xe8, the learner answered yes when asked whether it stopped in task_a. A-loop execution after B is learner-reported; its breakpoint transcript was not pasted. This supports a first timer-driven execution milestone with the stated evidence limits, not comprehensive preservation or robustness validation.

Discussed GDB disable versus delete and why a loop breakpoint can repeatedly fire before the next timer tick. No kernel changes made by teacher. Next consolidate the SysTick-request/PendSV-save-select-restore flow through learner explanation before extending scheduler features. Local/register state stress tests, timing fairness, and broader context-switch robustness remain unverified. Learner runs builds.
