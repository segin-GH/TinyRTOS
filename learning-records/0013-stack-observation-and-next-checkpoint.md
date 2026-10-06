# Stack observation and context-switching checkpoint

The learner observed main's initial push of r7 move SP from 0x20400000 to 0x203ffffc. Memory at the new SP contained the saved old r7 value 0, while current r7 became 0x203ffffc after add r7, sp, #0. They identified SP as holding an address rather than the saved value and correctly computed a later four-byte downward step. Stack arithmetic and register-versus-memory distinctions still benefit from retrieval practice.

After adding int var = 1 inside the while loop, their disassembly showed push {r7}, sub sp, #12, add r7, sp, #0, then movs r3, #1 and str r3, [r7, #4]. They observed SP and r7 at 0x203ffff0. Explained that the local uses four bytes at 0x203ffff4, that the compiler allocates additional frame space, and that initialization repeats using the same space because the declaration is inside the loop. These explanations have not yet been independently demonstrated. A uint32_t comparison was suggested but has not been reported completed.

The learner requested returning to the RTOS goal. Next teaching question introduces context preservation: task A has r0 = 10, r1 = 20, PC at its next instruction, and SP at its current stack position; task B runs and changes those registers. What goes wrong if task A resumes without restoring its register values? The learner has not answered yet. Do not infer mastery of context switching or advance to its implementation.

Session paused at the learner's request on 2026-10-06. Resume with the pending question, keep the scope tied to RTOS task switching, and provide one small question at a time. Build/boot and global initialization are verified by the previous debugger transcript.
