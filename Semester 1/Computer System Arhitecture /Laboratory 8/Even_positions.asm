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
    text db "  a b c d e aa ", 0
    file_descriptor dd 0
    access_mode db "w", 0
segment code use32 class=code
    start:
        ; the program works but the printing in file is weird
        create_file:
            push dword access_mode
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je end_of_program
        
        change_to_position:
            mov esi, text
            mov eax, 0
            start_:
                cmp byte[esi], 0
                je print_in_file
                check_position:
                    inc eax
                    push eax
                    cdq
                    mov ebx, 2
                    div ebx
                    cmp edx, 0
                    jne prepare_to_loop
                
                pop eax
                mov [esi], al
                inc esi
                jmp start_
                
                prepare_to_loop:
                inc esi
                pop eax
                jmp start_
        
        print_in_file:
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
