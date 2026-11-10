#ifndef UART_H
#define UART_H

#include <stdint.h>

typedef struct
{
    uint32_t baud;
    uint8_t uart_isnt;
} uart_t;

int uart_init(uart_t *uart);
int uart_deinit(uart_t *uart);

int uart_tx(uint8_t *buf, uint32_t size);
int uart_rx(uint8_t *buf, uint32_t size);

#endif
