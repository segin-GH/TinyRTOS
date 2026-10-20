# Observed repeated preemptive task switching

On 2026-10-21, learner restarted QEMU/GDB and supplied a trace stopping at task_b's timer-enable line, then task_a's loop. After disabling A's breakpoint and setting one at B's loop (0xf6), GDB stopped inside task_b's loop. Alternately enabling only A's loop breakpoint (0xe8) and only B's loop breakpoint produced further A and B stops. The pasted sequence directly confirms B → A → B → A → B with tasks containing no SVC yields in the reviewed source.

Timer-driven execution switching in both directions is now verified for the current build. B resumes inside its loop, not at its one-time timer-enable statement. Explained that a loop breakpoint may fire repeatedly before a timer tick and that selectively enabling a destination task's breakpoint lets the other task run freely.

This verifies execution transfer, not comprehensive working-register/local-state preservation, fairness, stack bounds, or ABI robustness. Next return to the previously confused PSP-versus-r0 writeback distinction using concrete before/after values or a small GDB experiment. Learner runs builds; explain the purpose before each exercise.
