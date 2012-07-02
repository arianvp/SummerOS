#include <asm/inttypes.h>
#include <asm/io.h>
#include <asm/gdt.h>
#include <asm/idt.h>
#include <video/kvideo.h>

uint32_t kmain(void)
{
	kcls();
	kputs("Hello, World!\n");
	gdt_init();
	idt_init();
	asm volatile("int $0x3");
	asm volatile("int $0x4");
	asm volatile("int $0x5");
	asm volatile("int $0x6");
	return 0xDEADBABA;
}