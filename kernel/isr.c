#include <asm/isr.h>
#include <asm/pic.h>
#include <video/kvideo.h>

/* Common Interupt Service Routine Handler! */
void isr_handler(struct regs args)
{
	kputs("interrupt number :");
	kputc(args.intno + 48);
	kputc('\n');
}

static void send_eio(int intno)
{
	if (intno >= 40)
	{
		outb(PIC2_CMD, PIC_EOI);
	}
	outb(PIC1_CMD, PIC_EOI);
}

isr_handler_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t intno, isr_handler_t handler)
{
	interrupt_handlers[intno] = handler;
}


void irq_handler(struct regs args)
{
	send_eio(args.intno);

	if (interrupt_handlers[args.intno] != 0)
	{
		isr_handler_t handler = interrupt_handlers[args.intno];
		handler(args);
	}
}