
#ifndef _K_TIME_H_
#define _K_TIME_H_

#include "k_stdint.h"

typedef unsigned long long time_t;

struct timespec
{
    time_t tv_sec;  /* Seconds */
    long   tv_nsec; /* Nanoseconds */
};

#endif
