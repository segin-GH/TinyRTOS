# TinyRTOS

A small real-time operating system for the MPS2 Cortex-M3 (QEMU `mps2-an385`),
built from scratch as a learning project. The goal is to progress from reset and
boot, through tasks, scheduling, and synchronization, to a port on STM32
hardware. See [MISSION.md](MISSION.md) and [LEARNING-PLAN.md](LEARNING-PLAN.md).

## Built with agents

This repository is developed using agent skills from
[mattpocock/skills](https://github.com/mattpocock/skills). Those skills drive the
learning loop: scoped lessons, predictions, experiments, and reviews, with the
learner writing the kernel and the agent guiding instead of handing over
finished implementations.

## Layout

- `rtos/` - kernel source, linker script, and build output.
- `lessons/` - guided investigations.
- `learning-records/` - evidence of demonstrated understanding.
- `reference/` - supporting reference material.
- `MISSION.md`, `LEARNING-PLAN.md`, `NOTES.md`, `RESOURCES.md` - project state and plan.
