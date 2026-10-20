# Local counter observation

On 2026-10-21, reviewed learner edits adding volatile local uint32_t counters initialized once before both task loops and incremented inside them. Learner rebuilt and supplied GDB output: A first stopped before its increment with count_a = 0; after disabling A's breakpoint, continuing, and interrupting execution, GDB stopped inside B's counter loop. Re-enabling A's breakpoint and continuing returned to A with count_a = 326080133. Two subsequent next commands stopped at A's increment with values 326080134 and 326080135.

This supports retention of A's local state during intervening B execution and verifies two consecutive increments. It does not comprehensively prove register preservation, stack isolation, or absence of counter wrap during the long free run. B's counter value has not yet been inspected. Next observe B's local counter at its loop breakpoint. Learner runs builds.

Before this exercise, learner correctly stated MRS reads a special register into a general register and MSR writes a general register value into a special register, after incorrect PSP-value predictions. Teacher explained independent copied values; independent writeback understanding remains to be revisited later.
