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
    access_mode db "w", 0
    n dd 0
    format db "%d", 0
    format_string db "%s", 0
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
        
        infinite_loop:
            read_number:
                push dword n
                push dword format
                call [scanf]
                add esp, 4 * 2
            
            cmp dword[n], 0
            je close_file
            
            check_div_7:
                mov eax, [n]
                cdq
                mov ebx, 7
                div ebx
                cmp edx, 0
                jne skip
            
            write_to_file:
                push dword [n]
                push dword format
                push dword [file_descriptor]
                call [fprintf]
                add esp, 4 * 3
                
            skip:
            
            jmp infinite_loop
              
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
