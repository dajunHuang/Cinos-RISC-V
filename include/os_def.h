/**
 * @file    os_def.h
 * @brief   The system uses a unified macro
 */
#ifndef _OS_DEF_H_
#define _OS_DEF_H_

#define OS_SECTION(x)       __attribute__((section(x)))
#define OS_USED             __attribute__((used))
#define OS_ALIGNED(x)       __attribute__((aligned(x)))
#define OS_WEAK             __attribute__((weak))
#define OS_CONSTRUCTOR      __attribute__((constructor))
#define os_inline           static inline

#endif
