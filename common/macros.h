#ifndef _MACROS_H_
#define _MACROS_H_

#include "os_def.h"
#ifdef CONFIG_KERNEL
#include <k_assert.h>
#include <k_stdint.h>
#else
#include <assert.h>
#include <stdint.h>
#endif

#ifdef container_of
#undef container_of
#endif
#define container_of(p, type, member) ((type *)((unsigned long)(p) - (unsigned long)(&((type *)0)->member)))

#define likely(x)               (x)
#define unlikely(x)             (x)

#define bitmask(x)              (1ul << (x))
#define lowbitsmask(x)          (bitmask(x) - 1ul)
#define align_to(size, align)   ((((size) + (align)-1) / (align)) * (align))

#define BOOTONLY                __attribute__((section(".boot")))
#define BOOTDATA                __attribute__((section(".boot.data")))
#define BOOTPHYSIC              __attribute__((section(".boot.physic")))

#define DEFAULT_ALINMENT        OS_ALIGNED(8)

// for hardware registers defination
#define REG32_RW(addr)          (*(volatile uint32_t *)(addr))
#define REG32_RO(addr)          (*(const volatile uint32_t *)(addr))
#define REG32_WO(addr)          REG32_RW(addr)
#define REG32s_RW(addr)         ((volatile uint32_t *)(addr))
#define REG32s_RO(addr)         ((const volatile uint32_t *)(addr))
#define REG32s_WO(addr)         REG32s_RW(addr)

static inline unsigned long bitfield_get(unsigned long value, unsigned int begin, unsigned int width)
{
    assert(width > 0 && begin < (sizeof(unsigned long) * 8 - 1));
    return (value >> begin) & lowbitsmask(width);
}

static inline unsigned long bitfield_clean(unsigned long value, unsigned int begin, unsigned int width)
{
    assert(width > 0 && begin < (sizeof(unsigned long) * 8 - 1));
    value &= ~(lowbitsmask(width) << begin);
    return value;
}

static inline unsigned long bitfield_set(unsigned long value, unsigned int begin, unsigned int width, unsigned int bv)
{
    assert(bv < lowbitsmask(width));
    value = bitfield_clean(value, begin, width);
    value |= bv << begin;
    return value;
}

#endif
