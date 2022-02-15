#include "p16f84a.inc"
; CONFIG
; __config 0x3FFA
 __CONFIG _FOSC_HS & _WDTE_OFF & _PWRTE_OFF & _CP_OFF

 cblock     0x0C
   DISPLAY
 endc
 org        0x00

start
    bsf     STATUS, RP0     ; go to Bank 1
    movlw   b'00000100'     ; configure Timer0, 1:32
    movwf   OPTION_REG      ; maximum prescaler
    clrf    TRISB           ; data direction of PORTB is OUTPUT
    clrf    DISPLAY         ; clear DISPLAY register
    bcf     STATUS, RP0     ; go to Bank 0

ForeverLoop
    btfss   INTCON, T0IF    ; bit test f, skip if set
                            ; TMR0 Overflow Interrupt Flag bit
                            ; 1 = TMR0 register has overflowed (must be cleared in software)
                            ; 0 = TMR0 register did not overflow
    goto    ForeverLoop     ; if TOIF == 0, execute, else skip
    bcf     INTCON, T0IF    ; if T0IF == 1, execute
    incf    DISPLAY, f      ; increment DISPLAY register and store
    movf    DISPLAY, w      ; move from DISPLAY to W register
    movwf   PORTB
    goto    ForeverLoop
 end
