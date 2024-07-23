/*********************************************************
 *
 *********************************************************/
#ifndef STDDEF_H
#define STDDEF_H

#include "printd.h"
/// WARNING: this header is shared between kernel and libmx,
/// be careful with the included headers.

#ifndef __cplusplus
typedef long ptrdiff_t;
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL (0)
#endif

#endif
