# Cooperative limit and timer recall

On 2026-10-20, the learner correctly predicted that B would never run again after a non-yielding A is selected by the current cooperative kernel. They suggested a timer as the mechanism for regaining control.

When asked whose context to save after interrupting A, the learner initially answered B. After correction, they recognized that running B before preserving A could corrupt A's register value, and independently recalled r4–r11 as the software-saved registers. Correct outgoing-task identification needs a later independent recheck.

Prepared lesson 0010 on locating the SysTick vector. No timer configuration, new handler, preemption implementation, or runtime observation has been demonstrated. Next identify vector index 15 in startup.S, then introduce a dedicated handler and timer configuration in small steps. Learner runs builds.
