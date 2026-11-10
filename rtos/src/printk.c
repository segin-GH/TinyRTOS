#include "printk.h"
#include "hal/uart/uart.h"

void printk(const char *msg)
{
    for (;;)
    {
        if (*msg == '\0')
            return;

        uart_tx((uint8_t *)msg);
        msg++;
    }
}
