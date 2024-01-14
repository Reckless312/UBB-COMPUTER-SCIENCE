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
    access_read db "r", 0
    len equ 100
    text times len db 0
    x dd 0
    y dd 0
    message db "X: %d, Y: %d", 0
segment code use32 class=code
    start:
        open_file:
            push dword access_read
            push dword file_name
            call [fopen]
            add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end_of_program
        
        loop_1:
            read_file:
                push dword[file_descriptor]
                push dword len
                push dword 1
                push dword text
                call [fread]
                add esp, 4 * 4
            
            cmp eax, 0
            je print_on_screen
            
            mov esi, text
            mov ecx, eax
            
            find_x_and_y:
                cmp byte[esi], "x"
                je increase_x
                
                cmp byte[esi], "y"
                je increase_y
                
                jmp skip_increase
                
                increase_x:
                    inc dword[x]
                    jmp skip_increase
                
                increase_y:
                    inc dword[y]
                    
                skip_increase:
                inc esi
            loop find_x_and_y
            jmp read_file
        
        print_on_screen:
            push dword [y]
            push dword [x]
            push dword message
            call [printf]
            add esp, 4 * 3
        
        close_file:
            push dword[file_descriptor]
            call [fclose]
            add esp, 4
        
        end_of_program:
            push    dword 0
            call    [exit]      
