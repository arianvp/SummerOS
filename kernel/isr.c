#include <asm/isr.h>
#include <video/kvideo.h>
void isr_handler(struct isr_args args)
{
	kputs("interrupt number :");
	kputc(args.intno + 48);
	kputc('\n');
}