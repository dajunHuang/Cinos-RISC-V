
#ifndef _K_STDINT_H_
#define _K_STDINT_H_

#include <config.h>
#ifdef __INT64_TYPE__
/* armclang predefines '__INT64_TYPE__' and '__INT64_C_SUFFIX__' */
#    define __INT64 __INT64_TYPE__
#else
/* armcc has builtin '__int64' which can be used in --strict mode */
#    define __INT64 __int64
#    define __INT64_C_SUFFIX__ ll
#endif

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef unsigned long ticks_t;

#ifdef CONFIG_ARCH_32

typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef signed long   intptr_t;
typedef unsigned long word_t;

typedef unsigned        long uintptr_t;
typedef   signed     __INT64 intmax_t;
typedef unsigned     __INT64 uintmax_t;

#else // CONFIG_ARCH_64

typedef long int64_t;
typedef unsigned long  uint64_t;
typedef signed long    intptr_t;
typedef unsigned long  uintptr_t;
typedef unsigned long  word_t;
typedef   signed     __INT64 intmax_t;
typedef unsigned     __INT64 uintmax_t;

#endif // CONFIG_ARCH_32

#endif
