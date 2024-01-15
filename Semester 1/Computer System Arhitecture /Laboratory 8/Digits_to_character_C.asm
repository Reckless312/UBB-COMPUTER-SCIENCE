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
    text db "1234abcdABCD&!", 0
    digits db "0123456789", 0
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
            prepare_checking:
                lodsb
                mov edi, digits
                mov ecx, 10
                start_checking:
                    scasb
                    jne not_digit
                    
                    dec esi
                    mov byte[esi], 'C'
                    inc esi
                    
                    not_digit:
                loop start_checking
                cmp al, 0
                jne prepare_checking
        
        print_in_file:
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
