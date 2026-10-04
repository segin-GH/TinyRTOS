# Initial image contents versus runtime data

The learner explains startup as preparation of global data and correctly predicts that incrementing an initialized global from 7 produces 8 in RAM while its initial image value remains 7. Clarifications provided: the CPU executes the initialization before main, data is used rather than executed, placement is linker/platform-dependent, and function-local static variables also have static storage duration. Those clarifications need later retrieval checks; boot execution is still unverified.

Next move from guided traces to an experiment: have the learner add one explicitly initialized nonzero global and one implicitly zero-initialized global, then reproduce the build with debugging information and observe initialization using QEMU/GDB.
