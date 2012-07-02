
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

