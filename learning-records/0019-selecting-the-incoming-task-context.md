# Selecting the incoming task context

On 2026-10-07, given A's saved SP = 0x20000FC0 and B's saved SP = 0x20001FC0, the learner correctly selected B's pointer to locate B's context. They also correctly identified that mistakenly selecting A's saved pointer would restore A's saved register values.

This demonstrates the association between task identity, its saved stack pointer, and the saved context in its stack. MSP/PSP selection and exception-return details have not yet been taught or demonstrated.

Next introduce MSP versus PSP, including that hardware stacks the interrupted task's frame on its active stack before a handler uses MSP. Ask for a stack-selection prediction rather than implying the hardware copies the frame between stacks.
