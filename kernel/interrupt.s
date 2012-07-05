
[EXTERN isr_handler]

isr_stub:
	pusha
	mov		ax,ds
	push 	eax

	mov 	ax,0x10
	mov		ds,ax
	mov		es,ax
	mov		fs,ax
	mov		gs,ax

	call isr_handler

	pop		eax
	mov		ds,ax
	mov		es,ax
	mov		fs,ax
	mov		gs,ax

	popa

	add		esp,8 ; sizeof(error_code & isr_num)
	sti
	iret

%macro ISR 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push	byte 0
		push	byte %1
		jmp		isr_stub
%endmacro


%macro ISR_ERR 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push	byte %1
		jmp		isr_stub
%endmacro

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR_ERR 8
ISR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31
 	
[EXTERN irq_handler]
irq_stub:
	pusha
	mov		ax,ds	; lower 16 bits of eax = ds
	push	eax		; save data segment
	mov		ax,0x10 ; load kernel data segment descriptor
	mov		ds,ax
	mov		es,ax
	mov		fs,ax
	mov		gs,ax

	call irq_handler

	pop		ebx		; restore original data segment descriptor
	mov		ds,bx
	mov		es,bx
	mov		fs,bx
	mov		gs,bx

	popa			; restore edi esi ebp etc

	add		esp,8	; clean up stack frame (sizeof(errno) + sizeof(isrnum))
	sti
	iret
%macro IRQ 2
	global irq%1
	irq%1:
		cli
		push 	byte 0
		push	byte %2
		jmp		irq_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10,42
IRQ 11,43
IRQ 12,44
IRQ 13,45
IRQ 14,46
IRQ 15,47