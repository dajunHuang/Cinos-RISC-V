#include <uart.h>

static volatile struct uart_regs_t *uart1 = (struct uart_regs_t *)DEVICE_VBASE_UART;

#define FR_RXFE    (1u << 4)
#define FR_TXFF    (1u << 5)

void uart_init(void)
{

}

int uart_receive_data(void)
{
    while (uart1->FR & FR_RXFE);
    return uart1->DR & 0xff;
}

int uart_send_data(char c)
{
    while (uart1->FR & FR_TXFF);
    uart1->DR = c;
    return (int)c;
}
