bits 32 ;
assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    S1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
    l1 equ $ - S1
    S2 db 'a', '4', '5'
    l2 equ $ - S2
    D times l1 db 0
; our code starts here
segment code use32 class=code
    start:
        ; Two character strings S1 and S2 are given. Obtain the string D which contains all the elements of S1 that do not appear in S2.
        ; S1: '+', '4', '2', 'a', '8', '4', 'X', '5'
        ; S2: 'a', '4', '5'
        ; D: '+', '2', '8', 'X'
        MOV ECX, l1;     length of the first list
        MOV EAX, 0;      index for D
        JECXZ SFARSIT;   jump to the end
        REPETA1:
            JECXZ SFARSIT
            MOV ESI, l2; length of list 2
            MOV BL, 1;   a boolean value
            REPETA2:;    nested loop
                CMP ESI, 0;  checking for every term in the second list if it's equal to the element in the first
                JE DECREASE_ECX
                MOV DL, [S1 + ECX - 1]
                CMP DL, [S2 + ESI - 1]
                JE BOOL; BL = 0
                DEC ESI
                CMP ESI, 0
                JNE REPETA2
            CMP BL, 1
            JE ASSIGN;  We add the value in D
            CMP ECX, 0
            JNE REPETA1
        BOOL:;     Making BL = 0
            MOV BL, 0
            JMP DECREASE_ECX
        DECREASE_ECX:
            DEC ECX
            JMP REPETA1
        ASSIGN:
            MOV BYTE[D + EAX], DL
            INC EAX
            DEC ECX
            JMP REPETA1
        SFARSIT:
        cdq+
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
