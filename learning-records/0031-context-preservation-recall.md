# Context preservation recall

On 2026-10-12, the learner requested a return to the RTOS purpose after exception terminology and the distinction between live and stacked LR proved unclear. Pause the custom SVC handler exercise; do not infer exception-return understanding from earlier saved-PC answers.

During the subsequent guided recall, the learner identifies saving A's SP, predicts that overwritten context would restore B's saved PC, selects A's saved SP to resume A, and predicts r4 = 99 if B overwrites A's r4 = 42 without preservation. They explicitly state that software must save it.

Next connect the software save to A's own stack. Keep questions and explanations small and grounded in preserving a task, before returning to handler mechanics or first-task launch. No new kernel implementation demonstrated.
