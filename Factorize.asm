        ; 8080 assembler code
        .hexfile Factorize.hex
        .binfile Factorize.com
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
GTU_OS:	PUSH D
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

new_line dw 00AH
	
	;; prints the factor and returns to loop
print_factor:
	MVI A,PRINT_B
	call GTU_OS

	MOV H,B
	MOV L,C
	
	LXI B,new_line
	MVI A,PRINT_STR
	call GTU_OS
	
	MOV B,H
	MOV C,L
	
	INR B
	JMP loop

	;; Finds the
	;; modulo of the number
division:
	SUB B
	CMP B
	JNC division
	ret
	
begin:
	LXI SP,stack 	; always initialize the stack pointer

	MVI A, READ_MEM	; store the OS call code to A
	call GTU_OS	; call the OS
			; integer is stored in B and C registers

	MVI B,1		; B = 1
loop:
	MOV A,C		; Assumed number is stored in B and C
			; And number is less than 256 
	CMP B
	
	JZ exit		; If A < B , jump to exit

	call division	; Make division

	CPI 0		; If residual is 0 it is a factor
	JZ print_factor	; Print the factor

	INR B
	JMP loop	; Repeat the process

	;; print the number itself
	;; and exit
exit:
	MVI A,PRINT_B
	call GTU_OS

	LXI B,new_line
	MVI A,PRINT_STR
	call GTU_OS
	hlt
