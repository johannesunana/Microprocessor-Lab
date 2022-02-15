#include "p16f84a.inc"
; CONFIG
; __config 0x3FFA
 __CONFIG _FOSC_HS & _WDTE_OFF & _PWRTE_OFF & _CP_OFF
 cblock 0X0C
	DELAY1
	DELAY2
 endc
 org 0                       ;reset vector
start
    bsf     STATUS,RP0      ;go to Bank1
    bcf     TRISB,RB0       ;set RB0 as Output Terminal
    bcf     STATUS,RP0      ;return to Bank0
    bcf     PORTB,RB0       ;clear RB0
main_loop
    movlw   0x82	    ;130 decimal
    movwf   DELAY2
    bsf     PORTB,RB0       ;set RB0
loop1
    decfsz  DELAY1,f
    goto    loop1
    decfsz  DELAY2,f
    goto    loop1
    movlw   0x82	    ;130 decimal
    movwf   DELAY2
    bcf     PORTB,RB0       ;clear RB0
loop2
    decfsz  DELAY1,f
    goto    loop2
    decfsz  DELAY2,f
    goto    loop2
    goto    main_loop       ;return to the main loop
 end