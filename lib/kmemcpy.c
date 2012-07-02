#include <kstring.h>

void *kmemcpy(void *dest, const void *src, size_t n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		((char*)dest)[i] = ((char*)src)[i];
	}
	return dest;
}