# Saved context base versus hardware return pointer

On 2026-10-07, after STMDB r0!, {r4-r11} was introduced, the learner correctly predicted that updating r0 does not automatically update PSP. They proposed keeping both addresses but recognized the combined base suffices because the saved size is known. The teacher refined this to knowing the layout: the hardware frame begins 32 bytes above the software-saved base in this simplified example.

Asked which address PSP should hold after software restores r4–r11, the learner initially answered "the flags." After distinguishing frame contents from its address with a two-block diagram, they correctly selected hardware-frame base 0x20000FE0 rather than combined base 0x20000FC0.

Guided frame-base selection is demonstrated. Independent reasoning about hardware restore offsets and actual exception return remain unverified. Next probe a concrete wrong-base restoration: hardware expects saved r0 at the frame base; at the software base it would instead encounter saved r4. Continue before implementing a full switch.
