# Per-task stacks and saved registers

On 2026-10-07, the learner correctly identified that saving B into a shared register-save area overwrites A's saved values. They independently proposed stacks with stack pointers to track the saved state. The teacher explained giving each task a separate stack and recording its saved SP in a task record.

The initial question about saving SP alone was unclear to the learner. With a concrete example where only SP = 0x20001000 was recorded and r0 = 10 was never saved, they correctly concluded that the stack pointer and register values must both be saved. This demonstrates that restoring an address alone cannot recover unsaved register contents.

The phrase "all the registers" expresses the need to preserve task state, not demonstrated knowledge of the exact Cortex-M context layout. Hardware versus software saving, execution position, flags, and first-task setup remain unverified. Next ask what execution position must be retained to resume a paused task at the correct instruction. Keep one question at a time.
