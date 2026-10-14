# Observed first task launch

On 2026-10-14, the learner built and stepped through the SVC first-task launch themselves. Handler loads task_a_stack base, adds 192 bytes to index 48, restores r4-r11 with ldmia r0!, writes the resulting index-56 address to PSP, loads LR with 0xfffffffd, and executes bx lr.

GDB observations: base 0x20000008; combined frame base 0x200000c8; r4-r11 all zero after restore; hardware frame base in r0 0x200000e8; LR confirmed 0xfffffffd. After stepping bx lr, GDB stops at task_a's first instruction, push {r7}, at 0xa0. SP is 0x20000108, matching &task_a_stack[64]. This demonstrates initial task entry with the prepared private stack, before the function prologue executes.

GDB labels 0x20000108 as vary because the global lies immediately after the task array. SP is initially the array's one-past-end address; descending stack pushes allocate within the array. This is not evidence that vary was overwritten.

Learner implemented guided assembly increments and supplied runtime evidence. Independent launch implementation and integrated explanation remain to be assessed. No cooperative switching, task return behavior, or context preservation across multiple tasks verified. Handler is a dedicated first-launch path; main's abandoned MSP frame and later SVC behavior need attention before reuse as a yield handler.

Next small observation: stepi the task's push {r7}; compare SP with the end of its stack, and examine the saved word. Consolidate stack ownership and the hardware/software restore split before adding switching.

Followup observed: learner supplied GDB output after push {r7}: SP = 0x20000104, memory there = 0. After add r7, sp, #0, SP and r7 both equal 0x20000104. This verifies task-stack use by the function prologue. Next consolidate the launch explanation before cooperative switching design.
