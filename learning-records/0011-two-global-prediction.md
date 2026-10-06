# Predicting the two globals at main

The learner added file-scope `int varx = 7;` and `int vary;` to `rtos/src/main.c`, and correctly predicted values 7 and 0 on entry to main. They recalled the data-copy loop and the initial value's image location in the linker's FLASH region. These predictions have not yet been verified in execution.

Next: rebuild with debug information, then observe reset-to-main in QEMU/GDB. Keep steps small and have the learner run the commands.
