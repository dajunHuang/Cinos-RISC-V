#ifndef _DEVICE_H_
#define _DEVICE_H_
#include <config.h>

/************************** UART **************************/
#define DEVICE_PBASE_UART               0x09000000
#define DEVICE_VBASE_UART               (CONFIG_DEV_KERNEL_VBASE)
#define DEVICE_SIZE_UART                0x1000  //4K
#define DEVICE_RS_VBASE_UART            (CONFIG_DEV_RS_VBASE)

/************************** GIC  **************************/
#define DEVICE_PBASE_GIC                0x08000000
#define DEVICE_VBASE_GIC                (DEVICE_VBASE_UART + DEVICE_SIZE_UART)
#define DEVICE_SIZE_GIC                 0x01000000 //16M
#define GICD_TO_GICR_OFFSET             0xA0000
#define GICD_PBASE                      0x08000000
#define GICR_PBASE                      0x080A0000

// 检查最后一个内核设备地址有没有超出规定范围
#if (DEVICE_VBASE_GIC + DEVICE_SIZE_GIC) > (CONFIG_DEV_KERNEL_VBASE + CONFIG_DEV_KERNEL_SIZE)
#error "设备地址设置超出范围"
#endif

/************************** timer  ************************/
#define DEVICE_PBASE_TIMER              0xfe5f0000     //qemu virt 没有外部timer
#define DEVICE_SIZE_TIMER               0x1000
#define DEVICE_RS_VBASE_TIMER           (DEVICE_RS_VBASE_UART + DEVICE_SIZE_UART)

/************************ GPIO0_BASE **********************/

#define DEVICE_PBASE_GPIO0              0x09030000
#define DEVICE_SIZE_GPIO0               0x1000
#define DEVICE_RS_VBASE_GPIO0           (DEVICE_RS_VBASE_TIMER + DEVICE_SIZE_TIMER)

// 检查最后一个根服务设备地址有没有超出规定范围
#if (DEVICE_RS_VBASE_GPIO0 + DEVICE_SIZE_GPIO0) > (CONFIG_DEV_RS_VBASE + CONFIG_DEV_RS_SIZE)
#error "设备地址设置超出范围"
#endif

enum usram_index {
    USRAM_ROOTSERVER_RO,
    USRAM_THREAD,
    USRAM_HEAP,

    USRAM_COUNT,
};

#endif
