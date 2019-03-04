        ; 8080 assembler code
        .hexfile p3.hex
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

	;Prints integers from 0 to 50 by steps of 2 on the screen. Each
	;number will be printed on a new line

F3Str: dw 'In F3.',00AH,00H
thread_ids:ds 20 ; memorry allocation for array

begin:
	lxi sp, stack   ; always initialize the stack pointer
	lxi d, thread_ids   ; set the start of array
	mvi h, 10          ; num of threads

create_loop:	
	; F3
	mvi b, 0
	mvi c, F3
	mvi a, TCreate  	; for print_b function
	call GTU_OS
	
	mov a, b	; save thread's id
	stax d
	inx d
	dcr h
	jnz create_loop
	
	lxi d, thread_ids    ; set the start of array
	mvi h, 10          ; num of threads

join_loop:
	ldax d
	inx d
	mov b, a
	mvi a, TJoin  	; for print_b function
	call GTU_OS
	
	dcr h
	jnz join_loop

	hlt


;;;;;;;;;;;;;;;;;;
F3:
	lxi b, F3Str
	mvi a, PRINT_STR
	call GTU_OS

    mvi d,  101	; initialize d with 1000	
    mvi e,  50	    ; 1 = 0 for initialize   

loop3:
    mov b, e  		; for printing the value it puts in b register
    mvi a, PRINT_B  ; for print_b function 
    call GTU_OS     ; system call            
    inr e           ; i += 1
    mov a, e        ; for comparing e and d
    cmp d           ; compare a and d    
    jnz loop3        ; goto loop if a != 50
	
	mvi a, TExit  	; for print_b function
	call GTU_OS

