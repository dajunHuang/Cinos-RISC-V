#ifndef CONFIG_H
#define CONFIG_H

#include "autoconf.h"
#include "default_config.h"

#define __CHAR_UNSIGNED__    1
#define CONFIG_TIME_EXTENDED (1)

#define MMU_ENABLE
#define JUMP_EL0

#define CONFIG_RS_STACK_SIZE          (CONFIG_RS_STACK_PAGES << CONFIG_PAGE_SHIFT)
#define CONFIG_INIT_SI_PAGES          (CONFIG_RS_STACK_PAGES + 1)
#define CONFIG_MIN_STACK_PAGES        (CONFIG_STACK_PAGES)
#define CONFIG_MAX_STACK_PAGES        (512)

// 初始页表个数（递增，不回收）
#define LNPTALLKS                     50

// 2^8 slots for capability in initial root task
#define CONFIG_GUARDBITS              (24)
#define CONFIG_GUARDLENBITS           (8)
#define CONFIG_RADIXBITS              (4)
#define CONFIG_RADIXBASE              (8)

#define CONFIG_INITIAL_CNODE_GUARDLEN (8)
#define CONFIG_INITIAL_CNODE_RADIX    (16)
#define CONFIG_INITIAL_CNODE_COUNT    (1 << CONFIG_INITIAL_CNODE_RADIX)
#define CONFIG_ELF_CNODE_GUARDLEN     (8)
#define CONFIG_ELF_CNODE_RADIX        (8)
#define CONFIG_ELF_CNODE_COUNT        (1 << CONFIG_ELF_CNODE_RADIX)

#define CONFIG_KERNEL_RS_SIZE         (0x0f000000)   // 这块要不要加入autoconf
#define CONFIG_ELF_VBASE_SIZE         (0x10000000)   // 这块要不要加入autoconf
#define CONFIG_KERNEL_SIZE            (0x01000000)
#define CONFIG_RSIPC_SIZE             (CONFIG_INIT_SI_PAGES << CONFIG_PAGE_SHIFT)
#define CONFIG_RS_SIZE                (CONFIG_KERNEL_RS_SIZE - CONFIG_RSIPC_SIZE - CONFIG_KERNEL_SIZE)
#define CONFIG_RSIPC_RS_VBASE         (CONFIG_RS_VBASE + CONFIG_RS_SIZE)

//                          vbase                                                      .
#define CONFIG_DEV_RS_VBASE           (0x10000000)
#define CONFIG_DEV_RS_SIZE            (0x10000000)
#define CONFIG_ELF_VBASE              (0x20000000)

#define CONFIG_UHEAP_RS_VBASE         (0x200000000L)   // 用户堆，rootserver下是固定偏移，elf里动态分配虚拟地址
// 这个地址向前延伸是rootserver启动线程的用户态资源
#define CONFIG_ELF_UHEAP_SIZE         (0x800000)   // elf只能分配到有限的堆虚拟地址

// 用户态
// 0xFFFF000000000000                                                                            .
// 内核态
#define CONFIG_DEV_KERNEL_VBASE       (0xFFFF000010000000L)   // kernel load address and execution address
#define CONFIG_DEV_KERNEL_SIZE        (0x10000000)
#define CONFIG_UHEAP_KERNEL_VBASE     (0xFFFF000200000000L)   // 内核的用户堆，一定是固定偏移，只有内核能访问
// 这个地址向前延伸是rootserver启动线程的内核态资源
#define CONFIG_KHEAP_KERNEL_VBASE     (0xFFFF000800000000L)
#define CONFIG_RSIPC_KERNEL_VBASE     (0xFFFF000A00000000L)
//                          vbase                                                      .

//                          pbase                                                      .
#define CONFIG_RS_PBASE               (CONFIG_KERNEL_PBASE + CONFIG_KERNEL_SIZE)
#define CONFIG_RSIPC_PBASE            (CONFIG_RS_PBASE + CONFIG_RS_SIZE)

//                                                        =(0x50000000)
#define CONFIG_UHEAP_PBASE            (CONFIG_KERNEL_PBASE + CONFIG_KERNEL_RS_SIZE)   // 用户堆起始地址
#define CONFIG_UHEAP_SIZE             (0x1B0000000L)                                    // 用户堆大小

#define CONFIG_KHEAP_PBASE            (CONFIG_UHEAP_PBASE + CONFIG_UHEAP_SIZE)   // 内核堆起始地址
#define CONFIG_KHEAP_SIZE             (0x40000000)                                // 内核堆大小

//                          pbase                                                      .

#define CONFIG_INIT_PROCS             (64)       // 初始进程数
#define CONFIG_MAX_PROCS              (0x8000)   // 需要二级cap来支持这么多进程

#endif
