#ifndef IDT_H_
#define IDT_H_
#include <asm/inttypes.h>
struct idt_entry
{
	uint16_t	base_lo;
	uint16_t	sel;
	uint8_t 	_0;
	uint8_t		flags;
	uint16_t	base_hi;
}__attribute__((packed));

struct idt_ptr
{
	uint16_t	lim;
	uint32_t	base;
} __attribute__((packed));


void idt_init(void);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
#endif