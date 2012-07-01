STACK_SIZE equ 4096

MBOOT_PAGE_ALIGN equ 1<<0
MBOOT_MEM_INFO equ 1<<1
MBOOT_HEADER_MAGIC equ 0x1badb002

MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]
[GLOBAL mboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

mboot:
	dd	MBOOT_HEADER_MAGIC
	dd	MBOOT_HEADER_FLAGS
	dd	MBOOT_CHECKSUM

	dd	mboot
	dd	code
	dd	bss
	dd	end
	dd	start

[GLOBAL start]
[EXTERN kmain]

start:
	push	ebx
	cli
	mov		esp, stack + STACK_SIZE
	call	kmain
	jmp		$

[SECTION .bss]
stack:
	resb	STACK_SIZE