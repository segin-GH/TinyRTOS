# PendSV request pending observation

On 2026-10-21, source inspection confirmed a dedicated PendSV vector and bx lr handler, a volatile uint8_t priority pointer at 0xE000ED22, and a write of 0xFFu before enabling SysTick. Learner correctly recalled 1 << 28 for the pending mask and uint8_t pointer width; volatile qualification was prompted.

With explicit instruction-by-instruction guidance, learner added SysTick assembly loading ICSR address 0xE000ED04 into r0, loading mask 0x10000000 into r1, storing r1 through r0, then executing bx lr. Source sequence verified. PendSV still only returns. No new build or PendSV execution observed yet; no timer-driven task switch implemented.

Next learner rebuilds, restarts QEMU with the new ELF, and sets a fresh PendSV_Handler breakpoint in GDB to observe delivery. Existing tasks still yield with SVC. Learner runs builds. Explain mechanisms and purpose before edits per updated teach skill.
