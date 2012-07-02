#include <asm/gdt.h>
#include <asm/idt.h>
#include <kstring.h>
extern void gdt_flush(struct gdt_ptr* ptr);

extern void idt_flush(struct idt_ptr* ptr);
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t lim, uint8_t access, uint8_t gran);
static void idt_set_gate(uint8_t num, void(*base)(void), uint16_t sel, uint8_t flags);

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


	kmemset(&idt_entries, 0, sizeof(struct idt_entry) * 256);
	idt_set_gate(0, isr0, 0x08, 0x8e);
	idt_set_gate(1, isr1, 0x08, 0x8e);
	idt_set_gate(2, isr2, 0x08, 0x8e);
	idt_set_gate(3, isr3, 0x08, 0x8e);
	idt_set_gate(4, isr4, 0x08, 0x8e);
	idt_set_gate(5, isr5, 0x08, 0x8e);
	idt_set_gate(6, isr6, 0x08, 0x8e);
	idt_set_gate(7, isr7, 0x08, 0x8e);
	idt_set_gate(8, isr8, 0x08, 0x8e);
	idt_set_gate(9, isr9, 0x08, 0x8e);
	idt_set_gate(10, isr10, 0x08, 0x8e);
	idt_set_gate(11, isr11, 0x08, 0x8e);
	idt_set_gate(12, isr12, 0x08, 0x8e);
	idt_set_gate(13, isr13, 0x08, 0x8e);
	idt_set_gate(14, isr14, 0x08, 0x8e);
	idt_set_gate(15, isr15, 0x08, 0x8e);
	idt_set_gate(16, isr16, 0x08, 0x8e);
	idt_set_gate(17, isr17, 0x08, 0x8e);
	idt_set_gate(18, isr18, 0x08, 0x8e);
	idt_set_gate(19, isr19, 0x08, 0x8e);
	idt_set_gate(20, isr20, 0x08, 0x8e);
	idt_set_gate(21, isr21, 0x08, 0x8e);
	idt_set_gate(22, isr22, 0x08, 0x8e);
	idt_set_gate(23, isr23, 0x08, 0x8e);
	idt_set_gate(24, isr24, 0x08, 0x8e);
	idt_set_gate(25, isr25, 0x08, 0x8e);
	idt_set_gate(26, isr26, 0x08, 0x8e);
	idt_set_gate(27, isr27, 0x08, 0x8e);
	idt_set_gate(28, isr28, 0x08, 0x8e);
	idt_set_gate(29, isr29, 0x08, 0x8e);
	idt_set_gate(30, isr30, 0x08, 0x8e);
	idt_set_gate(31, isr31, 0x08, 0x8e);
	idt_flush(&idtptr);

}

static void idt_set_gate(uint8_t num, void(*base)(void), uint16_t sel, uint8_t flags)
{
   idt_entries[num].base_lo = (uint32_t)base & 0xFFFF;
   idt_entries[num].base_hi = ((uint32_t)base >> 16) & 0xFFFF;

   idt_entries[num].sel = sel;
   idt_entries[num]._0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
}