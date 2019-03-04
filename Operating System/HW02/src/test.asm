        ; 8080 assembler code
        .hexfile test.hex
        .binfile test.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND     equ 7

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	
	PUSH D
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


str: dw 'Enter an integer value to put in B register:',00AH,00H
enter: dw 'Enter something to keep in memory:',00AH,00H
value: ds 100
random: dw 'This call gonna create a random byte.',00AH,00H
num	ds 2 ; a data to test

begin:
	lxi b, str     ; testing print_str system call it prints the given value
	mvi a, PRINT_STR
	call GTU_OS

	mvi a, READ_B ; testing read_b system call it takes an integer value to put in b register
	call GTU_OS

	mvi a, PRINT_B ; it prints the user's choiced integer value
	call GTU_OS

	lxi b, enter     ; testing print_str system call it prints the given value
	mvi a, PRINT_STR
	call GTU_OS

	lxi b, value	; it takes a string from keyboard
	mvi a, READ_STR
	call GTU_OS

	mvi a, PRINT_STR ; it shows the given string from keyboard
	call GTU_OS

	lxi b, random   ; testing print_str system call it prints the given value
	mvi a, PRINT_STR
	call GTU_OS

	mvi a, GET_RND ; this call creates a random byte
	call GTU_OS

	mvi a, PRINT_B ; it prints the random byte who stored in b reg
	call GTU_OS

	mvi a, GET_RND ; this call creates a random byte
	call GTU_OS

	mvi a, PRINT_B ; it prints the random byte who stored in b reg
	call GTU_OS

	LXI B, num	; put the address of string in registers B and C
	mvi a, READ_MEM ; it prints the random byte who stored in b reg
	call GTU_OS
	MVI A, PRINT_MEM	; store the OS call code to A
	call GTU_OS	; call the OS

exit:
	hlt