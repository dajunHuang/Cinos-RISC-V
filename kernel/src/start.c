#include "hal_uart.h"
#include "config.h"

void start(void)
{


	while (1) {
		char c = hal_uart_getchar();
		hal_uart_putchar('-');
		hal_uart_putchar(c);
	};
}
