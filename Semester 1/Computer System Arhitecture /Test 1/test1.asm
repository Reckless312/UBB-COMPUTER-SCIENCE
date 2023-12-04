bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    format db "%d", "%d", 0
    format_lower db "%d ", "<", "%d", 0
    format_equal db "%d ", "=", "%d", 0
    format_greater db "%d ", ">", "%d", 0
; our code starts here
segment code use32 class=code
    start:
        push dword b
        push dword a
        push format
        call [scanf]
        add esp, 4 * 3
        mov eax, [a]
        mov ebx, [b]
        cmp eax, ebx
        jl Lower
        cmp eax, ebx
        je Equal
        push dword ebx
        push dword eax
        push format_greater
        call[printf]
        add esp, 4 * 3
        jmp Ending
        Lower:
            push dword ebx
            push dword eax
            push format_lower
            call [printf]
            add esp, 4 * 3
            jmp Ending
        Equal:
            push dword ebx
            push dword eax
            push format_equal
            call [printf]
            add esp, 4 * 3
            jmp Ending
        Ending:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
