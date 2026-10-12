# Initial frame first three slots

On 2026-10-12, the learner created task_a_stack[64], task_a and task_exit loops, and a local construction pointer sp starting one past the array. Initially confused last element 63 with one-past 64 and used post-decrement in a way that would write out of bounds; corrected after guidance to pre-decrement. Correctly predicts next slot at index 62.

Current reviewed code places xPSR at 63, PC at 62 with task_a's converted address and bit 0 cleared, and LR at 61 with task_exit's converted function pointer retaining its Thumb marker. Learner explains assignment through pc writes the array without changing the pointer and computes 0x101 with bit 0 cleared as 256. Initially suggested OR for clearing; teacher supplied AND with ~1u. Independent bit-clear construction remains unverified.

Next fill hardware slots r12, r3, r2, r1, r0 below LR. Software frame, explicit eight-byte stack alignment, full build/frame inspection, PSP configuration and first-task launch remain pending. Frame construction is not task execution.
