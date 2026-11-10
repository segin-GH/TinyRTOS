# Observed the first UART byte

The learner passed the address of a `uint8_t` containing `B` to the UART transmit function. Their CMake output showed `uart.c` compiling and `kernel.elf` linking, and QEMU displayed `B` on the terminal. This verifies the boot-time path from `main()` through UART0 to the host terminal for one byte. Next build the string writer on that path.
