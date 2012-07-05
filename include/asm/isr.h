#ifndef ISR_H_
#define ISR_H_ 
#include <asm/inttypes.h>
struct regs
{
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //(PUSHA)
	uint32_t intno, errno;
	uint32_t eip, cs, eflags, useresp, ss;
};

typedef void (*isr_handler_t)(struct regs);

void register_interrupt_handler(uint8_t intno, isr_handler_t);
#endif
