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
    number dw 15234
    new_line db 10, 0
    format_string db "%s", 0
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
        
        mov eax, 0
        divide_number:
            mov ax, [number]
            mov edx, 0
            start_:
                cmp eax, 0
                je close_file
                
                mov ebx, 10
                div ebx
                
                push eax
                
                print_digit:
                    push edx
                    push dword format
                    push dword[file_descriptor]
                    call [fprintf]
                    add esp, 4 * 3
                
                print_new_line:
                    push dword new_line
                    push dword format_string
                    push dword[file_descriptor]
                    call [fprintf]
                    add esp, 4 * 3
                
                pop eax
                mov edx, 0
                jmp start_
        
        close_file:
            push dword[file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
