bits 32
global start        
extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    sir dd 1234A678h, 12785634h, 1A4D3C26h
    len equ ($ - sir) / 4
    word_sir resw (len * 2)
    one_bits dd 0
    format db "%d", 0
segment code use32 class=code
    start:
        mov esi, sir
        mov edi, word_sir
        mov ecx, len
        cmp ecx, 0
        je print_bits
        
        transfer_to_array:
            mov eax, [esi]
            add esi, 4
            push eax
            pop dx 
            pop ax
            mov [edi], dh
            inc edi
            mov [edi], ah
            inc edi
            je find_bits
            loop transfer_to_array
        
        mov esi, word_sir
        mov ecx, len
        find_bits:
            push ecx
            mov ax, [esi]
            add esi, 2
            mov ecx, 16
            start_loop:
                shl ax, 1
                mov bh, 0
                adc bh, 0
                cmp bh, 1
                jne skip_increase_bits
                
                inc dword[one_bits]
                
                skip_increase_bits:
                loop start_loop
            
            pop ecx
            loop find_bits
            
        print_bits:
            push dword [one_bits]
            push dword format
            call [printf]
            add esp, 4 * 2
            
        end_program:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
