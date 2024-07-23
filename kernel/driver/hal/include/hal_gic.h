#ifndef __HAL_GIC_H__
#define __HAL_GIC_H__
void hal_gicd_init(void);
void hal_gic_sgi_trigger(unsigned int id, int security, unsigned int filter, unsigned char cpulist);
#endif