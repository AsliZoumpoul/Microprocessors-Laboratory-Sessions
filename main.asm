;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
list1		.word 0,1,2,3,4,5,6,7,8,9
list2       .word 0,1,2,3,4,5,6,7,8,9
result		.word 0                                          ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


			push #list1
			push #list2
			push #result
			call #sublab1
			add #6,sp
			jmp $
			nop
sublab1		push r6
			mov #0,r6 ;int i
			push r15
			push r14
			push r13
			push r12
			push r10
			mov #0,r13     ;sum=0
			push r11
			mov sp,r11  ;frame pointer
			mov 18(r11),r15  ;list2
			mov 20(r11),r14   ;list1
			mov 16(r11),r10
loop		cmp #10,r6
			jz done
			mov @r15+, r12
			add @r14+, r12
			add r12,r13
			inc r6
			jmp loop
done		mov r13,0(r10) ;result
			pop r11
			pop r10
			pop r12
			pop r13
			pop r14
			pop r15
			pop r6
			ret








                                            

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
