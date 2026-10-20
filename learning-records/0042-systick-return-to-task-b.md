# SysTick return to task B

On 2026-10-20, shared GDB output showed LR = 0xfffffffd in SysTick_Handler, confirming return to Thread mode with PSP. Initial stepi stopped in the handler again. After disabling SysTick through GDB at control address 0xE000E010, one additional handler stop occurred, followed by task_b at its push {r7}. LR was 0xcd and xPSR 0x01000000. Return to task B is observed; the extra stop is consistent with a pending interrupt, not independently proven.

The learner explained that B resumed because A's context was never loaded, and correctly identified B's r4–r11 as the outgoing registers to save when B is interrupted. This independently rechecks the outgoing-task identity initially missed in record 0039.

Teacher introduced the intended separation: SysTick requests a switch; PendSV performs it at lowest priority. Neither PendSV nor timer-driven context switching is implemented or observed. Next locate vector index 14 (PendSV), give it a dedicated handler in small steps, then explain requesting it. SysTick was disabled only in live target memory by GDB; source still enables it on restart. Learner builds.
