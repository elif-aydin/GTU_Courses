        ; 8080 assembler code
        .hexfile P3.hex
        .binfile P3.com
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
GET_RND		equ 7
TExit		equ 8
TJoin		equ 9
TYield		equ 10
TCreate		equ 11
FileCreate	equ 12
FileClose	equ 13
FileOpen	equ 14
FileRead	equ 15
FileWrite	equ 16
FileSeek	equ 17
DirRead		equ 18

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


NumArrOne: dw 'abc',00AH,00H
NumArrTwo: dw '1234',00AH,00H
NumArrThree: dw 'defgh',00AH,00H

f1: dw 'f1.txt',00H
f2: dw 'f2.txt',00H
f3: dw 'f3.txt',00H

value: ds 256

begin:
	lxi sp, stack   ; always initialize the stack pointer

	lxi b, value
	mvi a, DirRead
	call GTU_OS     ; system call
	
	lxi b, value
	mvi a, PRINT_STR
    call GTU_OS     ; system call
	
exit:     
    hlt	; end program