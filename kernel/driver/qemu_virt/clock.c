#include <config.h>
#include <device.h>
#include "scr.h"

unsigned int clock_system(void)
{
    unsigned int timer_frequency = scr_read_CNTFRQ_EL0();
    return timer_frequency;
}

void clock_init(void)
{
    // Todo
    return;
}