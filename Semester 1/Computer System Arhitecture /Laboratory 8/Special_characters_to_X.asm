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
    file_name db "changed_special.txt", 0
    file_descriptor dd 0
    access_write db "w", 0
    text db "abcdefgABCDEFG1234!%*+'&", 0
    len equ text - $$
    special_characters db "!", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", 0
segment code use32 class=code
    start:
        create_file:
            push dword access_write
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program
            
        mov eax, len  
        mov esi, text
        cld
        change_to_lower:
            push eax
            mov al, [esi]
            mov ecx, 13
            mov edi, special_characters
            change_character:
                scasb
                jne skip_change
                
                change_to_X:
                    mov byte[esi], "X"
                    jmp after_change
                
                skip_change:
            loop change_character
            after_change:
            pop eax
            dec eax
            inc esi
            cmp eax, 0
            jne change_to_lower
        
        write_in_file:
            push dword text
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 2
        
        close_file:
            push dword[file_descriptor]
            call [fclose]
            add esp, 4
        end_of_program:
            push    dword 0
            call    [exit]      
