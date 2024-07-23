#ifndef STDLIB_ASSERT_H
#define STDLIB_ASSERT_H

#include <config.h>

#ifdef CONFIG_DEBUG
#include <halt.h>
#include "printd.h"

#ifdef assert
#undef assert
#endif

#define assert(x)                                                                                                      \
        do {                                                                                                           \
            if (!(x)) {                                                                                                \
                printd(PRINTD_ASSERT, #x " failed at %s.%d", __FILE__, __LINE__);                                                  \
                halt();                                                                                                \
            }                                                                                                          \
        } while (0)

#else
#define assert(x)
#endif

#endif
