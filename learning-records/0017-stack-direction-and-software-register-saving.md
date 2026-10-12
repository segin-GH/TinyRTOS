# Stack direction and software register saving

On 2026-10-07, the learner initially predicted SP = 0x20001020 for eight 32-bit words saved from SP = 0x20001000. The teacher corrected the direction to subtraction and SP = 0x20000FE0. The learner then independently calculated 0x20000FDC for one additional four-byte push. Recheck the eight-word calculation later; the first answer used the wrong direction.

After being told hardware exception stacking does not save r4–r11, the learner initially proposed setting an unsaved register to zero. With a concrete case of task A holding r4 = 42 before B changes it to 99, they correctly identified 42 as the value to save, the stack as its storage location, and 42 as the value to restore. The teacher clarified that this is A's own stack. The concrete save/restore prediction is demonstrated; independent generalization to the full software-saved register group remains unverified.

Next: combine the eight hardware-saved words and eight software-saved r4–r11 words in a simplified frame-size prediction, with no alignment padding or extra software metadata. Actual context-switch implementation and exception-return mechanics remain unverified.
