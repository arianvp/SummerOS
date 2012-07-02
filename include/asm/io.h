#ifndef IO_H_
#define IO_H_
#include <asm/inttypes.h>
#define build_mmio_read(name, size, type, reg, barrier)						\
static inline type name(const volatile void  *addr)							\
{																			\
	type ret;																\
	asm volatile("mov" size " %1,%0":reg (ret)								\
		:"m" (*(volatile type *)addr) barrier);								\
	return ret;																\
}

#define build_mmio_write(name, size, type, reg, barrier)					\
static inline void name(type val, volatile void  *addr)						\
{																			\
	asm volatile("mov" size " %0,%1": :reg (val),							\
		"m" (*(volatile type *)addr) barrier);								\
}

build_mmio_read(readb, "b", uint8_t, "=q", :"memory");
build_mmio_read(readw, "w", uint16_t, "=r", :"memory");
build_mmio_read(readl, "l", uint32_t, "=r", :"memory");

build_mmio_read(__readb, "b", uint8_t, "=q", );
build_mmio_read(__readw, "w", uint16_t, "=r", );
build_mmio_read(__readl, "l", uint32_t, "=r", );

build_mmio_write(writeb, "b", uint8_t, "q", :"memory")
build_mmio_write(writew, "w", uint16_t, "r", :"memory")
build_mmio_write(writel, "l", uint32_t, "r", :"memory")

build_mmio_write(__writeb, "b", uint8_t, "q", )
build_mmio_write(__writew, "w", uint16_t, "r", )
build_mmio_write(__writel, "l", uint32_t, "r", )


#define BUILDIO(bwl, bw, type)												\
static inline void out##bwl(type value, uint32_t port)						\
{																			\
	asm volatile("out" #bwl " %" #bw "0, %w1" : : "a"(value), "Nd"(port));	\
}																			\
																			\
static inline type in##bwl(uint32_t port)									\
{																			\
	type value;																\
	asm volatile("in" #bwl " %w1, %" #bw "0"								\
		     : "=a"(value) : "Nd"(port));									\
	return value;															\
}																			\
																			\
static inline void outs##bwl(uint32_t port, const void *addr, uint64_t count) \
{																			\
	asm volatile("rep; outs" #bwl											\
		     : "+S"(addr), "+c"(count) : "d"(port));						\
}																			\
																			\
static inline void ins##bwl(uint32_t port, void *addr, uint64_t count)		\
{																			\
	asm volatile("rep; ins" #bwl											\
		     : "+D"(addr), "+c"(count) : "d"(port));						\
}		

BUILDIO(b, b, uint8_t);
BUILDIO(w, w, uint16_t);
BUILDIO(l, ,  uint32_t);
#endif