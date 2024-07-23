#include <halt.h>
#include "printf.h"

void halt(void)
{
    unsigned int mask = 1;

    printf("oops: system will be halt permanently!\n");

    // todo:
    while(1);

    // add this to avoid warning
    mask = mask;
}