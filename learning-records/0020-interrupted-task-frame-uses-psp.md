# Interrupted task frame stays on the task stack

On 2026-10-07, after the teacher introduced MSP for handlers and PSP as the configured task stack pointer, the learner correctly identified that the hardware-saved frame of interrupted task A goes onto A's task stack. This demonstrates the immediate frame-location prediction in the PSP setup; independent transfer to handler instructions remains unverified.

Next: predict where a PUSH executed inside the interrupt handler writes, given that Handler mode uses MSP. This distinction prevents assuming that an ordinary handler PUSH saves r4–r11 onto the task's PSP stack. Do not supply a finished context-switch implementation.
