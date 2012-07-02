#ifndef GDT_H_
#define GDT_H_
#include <asm/inttypes.h>



struct gdt_entry
{
	uint16_t	lim_lo,
				base_lo;
	uint8_t		base_mid,
				access,
				gran,
				base_hi;
} __attribute__((packed));

struct gdt_ptr
{
	uint16_t lim;
	uint32_t base;
} __attribute((packed));


void gdt_init(void);

#endif