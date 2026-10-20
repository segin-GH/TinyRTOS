# SysTick configuration pending observation

On 2026-10-20, the learner identified vector index 15 as Default_Handler and changed it to SysTick_Handler. Source inspection initially found a self-branch; after feedback the learner changed it to bx lr. They correctly predicted this returning handler would not schedule B and that cycle duration depends on processor clock frequency. They calculated reload 999 for 1000 cycles.

The learner identified mask 0x7 but initially proposed AND; after computing 0 AND 7 as zero, they chose OR. They recalled volatile, then used guidance to declare volatile uint32_t pointers for control, reload, and current registers. Direct register-write syntax was explicitly supplied after they requested help; do not infer independent MMIO syntax proficiency.

Inspected source now contains reload = 999u, current = 0u, control = 7u through the pointers before the launch SVC. No new build or interrupt observation reported. Next learner rebuilds, then observes SysTick_Handler in QEMU/GDB. Current handler only returns; preemption is not implemented. SysTick may interrupt main before first launch because it is enabled before SVC; identify the interrupted context from EXC_RETURN when observing.
