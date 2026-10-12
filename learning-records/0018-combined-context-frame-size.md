# Combined context frame size

On 2026-10-07, given eight hardware-saved registers and eight software-saved registers (r4–r11), each four bytes, the learner correctly calculated a 64-byte combined frame. They independently computed saved SP = 0x20000FC0 from initial SP = 0x20001000, demonstrating downward stack arithmetic for the combined frame.

This is a simplified layout with no alignment padding or extra software-saved state. It does not establish knowledge of a complete production context layout, MSP/PSP selection, or EXC_RETURN handling.

Next: ask which task's saved SP must be selected to locate that task's context during restoration. Then introduce MSP/PSP and exception return in small steps using the Arm primary source before implementing switching.
