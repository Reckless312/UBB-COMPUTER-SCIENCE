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
    file_name resb 30
    text resb 120
    format db "%s", 0
    access_write db "w", 0
    file_descriptor dd 0
segment code use32 class=code
    start:
        read_file_name:
            push dword file_name
            push dword format
            call [scanf]
            add esp, 4 * 2
        
        read_text:
            push dword text
            push dword format
            call [scanf]
            add esp, 4 * 2
        
        open_file:
            push dword access_write
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program
        
        write_in_file:
            push dword text
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 2
        
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
