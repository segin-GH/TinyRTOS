# Exception return restores the saved PC

On 2026-10-07, the teacher introduced handler LR's EXC_RETURN marker, 0xFFFFFFFD for returning to Thread mode using PSP, and BX LR as the trigger under those conditions. Asked where B's actual resume address comes from, the learner answered the stack. The teacher specified the saved PC in B's hardware frame. Given saved PC = 0x00000180, the learner correctly predicted execution resumes at 0x00000180.

This demonstrates the guided link from the hardware frame's saved PC to execution resumption. The learner has not independently decoded EXC_RETURN or explained a complete exception-return sequence. Recheck the marker-versus-code-address distinction after spacing.

Next introduce the first-run problem: a new task has never been interrupted and has no naturally saved context. Use a proposed task_b entry function to ask which function's entry address belongs in its prepared frame's PC slot. Explain fabricated initial frames only in small steps; do not provide a completed task initializer. Thumb state, xPSR initialization, initial alignment, argument placement, and task-return behavior remain unverified.
