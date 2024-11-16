#include "hal_uart.h"
#include "config.h"

void start(void)
{


	while (1) {
		hal_uart_putchar('-');
		hal_uart_putchar('c');
	};
}
