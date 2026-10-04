# Build TinyRTOS by explaining it

Build your own RTOS for MPS2 Cortex-M3, from reset to executing tasks and coordinating them. You write the implementation; I guide experiments and review your reasoning. Progress is based on evidence, not a fixed number of weeks. See [MISSION.md](MISSION.md).

Working lab: QEMU `mps2-an385`, supported by the installed QEMU and identified as Cortex-M3 in [QEMU's MPS2 documentation](https://www.qemu.org/docs/master/system/arm/mps2.html). If you mean physical MPS2 hardware or AN511, adjust the lab before the first experiment.

## Current project

- `rtos/src/startup.S`: Cortex-M3 vector table and reset path with data-copy and BSS-clear loops.
- `rtos/linker.ld`: regions named FLASH/RAM, section placement, and startup symbols; declares 4 MiB per region. Validate addresses and actual memory types against AN385; region names alone do not establish hardware behavior.
- `rtos/src/main.c`: empty infinite loop.
- Object files and `kernel.elf` exist; that does not prove they match the current source or boot successfully.
- No build recipe, target selection, debugger procedure, task abstraction, scheduler, or synchronization code was found.
- ARM GCC, readelf, and QEMU are available. `arm-none-eabi-gdb` was not found on PATH; other debugger availability has not been checked.

## Milestones

| Step | Question to investigate | Your experiment | Evidence to move on |
|---|---|---|---|
| 0. Establish the lab | How do source files become a running MPS2 program? | Document a reproducible build and QEMU/debug procedure; inspect ELF entry and sections. | A fresh build reaches main; you reconcile the linker map with AN385 and QEMU documentation. |
| 1. Explain boot | What must be true before C runs? | Trace reset; inspect one initialized global and one zero-initialized global. | Explain their load/run addresses and show their values before and after startup. |
| 2. Understand execution state | What would let a paused function resume correctly? | Trace nested calls, local variables, registers, and the stack. | Draw the required saved state and justify each part. |
| 3. Exceptions as groundwork | How does the CPU leave and return to interrupted code? | Investigate Thread/Handler modes, MSP/PSP, exception frames, and exception return with a small handler. | Annotate a captured stack frame and explain the return path. |
| 4. Execute the first task | How can a task begin on its own stack? | Design a minimal task record, stack layout, and launch path; investigate SVC as a launch mechanism. | A task runs on its intended stack; explain entry, argument delivery, and what happens if it returns. |
| 5. Cooperative switching | How can two tasks take turns voluntarily? | Sketch two tasks and a yield trace; attempt a minimal context switch using the exception groundwork. | Each task resumes where expected, preserving distinct local state and registers. |
| 6. Scheduling policies | Who should run next, and why? | Hand-simulate FIFO, round-robin, and fixed-priority policies before coding policy variants. | Predict traces including equal priorities, starvation, and an empty ready set. |
| 7. Interrupts and preemption | What changes if a task does not yield? | Study exception entry/return, SysTick, and PendSV; compare predictions with debugger traces. | CPU-bound tasks can be interrupted and resume with intact state. |
| 8. Time and blocking | What makes a task eligible to run? | Design ready/running/blocked transitions, sleep, wakeups, and an idle task. | Sleeping tasks consume no scheduled execution; reason through wakeup and timer-wrap boundaries. |
| 9. Critical sections | How can an interrupt break a shared update? | Construct a harmful interleaving, then attempt a bounded protection strategy. | Explain atomicity, interrupt masking, and why protected regions must be short. |
| 10. Semaphores | How should an event or available resource wake a waiter? | Design binary/counting behavior and draw wait/wake transitions. | Handle event-before-wait, multiple waiters, and timeout-versus-signal races. |
| 11. Mutexes | What does resource ownership add? | Create contention, deadlock, and a three-task priority-inversion trace; then explore inheritance. | Explain ownership, effective priority, release, and inheritance limitations. |
| 12. Message queues | Where does a message live while its receiver waits? | Build a bounded producer/consumer queue with deliberate full/empty cases. | Explain data lifetime, ordering, blocking, and timeout behavior. |
| 13. Workers and work queues | Who executes deferred work, and when? | Use a worker task to process queued jobs; stress it with arrivals faster than service. | Explain queue capacity, backpressure, job lifetime, and long-job effects. |
| 14. Real-time scheduling | Will work finish before its deadline? | Compare fixed-priority/rate-monotonic and earliest-deadline-first traces in a simulator before kernel integration. | State workload assumptions, identify missed deadlines, and distinguish timing evidence from guarantees. |
| 15. Integrate | Can the system withstand awkward timing? | Combine a periodic task, event producer, and worker; add fault and stack diagnostics. | Reproduce behavior and explain failures with traces, not guesses. |

Split every milestone into small lessons. Start with two tasks and fixed storage; revisit allocation and optimizations when a real limitation motivates them.

## Sessions before the first task

Each session targets one observable result, usually within 30–60 minutes; split further whenever assembly or tooling needs more time.

1. **Build and inspect:** reproduce the ELF from source; identify entry address and memory sections.
2. **Reset and vectors:** stop at reset and trace how execution reaches startup.
3. **Memory initialization:** inspect initialized and zero-initialized globals across startup; validate linker symbols.
4. **Calls and stacks:** trace a nested C call; explain stack pointer, return address, and register roles.
5. **Exception entry and return:** capture a frame and account for what hardware preserves versus what software must preserve.
6. **Task design:** draw a task record and private stack; state lifetime and alignment requirements before writing code.
7. **First-task launch:** implement and debug your launch path; demonstrate a task running on its own stack.

These are starting estimates, not a promise of seven sessions. An unresolved prerequisite becomes the next small lesson.

## Skills developed inside the kernel

These are explicit learning goals, practiced alongside each milestone rather than postponed until the RTOS is complete. Diagnose prerequisites with a small exercise before each new use.

| Skill | Where we practice it | Evidence of understanding |
|---|---|---|
| Bit manipulation | Masks, shifts, field extraction, register configuration, interrupt controls, and later ready-priority bitmaps. | Predict exact bit patterns; preserve unrelated fields; reason about integer widths, signedness, shift boundaries, and hardware register semantics. |
| Data structures | Fixed task arrays, ready/wait lists, bounded ring buffers, and timer structures; later compare lists, bitmaps, and heaps where useful. | Draw state changes, implement operations, explain invariants, and handle empty/full/removal cases without corruption. |
| Algorithms | Task selection, queue operations, wakeup ordering, and deadline selection. | Explain worst-case time and memory costs using task/waiter counts; compare alternatives before choosing one. |
| Bare-metal programming | Reset, linker sections, ABI, stacks, memory-mapped I/O, interrupts, timers, and fault diagnosis. | Connect C and assembly to disassembly and observed register/memory state; use device documentation to justify each configuration. |

For each implementation, answer: what invariant must hold, what happens at the boundary, and what is the worst-case cost? Explain why volatile, atomicity, and interrupt protection address different questions when they arise.

Add short retrieval exercises using earlier bit operations and structures in later milestones. No standalone DSA syllabus or solved implementation is required; choose exercises that serve the kernel being built.

## Final milestone: port to STM32 hardware

The user's final goal is an STMicroelectronics microcontroller port; STM32 is the working interpretation, with the exact board and CPU core pending. MPS2 remains the initial learning target.

During development, identify three responsibilities as they arise: generic kernel policy/data structures, CPU-specific context switching and exception handling, and board-specific startup/memory/peripherals. Keep their boundaries understandable without building an elaborate portability framework upfront.

After the kernel works on MPS2:

1. Select the exact MCU/board and gather its reference manual, core documentation, memory map, and debug procedure.
2. Compare its core and ABI with the MPS2 port. Investigate differences such as floating-point context only if the selected device and build use them.
3. Adapt startup, vector table, linker regions, clock setup, tick configuration, interrupt priorities, and the observation channel.
4. Repeat reset-to-main and first-task investigations on hardware before enabling multitasking.
5. Verify context preservation, scheduling, sleep, synchronization, and queue behavior with reproducible traces.
6. Measure hardware timing and inspect stack/fault behavior; treat emulator observations as functional evidence rather than hardware timing guarantees.

Completion evidence: a reproducible hardware build, documented flashing/debugging workflow, first-task and multi-task demonstrations, and an explanation of what changed and why. Board purchasing, flashing, and hardware access will be planned once the target is known.

## Resume across sessions

At the end of each session, update NOTES.md with the current milestone, your last observation, unresolved question, and next experiment. Add a learning record only when you demonstrate understanding. At the next session, read these files and the current code before choosing an exercise. Do not advance merely because a demo runs: you should predict and explain its behavior.

Current checkpoint (2026-10-05): paused after guided startup-code investigation. Learner has traced memory stores, pointer increments, the data-copy boundary, and distinguished initial image data from runtime RAM values. Next session: brief recall, inspect/add two globals, reproduce the build with debug information, and observe initialization on MPS2 in QEMU/GDB. Build, boot, memory-map validation, and task launch remain unverified. See NOTES.md and learning-records for evidence and remaining gaps. The earlier scheduling diagnostic is deferred until scheduling work.

## How our sessions work

1. Recall one idea from the previous session without notes.
2. Predict one narrowly scoped behavior and explain why.
3. Make your own implementation or debugger experiment.
4. Compare observed behavior with the prediction; send your trace or code here.
5. Receive questions and one hint at a time, then revise your explanation.

On your next visit, recall an earlier concept before rereading. Later exercises mix already-practiced concepts. Learning records capture only understanding you demonstrate.

Start with [the boot investigation](lessons/0001-investigate-boot.html). The first lesson diagnoses prerequisites; it does not assume you already understand assembly.
