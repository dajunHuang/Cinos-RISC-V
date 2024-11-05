#include <sbi.h>

void hal_uart_init(void)
{

}

int hal_uart_getchar(void)
{
    return sbi_console_getchar();
}

int hal_uart_putchar(char c)
{
    sbi_console_putchar(c);
    return 0;
}