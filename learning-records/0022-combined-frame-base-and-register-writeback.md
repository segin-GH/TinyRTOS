# Combined frame base and register writeback

On 2026-10-07, the learner correctly stated that MRS r0, PSP does not save r4–r11. Asked what r0 holds after an unspecified save, they answered the same location; the teacher acknowledged this is possible without writeback and clarified the intended question as the address calculation.

The learner independently computed 0x20000FC0 as 32 bytes below hardware-frame base 0x20000FE0. They initially identified the unchanged hardware-frame address as pointing to the combined context. After a two-block memory diagram, they correctly selected 0x20000FC0 for the task record and explained that known length permits locating the rest of the frame.

This supports guided understanding of frame base and offsets, not independent mastery of restore instructions. Keep fixed layout and saved ordering explicit: in this example software registers occupy 32 bytes followed by the hardware frame. The pointer calculation and whether an instruction updates a register are distinct.

Next introduce STMDB r0!, {r4-r11}, including decrement-before and writeback. Probe whether changing the copied address in r0 also changes PSP; MRS copies a value rather than creating an alias. No completed context-switch implementation is authorized by the teaching preferences.
