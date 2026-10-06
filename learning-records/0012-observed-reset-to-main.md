# Observed startup initialization in QEMU/GDB

The learner reports rebuilding with debug information and connected GDB to paused QEMU. Their debugger transcript shows stepping from Reset_Handler into main at PC 0x88, then observing varx = 7 and vary = 0.

They observed the initial data word 7 at load address 0x90, its copy to varx at RAM address 0x20000000, and the BSS store of zero at 0x20000004. They correctly predicted pointer advances to 0x94 and 0x20000004 and that equality with the end boundary terminates the copy loop. They also correctly predicted _edata = 0x20000004 and checked &varx = 0x20000000.

The misconception that str r3, [r1] changes r1 resurfaced. After correction, they observed the memory value 7 while r1 retained 0x20000000; independent retrieval of this distinction should be revisited.

BL was explained as saving a return address in LR. The learner observed LR = 0x6d on entry to main, but understanding of return flow and Thumb bit 0 is not yet demonstrated. Next: inspect the instructions around call_main/hang and connect LR to the return destination; then consolidate startup responsibilities before progressing toward tasks.
