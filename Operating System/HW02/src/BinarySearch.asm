        ; 8080 assembler code
        .hexfile binarysearch.hex
        .binfile binarysearch.com
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

	;This program prints a null terminated string to the screen


array:ds 50 ; memorry allocation for array
string:	dw 'Error',00AH,00H 
searchmsg:	dw 'Enter a value for search :',00AH,00H 



;;;;;;;;;;;;;;;;;;fill the array;;;;;;;;;;;;;;;;;;;;;;
begin:
    lxi sp, stack      ; always initialize the stack pointer     
    lxi d, array   ; set the start of array
    mvi c, 50          ; num  of random numbers
        
get_next_value:
    mvi a, GET_RND     ; store the OS call code to A
    call GTU_OS        ; call the OS to get random number
    mov a, b           ; move b to a
    stax d             ; store the value a into memory referenced by D:E
    inx d              ; increment the memory pointer
    dcr c              ; decremet the num of random numbers
    jnz get_next_value ; loop until fill the memory with 50 random numbers
    jmp loop1          ; starting the sort
    
loop1:

    lxi d, array    ; set the start of array
    mvi h, 0            ; swap flag to check if array sorted
    mvi l, 49           ; array length

loop2:
    ldax d     ; get number from array
    mov b, a   ; move it to b
    inx d      ; go to nex number
    ldax d     ; get number from array
    mov c, a   ; move it to c
    mov a, b   ; get other number to a (for comparison)
    cmp c      ; compare a and c (our 2 number)
    jc not_swap    ; if first number lower, no need swap
    jz not_swap    ; if first number equal to other, no need swap
    jmp swap       ; otherwise, swap these numbers
    
swap:    
    inr h      ; set flag to indicate there is a swap
    dcx d      ; move back in the array
    mov a, c   ; take the lower number to a for storing in the lower index of array
    stax d     ; load that number to memory
    inx d      ; move forward in the array to store other number
    mov a, b   ; move number to a for storing
    stax d     ; store grater number in the grater index

not_swap:
    dcr l      ; decrease size to check if the hob is done
    jnz loop2
    mvi a, 0   ; set a 0 to compare swap flag
    cmp h      ; if there was a flag, go back to loop
    jnz loop1

;; printing

    lxi d, num_array    ; get array address
    mvi c, 50           ; set size
print:
    ldax d              ; load data from d to a
    mov b,a             ; take number to b to use a
    mvi a, PRINT_B
    call GTU_OS
    inx d                ; move forward in the array
    dcr c                ; decrease the size to check if job is done
    jnz print
    jmp search

;;;;;;;;;;;;;start search
search:
   	mvi d 50 ; 
	mvi e 0 ; start of array

	lxi b, searchmsg     ; testing print_str system call it prints the given value
	mvi a, PRINT_STR
	call GTU_OS	

	mvi a, READ_B
	call GTU_OS
	mov h,b
	lxi b, array

loop: 
	mov a, e
	cmp d
	jz fail
	jc fail

	; baslangic ve son indexi alıp ikiye böl
	mov a, d
	add a, e
	rar
	ani 01111111b
	
	; arrayin adresine bunu ekle
	add a, c
	mov c, a
	ldax b
	
	; karşılaştır
	cmp h
	jz success ; fark 0 sa bulundu
	jc right		; sağ tarafta
	jmp left	; ilki küçükse sol tarafta aranır
	
right: ; aradığımız sağ taraftaysa, array başlangıcını ortaya alırız.
	mov a, d
	rar
	ani 01111111b
	mov e, a
	jmp loop
	
left:	; aradığımız sol taraftaysa, size'ı ikiye böl.
	mov a, d
	rar
	ani 01111111b
	mov d, a
	jmp loop

fail:
	lxi b, string
	mvi a, PRINT_STR
	call GTU_OS
	jmp finish

success:
	mov b, c
	mvi a, PRINT_B
	call GTU_OS
	jmp finish

finish:	
	hlt		; end programjz 