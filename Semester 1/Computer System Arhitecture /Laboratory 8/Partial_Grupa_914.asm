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
    text resb 100
    format db "%s", 0
    file_name db "file_out.txt", 0
    access_write db "w", 0
    file_descriptor dd 0
    len dd 0
    characters db 0, 0, 0, 0
    format_char db "%c", 0
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
        
        read_text:
            push dword text
            push dword format
            call [scanf]
            add esp, 4 * 2
        
        mov esi, text
        find_length:
            cmp byte[esi], 0
            je found_length
            inc dword[len]
            inc esi
            jmp find_length
        found_length:
        
        save_characters:
            mov esi, text
            mov edi, characters
            add esi, dword[len]
            dec esi
            mov ecx, 4
            loop_1:
                push ecx
                std
                lodsb
                cld
                stosb
                pop ecx
            loop loop_1
            
        rotate_message:
            mov esi, text
            mov edi, text
            add edi, dword[len]
            add esi, dword[len]
            sub esi, 1
            sub edi, 1
            sub esi, 4
            std
            mov ecx, dword[len]
            sub ecx, 4
            loop_2:
                movsb        
            loop loop_2 

            fill_the_start:
                mov esi, characters
                mov edi, text
                add esi, 3
                mov ecx, 4
                loop_3:
                    std
                    lodsb
                    cld
                    stosb
                loop loop_3
        
        print_in_file:
            mov esi, text
            mov eax, [len]
            cdq
            mov ebx, 2
            div ebx
            
            mov ecx, eax
            start_printing:
                push ecx
                mov al, [esi]
                
                cmp al, 'A'
                jge sub_by_character
                
                sub al, '0'
                shl al, 4
                jmp after_eax
                
                sub_by_character:
                    sub al, 'A'
                    add al, 10
                    shl al, 4
                
                after_eax:
                    inc esi
                    mov bl, [esi]
                
                cmp bl, 'A'
                jge sub_by_character_2
                
                sub bl, '0'
                jmp after_ebx
                
                sub_by_character_2:
                    sub bl, 'A'
                    add bl, 10
                
                after_ebx: 
                    inc esi
                    add al, bl
                
                cbw
                cwde
                print:
                    push eax
                    push dword format_char
                    push dword [file_descriptor]
                    call [fprintf]
                    add esp, 4 * 3
                
                pop ecx
            loop start_printing
            
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
        end_of_program:
            push    dword 0
            call    [exit]      
