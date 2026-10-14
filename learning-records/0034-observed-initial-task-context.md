# Observed initial task context

On 2026-10-14, the learner built /tmp/tinyrtos-session.elf and ran QEMU/GDB themselves. Stopped before SVC at main.c:66. `p sp == &task_a_stack[48]` returned 1. The 16-word dump starts at 0x200000c8: r4–r11 and r0–r3/r12 are zero; stacked LR is 0x91, PC is 0x88, and xPSR is 0x01000000. The hardware frame begins at index 56, address 0x200000e8. These frame addresses are eight-byte aligned.

Learner independently identified r4 at index 48 and, with a prompt to count the eight software words, r0 at index 56. After reviewing pointer versus pointee alignment, source now declares `_Alignas(8) uint32_t task_a_stack[64]` and an ordinary uint32_t pointer sp.

This verifies construction and memory inspection, not task execution. SVC remains routed to Default_Handler; no PSP configuration or launch verified. Next observe SVC entry and distinguish main's live hardware frame from the separately constructed task frame before implementing launch.
