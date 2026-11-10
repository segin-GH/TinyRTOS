#include "uart.h"
#include <stdint.h>

volatile uint32_t *uart0_data = (volatile uint32_t *)0x40004000;
volatile uint32_t *uart0_state = (volatile uint32_t *)0x40004004;
volatile uint32_t *uart0_ctrl = (volatile uint32_t *)0x40004008;
volatile uint32_t *uart0_intstatus = (volatile uint32_t *)0x4000400C;
volatile uint32_t *uart0_baudiv = (volatile uint32_t *)0x40004010;

int uart_init(uart_t *uart)
{
    volatile uint32_t baud = 25000000U / uart->baud;
    *uart0_baudiv = baud;

    return 0;
}

int uart_deinit(uart_t *uart)
{
    return 0;
}

int uart_tx(uint8_t *buf, uint32_t size)
{
    *uart0_ctrl = 1U;

    for (;;)
    {
        uint32_t cur_state = 1;
        cur_state = *uart0_state & 0x01;

        if (cur_state == 0)
            break;
    }

    *uart0_data = *buf;
    return 0;
}

int uart_rx(uint8_t *buf, uint32_t size)
{
    return 0;
}
