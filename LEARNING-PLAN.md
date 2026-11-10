# Build TinyRTOS by explaining it

Build your own RTOS for MPS2 Cortex-M3, from reset to executing tasks and coordinating them. You write the implementation; I guide experiments and review your reasoning. Progress is based on evidence, not a fixed number of weeks. See [MISSION.md](MISSION.md).

Working lab: QEMU `mps2-an385`, supported by the installed QEMU and identified as Cortex-M3 in [QEMU's MPS2 documentation](https://www.qemu.org/docs/master/system/arm/mps2.html). All milestones use this emulator.

## Current project

Boot, first-task launch, and repeated SysTick/PendSV preemption have been observed in QEMU/GDB. Sleep is complete by learner report. The learner has implemented a one-waiter counting semaphore, and runtime checks are pending.

The active lesson is [verifying the counting semaphore in GDB](lessons/0015-verify-counting-semaphore.html). The [printk lesson](lessons/0014-first-printk.html) is queued for bring-up and diagnostics.

## Ranked milestones

| Rank | Problem to solve | Evidence to move on |
|---|---|---|
| 1. Finish the current semaphore | Define and verify a bounded counting semaphore with one waiter, task callers, and static lifetime. Make the capacity contract explicit. | Predict and capture empty take, give/wake/retry, stored token, and saturation at capacity 3. Explain the count, waiter, task state, and scheduler decision at each boundary. |
| 2. Make builds and tests repeatable | Create reproducible debug and release builds. Turn the semaphore cases into automated QEMU tests with a clear pass/fail result and a host timeout for hangs. Add tests for boot, context preservation, sleep, and idle as part of this baseline. | One command reruns the suite. An intentional failure and an intentional hang both fail the run. Save the release ELF/map as the first size baseline. |
| 3. Track tasks and make scheduling predictable | Replace the hard-coded A/B choice with a bounded static task registry. Define task IDs, stack bounds, eligibility, wait reasons, and task return behavior. Specify scheduling order and tick boundaries before adding policy variants. | GDB can explain what every task is waiting on. Tests cover several tasks, an empty ready set, task return, and tick wrap where applicable. |
| 4. Make failures observable | Add the UART boot console, assertions, a fault snapshot, and stack usage checks. Use a stack high-water mark to estimate peak stack used in the exercised workload. Add optional counters for switches and runtime as needed. | A deliberately triggered fault identifies the task and fault location. A deliberately small stack exercises the detection path. Measure the cost of enabled diagnostics. |
| 5. Add progress monitoring and watchdog recovery | Give critical tasks a way to report useful progress. A watchdog resets the device if it is left unfed. Refresh it only when the health policy is satisfied, with explicit expectations for tasks that legitimately block. | A deliberately stuck critical task triggers the emulated CMSDK watchdog and the guest restarts. Capture the reset in the QEMU test harness. Healthy tasks, including expected waits, run without false resets. |
| 6. Extend synchronization for the workload | Add multiple semaphore waiters and timeouts when required. Add fixed priorities and mutex ownership for shared resources, then test priority inversion. Add bounded message queues when tasks need to exchange data. | Tests demonstrate waiter order, timeout/give races, mutex contention, and queue full/empty behavior for the features selected. |
| 7. Tune and qualify the release | Run long workloads and inject failures. Compare build and algorithm choices against the same functional suite, map, and emulated instruction counts on fixed workloads. | The selected release meets explicit budgets, passes regressions, and has a documented recovery and debugging procedure. |

Keep size and timing visible from the first repeatable build. Compare loadable flash and static RAM from the map and section sizes, per-task stack use separately, and relative execution cost under a fixed QEMU configuration. Use fixed-capacity storage with a known memory cost. Try size-oriented compiler settings and dead-code removal one change at a time. Change scheduler structures only when measurement shows where the cost is. Keep advanced scheduling policies for a workload with a demonstrated need.

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

## Release evidence in QEMU

Use the emulated [CMSDK watchdog](https://github.com/qemu/qemu/blob/master/hw/arm/mps2.c) to test recovery. Record the QEMU version, machine, and test configuration so results can be reproduced. Use instruction counts to compare execution cost and guest ticks to check timer behavior. Physical interrupt latency and cycle budgets require measurements on a device. [QEMU instruction counting](https://www.qemu.org/docs/master/devel/tcg-icount.html)

## Resume across sessions

At the end of each session, update NOTES.md with the current milestone, your last observation, unresolved question, and next experiment. Add a learning record only when you demonstrate understanding. At the next session, read these files and the current code before choosing an exercise. Do not advance merely because a demo runs: you should predict and explain its behavior.

Current checkpoint (2026-11-09). Verify the existing one-waiter counting semaphore in GDB before starting the console. The demo has capacity 1. Use a controlled capacity-3 scenario for saturation.

## How our sessions work

1. Read the full problem statement with scope, behavioral contract, integration points, and acceptance cases.
2. Predict the state changes before building or running the experiment.
3. Run the build yourself and use the debugger to find the first observation that differs from your prediction.
4. Share the smallest reproduction, the expected and observed values, and the stop location. Review starts with that evidence. Implementation hints are available on request.
5. Once the behavior is understood, turn the trace into a regression where practical.

On your next visit, recall an earlier concept before rereading. Later exercises mix already-practiced concepts. Learning records capture only understanding you demonstrate.

Start with [the boot investigation](lessons/0001-investigate-boot.html). The first lesson diagnoses prerequisites; it does not assume you already understand assembly.
