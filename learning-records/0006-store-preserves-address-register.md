# A store writes memory and preserves the address register

The learner initially believed str r3, [r1] replaces r1 with the copied value. With a concrete example, they correctly predicted that memory receives 99 while r1 remains 0x20000000. This corrects that misconception for the plain str instruction without writeback; broader addressing modes are not yet covered.

They also correctly predicted that an initialized global is modified in RAM, but confused _sidata with the RAM destination when asked to map symbols. Next, reconnect r0/_sidata and r1/_sdata using one concrete copy example; symbol mapping remains unverified.
