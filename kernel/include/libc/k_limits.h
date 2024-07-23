#ifndef LIMITS_H
#define LIMITS_H

/// WARNING: this header is shared between kernel and libmx,
/// be careful with the included headers.

#include <config.h>

#ifdef CONFIG_ARCH_32

#define INT_MAX (0x7FFFFFFF)
#define INT_MIN (0x80000000)

#define WORD_BITS (32)
#define WORD_SHIFT (5)

#else // CONFIG_ARCH_64

#define INT_MAX (0x7FFFFFFF)
#define INT_MIN (0x80000000)

#define WORD_BITS (64)
#define WORD_SHIFT (6)

#endif // CONFIG_ARCH_32

#define NAME_MAX            255
#define PATH_MAX            4096

#endif
