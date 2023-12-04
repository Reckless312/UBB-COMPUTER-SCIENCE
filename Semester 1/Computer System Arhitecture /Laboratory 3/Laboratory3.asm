bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 255
    b db 255
    c dw 6553
    e dd 429496729    ; I tried with higher for c and x but it resulted in overflow, and I don't know if it's 
    x dq 18446744073  ; impossible because of the div / mul to way bigger numbers or if it's my code
                      ; There are probably better optimization when it's coming to multiplying / divizion
; our code starts here
segment code use32 class=code
    start:
        ; Assignment : (100 + a + b * c) / (a - 100) + e + x / a
        
        ; a is a byte
        ; b is a byte
        ; c is a word
        ; e is a dword
        ; e is a qword
        
        ; Unsigned representation
        
        MOV AL, BYTE[a];              AL = a
        MOV AH, 0;                    AH = 0, AX = a
        add AL, 100;                  AX = 100 + a
        adc AH, 0;                    AX = 100 + a + CF (if needed)
        MOV BX, AX;                   BX = 100 + a, Saving AX
        MOV AX, 0;                    Clearing AX
        MOV AL, BYTE[b];              AX = b
        MOV DX, 0;                    DX = 0, Preparing DX:AX
        MUL WORD[c];                  DX:AX = b * c
        MOV CX, 0;                    Preparing CX:BX for carry
        add AX, BX;                   AX = 100 + a + b * c
        adc DX, CX;                   DX:AX = 100 + a + b * c + CF(if needed)
        MOV BX, 0;                    Clearing CX:BX
        MOV CX, 0
        MOV BL, BYTE[a];              BX = a
        sub BL, 100;                  BX = a - 100
        sbb BH, 0;                    BX = a - 100 with CF(if needed)
        DIV BX;                       AX = (100 + a + b * c) / (a - 100)
        MOV DX, 0;                    The remainder is here, don't need it
        add AX, WORD[e];              I understand how it works, hard to explain :) , Pointer arithmetic is cool :0
        adc DX, WORD[e + 2];          DX:AX = (100 + a + b * c) / (a - 100) + e
        push DX;                      Saving DX:AX to pop them in a extended registor
        push AX
        MOV AX, 0;                    Clearing DX:AX
        MOV DX, 0
        MOV EAX, DWORD[x];            Some more cool stuff
        MOV EDX, DWORD[x + 4];        EDX:EAX = x
        MOV EBX, 0;                   Clearing up
        MOV BL, BYTE[a];              EBX = a
        DIV EBX;                      EAX = x / a
        MOV EDX, 0;                   Don't need the remainder
        pop EBX;                      EBX = (100 + a + b * c) / (a - 100) + e
        add EAX, EBX;                 EAX = (100 + a + b * c) / (a - 100) + e + x / a
        adc EDX, 0;                   EDX:EAX = (100 + a + b * c) / (a - 100) + e + x / a + CF(if needed)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
