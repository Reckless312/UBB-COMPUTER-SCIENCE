bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; A string of bytes 'input' is given together with two additional strings of N bytes each, 'src' and 'dst'. 
    ; Obtain a new string of bytes called 'output' from the 'input' string, by replacing all the bytes with the value src[i] with the new value dst[i], for i=1..N.
    input db '1','0','1','1','0','0','1','0'
    len equ $ - input; length of input
    src db '1','0','1','1'
    N equ $ - src; length of src, dst
    checker equ len - (len % N); to make sure we don't add anything extra
    rest_of_check equ len - checker; the rest of bytes to be added
    dst db '0','1','1','1'
    output times len db '0'; same amount of bytes as input
    

; our code starts here
segment code use32 class=code
    start:
        MOV ECX, 0; -> from 0 to checker
        CMP ECX, checker; if 0 from the start, ends
        JE END_OF_PROGRAM
        CLD; in case of direction flag = 1
        FOR_LOOP:
            MOV BL, 0; my registor to go for using loops
            MOV ESI, input; ESI point to input
            ADD ESI, ECX; location + ecx
            MOV EDI, src; EDI points to src
            N_TIMES_LOOP_TO_CHECK_RELATION:; This nested loops checks if the bytes are the same, if yes, then we move inside the "for loop"
                CMPSB
                JNE ASSIGN_ORIGINAL_VALUE_OF_INPUT; we jump into a function which puts the "N" bytes from "input" into "output"
                INC BL
                CMP BL, N
                JNE N_TIMES_LOOP_TO_CHECK_RELATION
            MOV BL, 0
            MOV ESI, dst; if we reach this part, the bytes match and we change the bytes of "output" with the ones from "dst"
            MOV EDI, output
            ADD EDI, ECX; to be on the right position
            ASSIGN_NEW_VALUE_OF_DST_N_TIMES:; loop that changes the bytes
                MOVSB
                INC BL
                CMP BL, N
                JNE ASSIGN_NEW_VALUE_OF_DST_N_TIMES
            ADD ECX, N; we add to ecx the amount of bytes changed/ unchanged
            CMP ECX, checker; we go as far as checker 
            JGE END_COMMAND
            JMP FOR_LOOP; back to the loop
        ASSIGN_ORIGINAL_VALUE_OF_INPUT:; from input -> output
            MOV ESI, input; preps, pointing and adding to the locations we need
            ADD ESI, ECX
            MOV EDI, output
            ADD EDI, ECX
            MOV BL, 0
            LOOP_TO_ASSIGN_ORIGINAL:; the assign loop
               MOVSB
               INC BL
               CMP BL, N
               JNE LOOP_TO_ASSIGN_ORIGINAL
            ADD ECX, N
            CMP ECX, checker
            JGE END_COMMAND
            JMP FOR_LOOP; back to for if not equal or greater
        END_COMMAND:; final step, adding the "rest_of_check" bytes, to the "output"
            MOV BL, 0
            MOV ESI, input
            ADD ESI, ECX
            MOV EDI, output
            ADD EDI, ECX
            LOOP_TO_ASSIGN_REST:; another loop to assign
                CMP BL, rest_of_check
                JE END_OF_PROGRAM
                INC BL
                MOVSB
                JMP LOOP_TO_ASSIGN_REST
        END_OF_PROGRAM:; The end of the program
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
