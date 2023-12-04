bits 32
global start      
extern exit, scanf, printf 
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    a dd 0
    b dd 0
    format db "%d", "%d", 0
    message db "Quotient = %d", ", remainder = %d", 0
segment code use32 class=code
    start:
        push dword b
        push dword a
        push format
        call [scanf]
        add esp, 4 * 3
        mov eax, [a]
        mov ebx, [b]
        cdq
        idiv ebx
        push edx
        push eax
        push message
        call[printf]
        add esp, 4 * 3
        push    dword 0      
        call    [exit]       
