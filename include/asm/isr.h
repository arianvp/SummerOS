#ifndef ISR_H_
#define ISR_H_ 
#include <asm/inttypes.h>
struct isr_args
{
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //(PUSHA)
	uint32_t intno, errno;
	uint32_t eip, cs, eflags, useresp, ss;
};
#endif
