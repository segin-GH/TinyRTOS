# Restore layout and task selection

On 2026-10-07, given a diagram with saved r4 at combined base 0x20000FC0 and saved r0 at hardware-frame base 0x20000FE0, the learner correctly predicted that using the combined base for hardware restoration would load saved r4 into r0. This demonstrates a concrete consequence of choosing the wrong frame base.

After the teacher summarized software restoration of r4–r11 followed by hardware exception return, the learner correctly identified the RTOS as selecting the next task. Hardware restoration follows the selected context rather than deciding which task is eligible to run.

Next request one integrated explanation of saving A and restoring B, including each task's stack and saved base, the hardware/software split, and the hardware-frame pointer at return. Do not infer integrated understanding from individual guided answers. Implementation, first-task frame construction, EXC_RETURN, and safe scheduler mechanics remain unverified.
