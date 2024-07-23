#include <uart.h>
#include "autoconf.h"

void hal_uart_init(void)
{
    uart_init();
}

int hal_uart_getchar(void)
{
    return uart_receive_data();
}

int hal_uart_putchar(char c)
{
    return uart_send_data(c);
}