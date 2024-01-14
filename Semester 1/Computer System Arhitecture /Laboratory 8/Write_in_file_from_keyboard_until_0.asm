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
    file_name db "writing_file.txt", 0
    file_descriptor dd 0
    access_write db "w", 0
    text resb 50
    format db "%s", 0
segment code use32 class=code
    start:
        ; I interpreted it as reading only the character "0" or more specifically, that character being the first
        create_file:
            push dword access_write
            push dword file_name
            call [fopen]
            add esp, 4 * 2
            
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program    
            
        infinite_loop:
            read_from_keyboard:
                push dword text
                push format
                call [scanf]
                add esp, 4 * 2
            check_for_0:
                mov esi, text
                cmp byte[esi], "0"
                je close_file
            
            write_in_file:
                push dword text
                push dword [file_descriptor]
                call [fprintf]
                add esp, 4 * 2
            
            jmp infinite_loop
        
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
