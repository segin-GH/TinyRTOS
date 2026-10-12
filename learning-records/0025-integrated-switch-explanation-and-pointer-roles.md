# Integrated switch explanation and pointer roles

On 2026-10-07, the learner independently summarized an A-to-B switch as tracking both task stacks, saving A's registers, dividing saving between hardware and software, and loading B's registers so B can execute. They correctly recalled software saving r4–r11 but said hardware saves PSP. The teacher corrected this: hardware uses the active PSP to write its eight-word frame, while the RTOS records the combined saved-context address in the task record.

Asked to distinguish PSP from saved PC, the learner described PSP as the process stack pointer associated with the hardware frame and PC as the program counter associated with what executes. Clarify wording: PSP holds an address into stack memory; the memory holds the frame. Saved PC holds the resume instruction address, not the instructions themselves.

The integrated response supports a broad save/restore model but did not independently supply the full restoration sequence or exception-return mechanics. Revisit the hardware saves PSP misconception after spacing. Next introduce EXC_RETURN and why exception return restores the hardware frame rather than behaving like an ordinary function return. Retain one question at a time and user-written implementation.
