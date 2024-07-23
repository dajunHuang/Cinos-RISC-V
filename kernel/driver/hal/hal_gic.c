#include "config.h"

#if defined(CONFIG_DRIVERS_GIC_V2)
#include <gic_v2.h>
#elif defined(CONFIG_DRIVERS_GIC_V3)
#include "scr.h"
#include <gic_v3.h>
#endif

void hal_gicd_init(void)
{

}

void hal_gic_sgi_trigger(unsigned int id, int security, unsigned int filter, unsigned char cpulist)
{

}
