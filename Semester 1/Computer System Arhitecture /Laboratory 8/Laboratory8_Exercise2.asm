bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "lab8_1.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    len equ 100
    text times len db 0
    consonants dd 0
    format_message db "Total consonants: %d", 0
; our code starts here
segment code use32 class=code
    start:
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        mov [file_descriptor], eax
        cmp eax, 0
        je final
        bucla:
            push dword [file_descriptor]
            push dword len
            push dword 1
            push dword text
            call [fread]
            add esp, 4 * 4
            cmp eax, 0
            je cleanup
            mov ecx, eax
            mov esi, text
            check_consonants:
                cmp byte[esi], 'a'
                je skip
                cmp byte[esi], 'e'
                je skip
                cmp byte[esi], 'i'
                je skip
                cmp byte[esi], 'o'
                je skip
                cmp byte[esi], 'u'
                je skip
                cmp byte[esi], 'A'
                je skip
                cmp byte[esi], 'E'
                je skip
                cmp byte[esi], 'I'
                je skip
                cmp byte[esi], 'O'
                je skip
                cmp byte[esi], 'U'
                je skip
                cmp byte[esi], ' '
                je skip
                cmp byte[esi], '.'
                je skip
                jmp increase_consonants
                inc esi
                dec ecx
                cmp ecx, 0
                jne check_consonants 
            jmp bucla
        skip:
            dec ecx
            cmp ecx, 0
            je bucla
            inc esi
            jmp check_consonants
        increase_consonants:
            inc dword[consonants]
            dec ecx
            cmp ecx, 0
            je bucla
            inc esi
            jmp check_consonants
        cleanup:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        push dword [consonants]
        push dword format_message
        call [printf]
        add esp, 4 * 2
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program