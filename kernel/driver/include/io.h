#ifndef _IO_H_
#define _IO_H_

#include <k_stdint.h>

#define readb(addr) (*(volatile unsigned char *)(uintptr_t)(addr))
#define readw(addr) (*(volatile unsigned short *)(uintptr_t)(addr))
#define readl(addr) (*(volatile unsigned int *)(uintptr_t)(addr))
#define readq(addr) (*(volatile unsigned long long *)(uintptr_t)(addr))

#define writeb(b, addr) (*(volatile unsigned char *)(addr) = (b))
#define writew(b, addr) (*(volatile unsigned short *)(addr) = (b))
#define writel(b, addr) (*(volatile unsigned int *)(addr) = (b))
#define writeq(b, addr) (*(volatile unsigned long long *)(addr) = (b))

#endif
