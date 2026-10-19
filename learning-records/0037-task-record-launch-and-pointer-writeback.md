# Task record launch and register writeback

On 2026-10-19, the learner identified `sp` as the address of the saved r4 slot, stored it in a file-scope `struct task` record, and changed the launch handler to read that record. They correctly predicted that `ldmia r0!` updates only r0, not the saved pointer in RAM; their GDB trace confirmed r0 advancing from 0x200000c8 to 0x200000e8 while task_a_record.saved_sp stayed 0x200000c8.

The learner rebuilt and observed exception return reaching task_a's first instruction with SP = 0x20000108, equal to &task_a_stack[64]. Record-based first launch is verified; selecting through a task pointer, a second task, outgoing context saving, and cooperative switching remain unimplemented and unverified.
