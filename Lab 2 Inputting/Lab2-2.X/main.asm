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
    bsf         STATUS, RP0
    bsf         TRISA, TRISA0
    clrw
    movlw       0x00
    andwf       TRISB                                
    bcf         STATUS, RP0
    andwf       PORTB

pattern1
    clrw
    movlw       0x55            ;0b'0101 0101'
    movwf       PORTB
loop1
    movlw       0xAA
    movwf       DELAY2
    call        delay
    
    movlw       0xAA
    movwf       DELAY2
    rrf         PORTB, f        ;move bits to the right
    btfsc       PORTA, RA0
    goto        loop1
    goto        pattern2

pattern2
    clrw
    movlw       0x01            ;0b'0000 0001'
    movwf       PORTB
loop2
    movlw       0xAA
    movwf       DELAY2
    call        delay
    
    movlw       0xAA
    movwf       DELAY2
    rlf         PORTB, f        ;move bits to the left
    call        delay

    btfsc       PORTA, RA0
    goto        loop2
    goto        pattern3

pattern3
    clrw
    movlw       0xF0            ;0b'1111 0000'
    movwf       PORTB
loop3
    movlw       0xAA
    movwf       DELAY2
    call        delay
    
    movlw       0xAA
    movwf       DELAY2
    comf        PORTB, f        ;complement PORTB
    btfsc       PORTA, RA0
    goto        loop3
    goto        pattern4

pattern4
    clrw
    movlw       0xCC            ;0b'1100 1100'
    movwf       PORTB
loop4
    movlw       0xAA
    movwf       DELAY2
    call        delay
    
    movlw       0xAA
    movwf       DELAY2
    rrf         PORTB, f        ;move bits to the right
    btfsc       PORTA, RA0
    goto        loop4
    goto        pattern1

delay
loop
    decfsz      DELAY1, f
    goto        loop
    decfsz      DELAY2
    goto        loop
    return
 end