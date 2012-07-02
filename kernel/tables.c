#include <asm/gdt.h>
#include <asm/idt.h>
#include <kstring.h>
extern void gdt_flush(struct gdt_ptr *ptr);
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

struct gdt_entry gdt_entries[5];
struct gdt_ptr   gdtptr;
struct idt_entry idt_entries[256];
struct idt_ptr   idtptr;

void gdt_init()
{
	gdtptr.lim = (sizeof(struct gdt_entry) * 5) - 1;
	gdtptr.base = (uint32_t) &gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);// CODE SEGMENT
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);// DATA SEGMENT 
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);// USERMODE CODE SEGMENT
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);// USERMODE DATA SEGMENT
	gdt_

	gdt_flush(&gdtptr);
}


static void gdt_set_gate(int32_t num, uint32_t base, uint32_t lim, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_lo		= (base & 0xFFFF);
   gdt_entries[num].base_mid	= (base >> 16) & 0xFF;
   gdt_entries[num].base_hi		= (base >> 24) & 0xFF;

   gdt_entries[num].lim_lo		= (lim & 0xFFFF);
   gdt_entries[num].gran		= (lim >> 16) & 0x0F;

   gdt_entries[num].gran		|= gran & 0xF0;
   gdt_entries[num].access		= access;
}

void idt_init()
{
	idtptr.lim =  (sizeof(struct idt_entry) * 256) - 1;
	idtptr.base = (uint32_t) &idt_entries;

	idt_set
	kmemset(&idt_entries, 0, sizeof(struct idt_entry) * 256);
	idt_set_gate( , isr0, 0x08, 0x8e);
	idt_set_gate( , isr1, 0x08, 0x8e);
	idt_set_gate( , isr2, 0x08, 0x8e);
	idt_set_gate( , isr3, 0x08, 0x8e);
	idt_set_gate( , isr4, 0x08, 0x8e);
	idt_set_gate( , isr5, 0x08, 0x8e);
	idt_set_gate( , isr6, 0x08, 0x8e);
	idt_set_gate( , isr7, 0x08, 0x8e);
	idt_set_gate( , isr8, 0x08, 0x8e);
	idt_set_gate( , isr9, 0x08, 0x8e);
	idt_set_gate( , isr10, 0x08, 0x8e);
	idt_set_gate( , isr11, 0x08, 0x8e);
	idt_set_gate( , isr12, 0x08, 0x8e);
	idt_set_gate( , isr13, 0x08, 0x8e);
	idt_set_gate( , isr14, 0x08, 0x8e);
	idt_set_gate( , isr15, 0x08, 0x8e);
	idt_set_gate( , isr16, 0x08, 0x8e);
	idt_set_gate( , isr17, 0x08, 0x8e);
	idt_set_gate( , isr18, 0x08, 0x8e);
	idt_set_gate( , isr19, 0x08, 0x8e);
	idt_set_gate( , isr20, 0x08, 0x8e);
	idt_set_gate( , isr21, 0x08, 0x8e);
	idt_set_gate( , isr22, 0x08, 0x8e);
	idt_set_gate( , isr23, 0x08, 0x8e);
	idt_set_gate( , isr24, 0x08, 0x8e);
	idt_set_gate( , isr25, 0x08, 0x8e);
	idt_set_gate( , isr26, 0x08, 0x8e);
	idt_set_gate( , isr27, 0x08, 0x8e);
	idt_set_gate( , isr28, 0x08, 0x8e);
	idt_set_gate( , isr29, 0x08, 0x8e);
	idt_set_gate( , isr30, 0x08, 0x8e);
	idt_set_gate( , isr31, 0x08, 0x8e);

}