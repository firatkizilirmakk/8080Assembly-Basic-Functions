				; 8080 assembler code
	        .hexfile Palindrome.hex
	        .binfile Palindrome.com
	        ; try "hex" for downloading in hex format
	        .download bin  
	        .objcopy gobjcopy
	        .postbuild echo "OK!"
	        ;.nodump

	; OS call list
PRINT_B		equ 4
PRINT_MEM	equ 3
READ_B		equ 7
READ_MEM	equ 2
PRINT_STR	equ 1
READ_STR	equ 8

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:
	push D			
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D			
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        


pal:	dw 'Palindrome',00AH,00H ; null terminated string
not_pal:dw 'Not Palindrome',00AH,00H ; null terminated string
string:	dw 00H			     ; for storing user read string
	

begin:
	LXI SP,stack 	; always initialize the stack pointer

	LXI B,string
	MVI A, READ_STR	; store the OS call code to A
	call GTU_OS	; call the OS
			; string is stored in B and C registers
	MVI D, 0
	;; put the characters into stack
	;; for later use
put_stack:
	LDAX B
	INX B

	CPI 0
	JZ look_ahead	; if NULL is encountered
			; time to look for palindrome 
	
	MOV H,A
	PUSH H
	INR D

	
	JMP put_stack	
	
look_ahead:
	LXI B,string	;look for start address
	jmp look

	;; pop from stack and look for
	;; characters from both ends
look:
	POP H
	DCR D

	LDAX B
	CMP H
	JNZ print_not_pal
	
	INX B
	MOV E,A
	MOV A,D
	CPI 0
	JZ print_pal

	MOV A,E	
	
	JMP look
	;; print not palindrome string
print_not_pal:
	LXI B, not_pal
	jmp exit
	;; print palindrome string
print_pal:	
	LXI B, pal
	jmp exit
	
exit:
	MVI A, PRINT_STR
	call GTU_OS
	hlt
