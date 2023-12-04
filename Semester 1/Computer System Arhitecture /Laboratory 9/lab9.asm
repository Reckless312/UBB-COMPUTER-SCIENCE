bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fread, fprintf, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "in.txt", 0
    nume_fisier_2 db "out.txt", 0
    mod_acces db "r", 0
    mod_acces_2 db "w", 0
    descriptor_in dd -1
    decriptor_out dd -1
    nr_car_citite dd 0
    len equ 100
    S times (len + 1) db 0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces_2
        push dword nume_fisier_2
        call[fopen]
        add esp, 4*2
        mov [decriptor_out], eax
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add esp, 4*2
        cmp eax, 0
        je final
        mov [descriptor_in], eax
        bucla:
            push dword [descriptor_in]
            push dword len
            push dword 1
            push dword S
            call [fread]
            add esp, 4*4
            cmp eax, 0
            je final
            mov ecx, eax
            mov DL, 5
            mov ESI, S
            bucla_2:
                CMP ECX, 0
                je continue
                MOV BL, [ESI]
                XOR BL, DL
                MOV [ESI], BL
                DEC ECX
                INC ESI
                JMP bucla_2
            continue:
            push dword S
            push dword[decriptor_out]
            call [fprintf]
            add esp, 4*2
            jmp bucla
        cleanup:
            push dword[descriptor_in]
            call[fclose]
            add esp, 4
        cleanup_2:
            push dword[decriptor_out]
            call[fclose]
            add esp, 4
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
