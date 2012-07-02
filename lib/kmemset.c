#include <asm/inttypes.h>
void * kmemset ( void * ptr, int value, size_t num )
{
	int i;
	for (i = 0; i < num; i++)
	{
		((char*)ptr)[i] = value;
	}
	return ptr;
}
