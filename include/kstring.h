#ifndef KMEMOPS_H_
#define KMEMOPS_H_
#include <asm/inttypes.h>
void * kmemset ( void * ptr, int value, size_t num );

void *kmemcpy(void *dest, const void *src, size_t n);
#endif
