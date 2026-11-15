# Observed mutex reacquisition and alternation

The learner implemented a task-owned non-blocking mutex, guarded the protected code on successful acquisition, and showed QEMU output in which B repeatedly acquired after A's first acquisition. The learner added a pause after each unlock and obtained sustained A/B alternation, demonstrating how the callers can create opportunities for each other to acquire. The deliberate non-owner release and interrupt-mask runtime checks are still open.
