        ; 8080 assembler code
        .hexfile p4.hex
        .binfile P4.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

; OS call list
PRINT_B     equ 1
PRINT_MEM   equ 2
READ_B      equ 3
READ_MEM    equ 4
PRINT_STR   equ 5
READ_STR    equ 6
GET_RND     equ 7
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
    nop ; This is where we run our OS in C++, see the CPU8080::isSystemCall()
        ; function for the detail.
    pop psw
    pop h
    pop d
    pop D
    ret
    ; ---------------------------------------------------------------
    ; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

    ;This program adds numbers from 0 to 10. The result is stored at variable
    ; sum. The results is also printed on the screen.

num_array:ds 50 ; memorry allocation for array
num_array_2:ds 50 ; memorry allocation for array

F4Str: dw 'In F4.',00AH,00H
F5Str: dw 'In F5.',00AH,00H
1stElem: dw '1st element:',00AH,00H
10thElem: dw '10th element:',00AH,00H
40thElem: dw '40th element:',00AH,00H

;;;;;;;;;;;;;;;;;;fill the array;;;;;;;;;;;;;;;;;;;;;;
begin:
    lxi sp, stack
	
	mvi b, 0
	mvi c, F5
	mvi a, TCreate  	
	call GTU_OS

	mvi a, TJoin  
	call GTU_OS

	hlt

;;;;;;;;;;;;;;;;;;;;;

F5:      
    lxi d, num_array_2   ; set the start of array
    mvi c, 50          ; num  of random numbers
        
get_next_value2:
    mvi a, GET_RND     ; store the OS call code to A
    call GTU_OS        ; call the OS to get random number
    mov a, b           ; move b to a
    stax d             ; store the value a into memory referenced by D:E
    inx d              ; increment the memory pointer
    dcr c              ; decremet the num of random numbers
    jnz get_next_value2 ; loop until fill the memory with 50 random numbers
    jmp loop2_1          ; starting the sort
    
loop2_1:

    lxi d, num_array_2    ; set the start of array
    mvi h, 0            ; swap flag to check if array sorted
    mvi l, 49           ; array length

loop2_2:
    ldax d     ; get number from array
    mov b, a   ; move it to b
    inx d      ; go to nex number
    ldax d     ; get number from array
    mov c, a   ; move it to c
    mov a, b   ; get other number to a (for comparison)
    cmp c      ; compare a and c (our 2 number)
    jc not_swap2    ; if first number lower, no need swap
    jz not_swap2    ; if first number equal to other, no need swap
    jmp swap2       ; otherwise, swap these numbers
    
swap2:    
    inr h      ; set flag to indicate there is a swap
    dcx d      ; move back in the array
    mov a, c   ; take the lower number to a for storing in the lower index of array
    stax d     ; load that number to memory
    inx d      ; move forward in the array to store other number
    mov a, b   ; move number to a for storing
    stax d     ; store grater number in the grater index

not_swap2:
    dcr l      ; decrease size to check if the hob is done
    jnz loop2_2
    mvi a, 0   ; set a 0 to compare swap flag
    cmp h      ; if there was a flag, go back to loop
    jnz loop2_1

;; printing

	lxi b, 1stElem
	mvi a, PRINT_STR
	call GTU_OS

    lxi d, num_array_2    ; get array address
	ldax d              ; load data from d to a
    mov b,a             ; take number to b to use a
    mvi a, PRINT_B
    call GTU_OS

	mov a, d
	adi 10
	mov d, a
	ldax d              ; load data from d to a
    mov b,a             ; take number to b to use a
    mvi a, PRINT_B
    call GTU_OS

	mov a, d
	adi 30
	mov d, a
	ldax d              ; load data from d to a
    mov b,a             ; take number to b to use a
    mvi a, PRINT_B
    call GTU_OS
	
	mvi a, TExit
    call GTU_OS


;;;;;;;;;;;;;;;;;;;;;
F4:      
    lxi d, num_array   ; set the start of array
    mvi c, 50          ; num  of random numbers
        
get_next_value1:
    mvi a, GET_RND     ; store the OS call code to A
    call GTU_OS        ; call the OS to get random number
    mov a, b           ; move b to a
    stax d             ; store the value a into memory referenced by D:E
    inx d              ; increment the memory pointer
    dcr c              ; decremet the num of random numbers
    jnz get_next_value1 ; loop until fill the memory with 50 random numbers
    jmp loop1_1          ; starting the sort
    
loop1_1:

    lxi d, num_array    ; set the start of array
    mvi h, 0            ; swap flag to check if array sorted
    mvi l, 49           ; array length

loop1_2:
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
    jnz loop1_2
    mvi a, 0   ; set a 0 to compare swap flag
    cmp h      ; if there was a flag, go back to loop
    jnz loop1_1

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
    mvi a, TExit
    call GTU_OS

