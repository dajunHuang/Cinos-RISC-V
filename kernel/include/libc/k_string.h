#ifndef STRING_H
#define STRING_H

#include <k_assert.h>
#include <k_stddef.h>
#include <k_string.h>

static inline void memset(void *p, int value, size_t size)
{
    int *pp = p;

    // make sure both of p and size are aligned with 4 bytes
    assert(((unsigned long)p & 0x3) == 0);
    assert((size & 0x3) == 0);

    size >>= 2;

    while (size != 0) {
        *pp = value;
        pp++, size--;
    }
}

// void *memcpy(void *t, const void *s, size_t size);
static inline void *memcpy(void *t, const void *s, size_t size)
{
    unsigned char *tt = t;
    const unsigned char *ss = s;

    while (size > 0) {
        *tt = *ss;
        tt++, ss++;
        size--;
    }

    return t;
}



static inline size_t strlen(const char *str)
{
    size_t result = 0;

    if (str != 0) {
        while (*str != 0)
            result++, str++;
    }

    return result;
}

static inline size_t strcpy(char *dst, const char *src)
{
    size_t result = 0;
    char *p = dst;
    const char *q = src;
    if (dst != 0 && src != 0) {
        while (*q != 0) {
            *p = *q;
            p++;
            q++;
            result++;
        }
    }
    return result;
}

static inline char *strcat(char *dest, const char *src)
{
    char *ret = dest;
    dest += strlen(dest);
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}

static inline int strcmp(const char *str1, const char *str2)
{
    const char *__str1 = str1;
    const char *__str2 = str2;
    while (*__str1 && *__str2) {
        if (*__str1 > *__str2)
            return 1;
        if (*__str1 < *__str2)
            return -1;
        __str1++;
        __str2++;
    }
    if (*__str1)
        return 1;
    if (*__str2)
        return -1;
    return 0;
}
#endif
