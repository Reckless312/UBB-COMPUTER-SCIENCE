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
    file_descriptor dd 0
    access_mode db "w", 0
    hexa_number dw 3D45h
    format db "%d", 0
    new_line db 10, 0
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
        
        mov ax, [hexa_number]
        cwde
        
        start_:
            push eax
            
            shl eax, 28
            shr eax, 28
            
            push eax
            push dword format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            push new_line
            push dword format_string
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            pop eax
            shr eax, 4
            cmp eax, 0
            jne start_
            
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
        end_of_program:
            push    dword 0
            call    [exit]      
