bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 127
    b db 127
    c dw 3225
    e dd 214243314   ; I tried with higher for c and x but it resulted in overflow, and I don't know if it's 
    x dq 9223322521  ; impossible because of the div / mul to way bigger numbers or if it's my code
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
        
        ; Signed representation
        
        MOV AL, BYTE[a];              AL = a
        cbw;                          AX = a
        add AL, 100;                  AX = 100 + a
        adc AH, 0;                    AX = 100 + a + CF (if needed)
        MOV BX, AX;                   BX = 100 + a, Saving AX
        MOV AL, BYTE[b]
        cbw;                          AX = b
        IMUL WORD[c];                 DX:AX = b * c
        add AX, BX;                   AX = 100 + a + b * c
        adc DX, 0;                    DX:AX = 100 + a + b * c + CF(if needed)
        MOV BX, AX;                   Saving DX:AX in CX:BX
        MOV CX, DX
        MOV AL, BYTE[a]
        cbw;                          AX = a
        sub AL, 100;                  AX = a - 100
        sbb AH, 0;                    AX = a - 100 with CF(if needed)
        push BX;                      Saving CX:BX on the stack
        push CX
        MOV BX, AX;                   BX = a - 100
        pop DX;                       DX:AX = 100 + a + b * c
        pop AX
        IDIV BX;                      AX = (100 + a + b * c) / (a - 100)
        MOV DX, 0;                    The remainder is here, don't need it
        add AX, WORD[e]              
        adc DX, WORD[e + 2];          DX:AX = (100 + a + b * c) / (a - 100) + e
        push DX;                      Saving DX:AX to pop them in a extended registor
        push AX
        MOV AL, BYTE[a]
        cbw
        cwde;                         EAX = a
        MOV EBX, EAX;                 EBX = a
        MOV EAX, DWORD[x]
        MOV EDX, DWORD[x + 4];        EDX:EAX = x
        IDIV EBX;                     EAX = x / a
        MOV EDX, 0;                   Don't need the remainder
        pop EBX;                      EBX = (100 + a + b * c) / (a - 100) + e
        add EAX, EBX;                 EAX = (100 + a + b * c) / (a - 100) + e + x / a
        adc EDX, 0;                   EDX:EAX = (100 + a + b * c) / (a - 100) + e + x / a + CF(if needed)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
