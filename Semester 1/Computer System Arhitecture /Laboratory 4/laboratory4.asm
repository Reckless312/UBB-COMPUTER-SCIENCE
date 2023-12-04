bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A dq 1000000000000
    N db 0
    B dd 0
    C db 0
; our code starts here
segment code use32 class=code
    start:
    
        ; Given the quadword A, obtain the integer number N represented on the bits 35-37 of A.
        ; Then obtain the the doubleword B by rotating the low   doubleword of A N positions to the right. Obtain the byte C as follows:
        ; the bits 0-3 of C are the same as the bits 8-11 of B
        ; the bits 4-7 of C are the same as the bits 16-19 of B
        
        MOV EAX, DWORD[A]
        MOV EDX, DWORD[A + 4]
        SHL EDX, 26
        SHR EDX, 29
        MOV [N], DL ; ?
        
        MOV CL, BYTE[N]
        MOV EAX, DWORD[A]
        MOV EDX, DWORD[A + 4]
        ROR EAX, CL
        MOV [B], EAX
        
        MOV AX, WORD[B]
        SHL AX, 4
        SHR AX, 12
        OR [C], AX
        MOV AL, [C]
        MOV AX, WORD[B + 2]
        SHL AX, 12
        SHR AX, 8
        OR [C], AX
        MOV AL, [C]
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
