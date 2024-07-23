#include "hal_uart.h"

int getchar(void)
{
    return hal_uart_getchar();
}

int putchar(int c)
{
    return hal_uart_putchar(c);
}

int puts(const char *s)
{
    int i = 0;
    for (; s[i] != '\0'; i++) {
        putchar(s[i]);
    }
    putchar('\r');
    putchar('\n');
    return i;
}
