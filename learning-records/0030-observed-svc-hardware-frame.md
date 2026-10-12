# Observed SVC hardware frame

On 2026-10-12, the learner added asm("svc #0") before main's loop, rebuilt, and supplied QEMU/GDB output stopped at Default_Handler. Live SP = 0x203fffd0, LR = 0xfffffff9, PC = 0x84. The eight stack words match r0–r3, r12, LR, PC, xPSR; saved PC = 0x90 and saved xPSR = 0x61000000.

The learner correctly identifies 0x90 as the exception-return resume address. Their disassembly locates SVC at 0x8e and the following MOVS at 0x90, directly corroborating the saved PC. Current execution uses MSP; no PSP configuration, returning handler, or first-task launch has been demonstrated. The teacher explained SVC and its service immediate; independent understanding of that mechanism remains to be checked.

Next: distinguish live handler LR = 0xfffffff9 from stacked interrupted LR = 0x6d before attempting exception return. Keep the learner writing kernel changes.
