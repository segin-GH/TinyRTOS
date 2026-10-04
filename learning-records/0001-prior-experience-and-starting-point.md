# Prior RTOS experience and starting point

The user reports four years of embedded engineering experience and use of FreeRTOS and Zephyr. They explicitly report uncertainty about context preservation, boot vector entries, and priority inversion; prior API exposure should not be treated as kernel-internals mastery.

Their diagnostic answers identify starvation under a continuously runnable higher-priority task, exclusive bus access as a mutex use case, and queue overload with possible capacity or admission responses. Their time-slicing claim needs investigation, and interrupt event signaling has not yet been assessed. Start with a short scheduling prediction before progressing to CPU state and boot.
