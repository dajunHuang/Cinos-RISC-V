
#include "device.h"
#include "uapi/bootinfo.h"
#include "tools/macros.h"

extern unsigned long boot_physic_end;

/* kernel's RAM */
const region_t ksram[] = {
    {.pbase = CONFIG_KERNEL_PBASE,  .vbase = CONFIG_KERNEL_VBASE,    .size = CONFIG_KERNEL_SIZE,  .exec = REGION_EXEC},
    {.pbase = CONFIG_KHEAP_PBASE, .vbase = CONFIG_KHEAP_KERNEL_VBASE, .size = CONFIG_KHEAP_SIZE, .exec = REGION_NONE},
    {
     .pbase = CONFIG_RSIPC_PBASE,
     .vbase = CONFIG_RSIPC_KERNEL_VBASE,
     .size  = CONFIG_RSIPC_SIZE,
     .exec = REGION_NONE
    },
    {.pbase = CONFIG_UHEAP_PBASE, .vbase = CONFIG_UHEAP_KERNEL_VBASE, .size = CONFIG_UHEAP_SIZE, .exec = REGION_NONE},
    {.size = 0}, // end of regions
};

/* kernel's device */
const region_t ksdev[] = {
    // UART port. The order follow, does not matter anything.
    {.pbase = DEVICE_PBASE_UART,  .vbase = DEVICE_VBASE_UART,  .size = DEVICE_SIZE_UART,    .exec = REGION_NONE},
    {.pbase = DEVICE_PBASE_GIC,   .vbase = DEVICE_VBASE_GIC,   .size = DEVICE_SIZE_GIC,     .exec = REGION_NONE},
    {.size = 0}
};

/* user's RAM */
const region_t usram[] = {
    /**
     * @brief   this region belong to the kernel but is used to store the rootserver
     */
    [USRAM_ROOTSERVER_RO] = {
     .pbase = CONFIG_RS_PBASE,
     .vbase = CONFIG_RS_VBASE,
     .size  = CONFIG_RS_SIZE,
     .exec = REGION_EXEC
    },
    // bi + rootserver主线程的运行资源
    [USRAM_THREAD] = {
     .pbase = CONFIG_RSIPC_PBASE,
     .vbase = CONFIG_RSIPC_RS_VBASE,
     .size  = CONFIG_RSIPC_SIZE,
     .exec = REGION_NONE
    },
    [USRAM_HEAP] = {
     .pbase = CONFIG_UHEAP_PBASE,
     .vbase = CONFIG_UHEAP_RS_VBASE,
     .size  = CONFIG_UHEAP_SIZE,
     .exec = REGION_NONE
    },
    /**
     * @brief   end of regions
     */
    {
     .size = 0
    },
};

/* user's device */
const region_t usdev[] = {
    {.pbase = DEVICE_PBASE_UART, .vbase = DEVICE_RS_VBASE_UART, .size = DEVICE_SIZE_UART, .exec = REGION_NONE},
    // {.pbase = DEVICE_PBASE_TIMER, .vbase = DEVICE_RS_VBASE_TIMER, .size = DEVICE_SIZE_TIMER, .exec = REGION_NONE},
    //{.pbase = DEVICE_PBASE_GPIO0, .vbase = DEVICE_RS_VBASE_GPIO0, .size = DEVICE_SIZE_GPIO0, .exec = REGION_NONE},
    {.size = 0},
};
