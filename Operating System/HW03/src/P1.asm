        ; 8080 assembler code
        .hexfile P1.hex
        .binfile P1.com
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


NumArr: dw '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50',00H
str_msg: dw 'Enter file name: ',00H
value: ds 100

begin:
	lxi sp, stack   ; always initialize the stack pointer

	lxi b, str_msg     ; testing print_str system call it prints the given value
	mvi a, PRINT_STR
	call GTU_OS
	
	lxi b, value	; it takes a string from keyboard
	mvi a, READ_STR
	call GTU_OS
	
	lxi b, value
	mvi a, FileCreate 
    call GTU_OS     	; system call 
	
	lxi b, value
	mvi a, FileOpen
	call GTU_OS     	; system call 
	
	mov e, b
	mov h, b
	lxi b, NumArr
	mvi d, 140
    mvi a, FileWrite 
    call GTU_OS     ; system call
	
	mov b, h
	mvi a, FileClose
	call GTU_OS     ; system call

exit:     
    hlt	; end program