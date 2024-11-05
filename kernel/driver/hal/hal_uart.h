#ifndef __HAL_UART_H__
#define __HAL_UART_H__

void hal_uart_init(void);
int hal_uart_getchar(void);
int hal_uart_putchar(char c);
#endif