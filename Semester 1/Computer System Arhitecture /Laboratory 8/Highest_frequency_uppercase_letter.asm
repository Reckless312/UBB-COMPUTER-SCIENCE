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
    file_in db "input.txt", 0
    file_in_descriptor dd 0
    len equ 100
    buffer times len db 0
    letters db "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 0
    frequency dd 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    highest_frequency dd 0
    highest_frequency_letter dd 0
    access_read db "r", 0
    message db "Highest frequency: %d ; letter is : %c", 0
segment code use32 class=code
    start:
        open_file:
            push dword access_read
            push dword file_in
            call [fopen]
            add esp, 4 * 2
        
        mov [file_in_descriptor], eax
        cmp eax, 0
        je end_program
        
        loop_1:
            read_text:
                push dword [file_in_descriptor]
                push dword len
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4
            cmp eax, 0
            je find_maximum
            
            cld
            
            mov esi, buffer
            start_comparing:
                push eax
                mov edi, letters
                lodsb
                push esi
                mov esi, frequency
                mov ecx, 26
                
                go_in_letters:
                    cmp al, [edi]
                    jne skip_increase
                    
                    increase_frequency:
                        inc dword[esi]
                        jmp prepare_to_repeat
                    
                    skip_increase:
                    add esi, 4
                    inc edi
                loop go_in_letters
                
                prepare_to_repeat:
                    pop esi
                    pop eax
                    dec eax
                    cmp eax, 0
                    jne start_comparing
                    
            jmp read_text
        
        find_maximum:
            mov dl, 0
            mov esi, frequency
            
            start_comparing_2:
                mov ecx, 26
                loop_2:
                    lodsd
                    cmp eax, [highest_frequency]
                    jng skip_increase_frequency
                    
                    mov [highest_frequency], eax
                    mov [highest_frequency_letter], dl
                    add dword[highest_frequency_letter], 65 
                    
                    skip_increase_frequency:
                    
                    inc dl
                loop loop_2    
        
        print_the_values:
            push dword [highest_frequency_letter]
            push dword [highest_frequency]
            push dword message
            call [printf]
            add esp, 4 * 3
                    
        close_file:
            push dword [file_in_descriptor]
            call [fclose]
            add esp, 4
            
        end_program:
            push    dword 0
            call    [exit]      
