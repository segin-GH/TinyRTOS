# RTOS Resources

## Knowledge

- [GNU linker manual: Output Section LMA](https://sourceware.org/binutils/docs/ld/Output-Section-LMA.html)
  Primary reference for load versus runtime addresses, AT/AT>, and startup copy/zero loops. Use with the two-global initialization experiment.

- [Arm Cortex-M3 Devices Generic User Guide](https://documentation-service.arm.com/static/5ea823e69931941038df1af5)
  Primary architecture reference for the vector table, stack pointers, exceptions, SysTick, and PendSV. Read the relevant section after making a prediction; do not read the entire manual upfront.
- [QEMU Stellaris board documentation](https://www.qemu.org/docs/master/system/arm/stellaris.html)
  Comparison only; this course now targets MPS2 rather than Stellaris.
- [QEMU MPS2 board documentation](https://www.qemu.org/docs/master/system/arm/mps2.html)
  Identifies mps2-an385 as Cortex-M3/AN385 and documents emulator differences from hardware. Primary lab reference; obtain the linked application-note identity's Arm memory-map documentation before changing the linker.
- [FreeRTOS RTOS fundamentals](https://www.freertos.org/Documentation/01-FreeRTOS-quick-start/01-Beginners-guide/01-RTOS-fundamentals)
  Primary project documentation for scheduling and real-time motivation. Compare concepts after designing your own behavior.
- [FreeRTOS queues](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues-mutexes-and-semaphores/01-Queues)
  Reference for communication and blocking behavior. Save for the queue milestone.
- [FreeRTOS mutexes](https://freertos.org/Real-time-embedded-RTOS-mutexes.html)
  Reference for FreeRTOS ownership-related synchronization and priority inheritance; distinguish its implementation choices from universal requirements.

## Wisdom (Communities)

- [FreeRTOS Community Forums](https://forums.freertos.org/)
  Kernel maintainers and users discuss scheduling and synchronization edge cases. Optional: bring a minimal trace and your reasoning when seeking critique; no posting is authorized.

## Gaps

- Fetch Arm AN385 for the board memory map; establish the debugger workflow in the first session.
- Add primary sources on rate-monotonic and earliest-deadline-first analysis when reaching that milestone.
