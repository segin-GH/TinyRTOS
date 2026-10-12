# Execution position and condition flags belong to task context

On 2026-10-07, the learner independently identified PC as the register tracking a paused task's execution position. They agreed that changing condition flags between CMP and BEQ could corrupt the resumed task's branch decision, and correctly identified Z = 1 as the value needed for BEQ after an equal comparison.

The teacher explained BEQ's dependency on Z before the learner supplied that value. Independent explanation of the comparison-to-branch dependency remains a useful later retrieval check. Combined with the preceding records, the learner has identified working register values, SP, PC, and condition flags as state relevant to resumption. This is not evidence of mastery of the complete Cortex-M context layout.

Next: introduce Cortex-M exception entry as automatic saving of part of the task state, using the Arm guide and a small observed or predicted stack frame. Distinguish hardware saving from the remaining RTOS software responsibility. Do not supply a finished context-switch implementation.
