# Observed SVC return to main

On 2026-10-14, the learner added SVC_Handler in startup.S, routed vector entry 11 to it, built the image themselves, and stopped there using GDB. Initially the handler branched to itself; learner observed repeated stops at the same instruction. After replacing the branch with bx lr, learner rebuilt and supplied a trace: x/i $pc showed bx lr at SVC_Handler (0x88), and stepi returned to main.c:69 (int var = 1). Learner explicitly recognized the return to main. Live handler LR had been observed as 0xfffffff9.

During this session, learner requested foundational GDB explanation. Practiced distinguishing a RAM address from its contents with x/1wx, examining SP with info registers, locating stacked PC with x/1wx, and examining the instruction at the saved PC with x/i. Supplied dumps connected main's saved PC to its post-SVC instruction and the prepared task's saved PC to task_a. Code addresses changed on rebuild; use symbols or current image observations rather than earlier numeric addresses.

Observed exception return uses main's existing MSP frame. No PSP configuration, software r4-r11 restoration, or task launch has occurred. Next guide first-task launch in small steps, explaining stack selection and the handler's live EXC_RETURN separately from the task's stacked LR. Learner builds code; agent reviews source and supplied observations.
