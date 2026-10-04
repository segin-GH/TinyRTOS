# Mission: Build TinyRTOS from scratch

## Why
Build my own RTOS for MPS2 Cortex-M3, learning how each part works by implementing and investigating it myself. Use the existing TinyRTOS project to progress from reset and boot to executing tasks, scheduling them, and coordinating their work.
Use this project to strengthen bit manipulation, data structures and algorithms, and bare-metal programming through practical kernel work.
The final goal is to port the RTOS to an STMicroelectronics microcontroller, provisionally STM32, and demonstrate it on real hardware. The exact device is still to be selected.

## Success looks like
- Explain and demonstrate the path from reset to the first task.
- Implement context switching and several scheduling policies, and predict their execution traces.
- Implement and explain blocking, semaphores, mutexes, message queues, and workers.
- Diagnose failures using registers, memory, and task traces rather than copying a finished kernel.
- Manipulate register fields safely, choose and implement kernel data structures, and explain their time and memory costs.
- Build and debug bare-metal code using linker maps, disassembly, memory-mapped peripherals, and interrupts.
- Port the kernel from the MPS2 learning target to the selected STM32 and explain each architecture and board-specific adaptation.

## Constraints
- Learning spans multiple sessions; preserve progress in this workspace.
- Four years of embedded engineering and FreeRTOS/Zephyr experience; kernel internals need foundational investigation.
- User writes the kernel. Teacher provides scoped exercises, questions, sources, hints, and reviews without completed solutions.
- Target: MPS2 Cortex-M3. Use QEMU mps2-an385 as the working lab assumption; confirm if physical hardware or AN511 is intended.

## Out of scope
- Adopting an existing RTOS as the implementation.
- Production certification, multicore support, and advanced optimization in the initial course.
