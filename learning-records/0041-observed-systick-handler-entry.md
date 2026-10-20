# Observed SysTick handler entry

On 2026-10-20, the learner rebuilt, started QEMU, connected GDB at Reset_Handler, set a breakpoint on SysTick_Handler, and continued. Shared GDB output stopped at address 0xb8, startup.S:119, on bx lr inside SysTick_Handler. Timer exception delivery through the configured vector is now observed.

The interrupted context remains unknown: SysTick is enabled before the launch SVC, so it might have interrupted main or a PSP task. Next inspect live LR to distinguish EXC_RETURN 0xfffffff9 (Thread/MSP) from 0xfffffffd (Thread/PSP). No timer-driven task switch or repeated timer entry/return observed yet. Handler still only returns. Learner runs builds.
