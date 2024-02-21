bits 32
global start        
extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    N dd 0
    format db "%d", 0
    numbers_read resd 100
    nr dd 0
    sum_of_numbers resd 100
    current_sum dd 0
segment code use32 class=code
    start:
        read_N:
            push dword N
            push dword format
            call [scanf]
            add esp, 4 * 2
        
        mov ecx, [N]
        mov edi, numbers_read
        
        read_numbers:
            push ecx
            push dword nr
            push dword format
            call [scanf]
            add esp, 4 * 2
            mov eax, [nr]
            mov [edi], eax
            add edi, 4
            pop ecx
            loop read_numbers 
        
        mov esi, numbers_read
        mov ecx, [N]
        mov edi, sum_of_numbers
        
        move_to_sum:
            mov dword[current_sum], 0
            mov eax, [esi]
            add esi, 4
            cmp eax, 0
            je skip
            mov ebx, 10
            cdq
            another_loop:
                div ebx
                push eax
                mov eax, edx
                push ebx
                push edx
                cdq
                mov ebx, 2
                div ebx
                cmp edx, 0
                jne not_even
                pop edx
                add [current_sum], edx
                jmp after_pop
                
                not_even:
                    pop edx
                    after_pop:
                    pop ebx
                    pop eax
                    cmp eax, 0
                    je done_checking
                    jmp another_loop
                    
                done_checking:
                    mov eax, [current_sum]
                    mov [edi], eax
                    add edi, 4
                
                skip:
                loop move_to_sum
        end_program:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
