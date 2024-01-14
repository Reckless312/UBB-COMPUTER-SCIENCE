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
    file_in db "input.txt", 0
    file_descriptor dd 0
    format db "Total vowels: %d", 0
    len equ 100
    buffer times len db 0
    acces_read db "r", 0
    vowels db "a", "e", "i", "o", "u", 0
    total_vowels dd 0
segment code use32 class=code
    start:
        open_file:
            push dword acces_read
            push dword file_in
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je end_of_program
        
        cld
        loop_1:
            read_file:
                push dword [file_descriptor]
                push dword len
                push dword 1
                push dword buffer
                call[fread]
                add esp, 4 * 4
            
            cmp eax, 0
            je print_result
            
            mov esi, buffer
            
            start_comparing:
                push eax
                
                lodsb
                mov ecx, 5
                mov edi, vowels
                
                go_in_letters:
                    scasb
                    je increase_vowels
                    jmp skip_increase
                    
                    increase_vowels:
                        inc dword [total_vowels]
                        jmp prepare_for_repeat
                        
                    skip_increase:
                loop go_in_letters
                
                prepare_for_repeat:
                    pop eax
                    dec eax
                    cmp eax, 0
                    jne start_comparing
                
            jmp read_file
        
        print_result:
            push dword [total_vowels]
            push dword format
            call [printf]
            add esp, 4 * 2
            
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]  
