#include "p16f84a.inc"
; CONFIG
; __config 0x3FFA
 __CONFIG _FOSC_HS & _WDTE_OFF & _PWRTE_OFF & _CP_OFF

 cblock         0x0C
    DELAY1
    DELAY2
 endc
 org            0x00

start
    bsf         STATUS, RP0     ; set bit 5, go to Bank 1
    bsf         TRISA, TRISA0   ; TRISA data direction register
                                ; set TRISA bit 0, RA0 pin is INPUT
    clrw                        ; clear W (working) register
    movlw       0x00            ; move 0b'00000000' to W register
    andwf       TRISB           ; (W & TRISB), CLEAR TRISB bits
                                ; PORTB pin RBx is OUTPUT
    bcf         STATUS, RP0     ; clear bit 5, go to Bank 0
    andwf       PORTB           ; 0b'00000000' & PORTB, clear pins

main_loop
    movlw       0x58            ; move  0d'163' to W register
    movwf       DELAY2
    btfsc       PORTA, RA0      ; check if pin RA0 is SET (unpressed)
                                ; execute next statement, if CLEAR
                                ; (pressed/GND), call delay
    goto        main_loop       ; go to main_loop, wait for input
    call        delay           ; cause delay as debounce
                                ; call delay subroutine
    movlw       0x58
    movwf       DELAY2
    incf        PORTB, f        ; add 1 bit to PORTB
    call        delay
    goto        main_loop       ; go to main_loop

delay                           ; short delay routine for debounce
loop
    decfsz      DELAY1, f
    goto        loop
    decfsz      DELAY2, f
    goto        loop
    return
 end