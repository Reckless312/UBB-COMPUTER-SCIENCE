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
    file_name db "input.txt", 0
    file_descriptor dd 0
    access_mode db "r", 0
    words dd 0
    len equ 100
    text times len db 0
    end_in_letter dd 0
    message db "Total words: %d", 0
segment code use32 class=code
    start:
        read_file:
            push dword access_mode
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program
        
        loop_1:
            read_from_file:
                push dword [file_descriptor]
                push dword len
                push dword 1
                push dword text
                call [fread]
                add esp, 4 * 4
            
            mov esi, text
            mov ecx, eax
            
            check_letters:
                mov edi, esi
                inc edi
                cmp byte[esi], ' '
                je skip
                cmp byte[esi], '.'
                je skip
                cmp byte[edi], ' '
                je found_word
                cmp byte[edi], '.'
                je found_word
                jmp skip
                
                found_word:
                    inc dword[words]
                    jmp skip
                
                skip:
                
                did_it_finish_in_letter:
                    cmp byte[esi], ' '
                    je did_not
                    cmp byte[esi], '.'
                    je did_not
                    
                    mov dword[end_in_letter], 1
                    jmp before_loop
                    
                    did_not:
                        mov dword[end_in_letter], 0
                
                before_loop:
                inc esi
            loop check_letters
        
        end_in_word:
            cmp dword[end_in_letter], 1
            jne print_on_screen
            inc dword[words]
        
        print_on_screen:
            push dword [words]
            push dword message
            call [printf]
            add esp, 4 * 2
        
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
