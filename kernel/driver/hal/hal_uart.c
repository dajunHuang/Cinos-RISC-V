#include <sbi.h>

void hal_uart_init(void)
{

}

int hal_uart_getchar(void)
{
    return 0;
}

int hal_uart_putchar(char c)
{
    sbi_dbcn_write_byte(c);
    return 0;
}