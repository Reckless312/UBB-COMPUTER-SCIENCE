bits 32
global start        
extern exit, scanf, printf, fopen, fclose, fread, fprintf               
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
segment data use32 class=data
    file_name db "output.txt", 0
    text db "123456789010abcde$%2", 0
    file_descriptor dd 0
    access_mode db "w", 0
    sum dd 0
    digits db "0123456789", 0
    format db "%d", 0
segment code use32 class=code
    start:
        create_file:
            push dword access_mode
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program
        
        loop_1:
            cld
            mov esi, text
            check_digit:
                mov edi, digits
                lodsb
                mov ecx, 10
                is_digit:
                    scasb
                    je increase_sum
                    jmp before_loop
                    
                    increase_sum:
                        sub al, '0'
                        cbw
                        cwde
                        add [sum], eax
                    
                    before_loop:
                loop is_digit
                cmp byte[esi], 0
                jne check_digit
        
        print_in_file:
            push dword [sum]
            push dword format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
        
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
