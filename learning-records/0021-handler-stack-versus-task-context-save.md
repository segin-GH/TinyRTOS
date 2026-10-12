# Handler stack versus task context save

On 2026-10-07, the learner correctly predicted that PUSH inside the interrupt handler writes to the handler's stack, after being reminded Handler mode uses MSP. They identified A's stack pointer as the pointer to read to locate A's hardware frame; the teacher connected this to PSP in the configured task setup. They correctly chose downward address movement to allocate software-saved r4–r11 space on A's stack.

This demonstrates the stack-location distinction and downward allocation direction in the guided scenario. MRS, explicit multiple-register stores, updating PSP, and exception return remain unverified. Next introduce MRS r0, PSP and ask whether reading the pointer also saves the working register values, reinforcing the pointer-versus-memory distinction without providing a completed switch implementation.
