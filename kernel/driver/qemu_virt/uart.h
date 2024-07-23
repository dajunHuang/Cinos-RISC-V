#ifndef UART_H
#define UART_H

#include "device.h"
#include "k_stdint.h"
#include "macros.h"

struct uart_regs_t {
    uint32_t DR;               // 0x000 Data Register
    uint32_t RSR;              // 0x004 Receive Status Register
    uint32_t reserve[4];       // 0x008 ~ 0x014
    uint32_t FR;               // 0x018 Flag Register
    uint32_t reserve1;         // 0x01C
    uint32_t ILPR;             // 0x020 IrDA Low-power Counter Register
    uint32_t IBRD;             // 0x024 Integer Baud Rate Register
    uint32_t FBRD;             // 0x028 Fractional Baud Rate Register
    uint32_t LCR_H;            // 0x02C Line Control Register  
    uint32_t CR;               // 0x030 Control Register   
    uint32_t IFLS;             // 0x034 Interrupt FIFO Level Select Register
    uint32_t IMSC;             // 0x038 Interrupt Mask Set/Clear Register   
    uint32_t RIS;              // 0x03C Raw Interrupt Status Register
    uint32_t MIS;              // 0x040 Masked Interrupt Status Register 
    uint32_t ICR;              // 0x044 Interrupt Clear Register
    uint32_t DMACR;            // 0x048 DMA Control Register
};


void uart_init(void);
int uart_receive_data(void);
int uart_send_data(char c);
#endif
