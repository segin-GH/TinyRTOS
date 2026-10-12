# Register values must survive task switches

On 2026-10-07, the learner correctly predicted that task A's pending adds r2, r0, r1 produces 300 when task B leaves r0 = 100 and r1 = 200. They identified A's intended result as 30 from its original values 10 and 20, and independently proposed storing A's register values somewhere before B runs.

This demonstrates the need to save working register values across a task switch. Restoring the values was explained by the teacher; independent understanding of restoration, storage ownership, full task context, and Cortex-M exception stacking remains unverified.

Next: ask whether a single shared save area can retain both A's and B's state when each is paused. Keep one question at a time; do not provide a context-switch implementation.
