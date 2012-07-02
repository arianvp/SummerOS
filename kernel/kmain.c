#include <asm/inttypes.h>
#include <asm/io.h>
#include "kscreen.h"

uint32_t kmain(void)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i = 0;
	kcls();
	kputs("Hello, World!");
	return 0xDEADBABA;
}