# Cross-build the kernel with CMake

The learner moved the CMake project to `rtos/`, configured it with the ARM toolchain, and built the kernel. Their configure output showed `/usr/bin/arm-none-eabi-gcc` for C and assembly, and inspection confirmed `rtos/build/kernel.elf` exists. The learner identified `build/` as the location of the generated output, so the UART lesson can use that ELF for QEMU and GDB.
