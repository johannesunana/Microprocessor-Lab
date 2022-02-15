#include <avr/io.h>
#include <stdint.h>
#include <ctype.h>
#include "UART.h"

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define LED5 PB4

int32_t main(void) {
    /* Initialize Setup */
    uint8_t letterInput;
    DDRB |= ((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
        (1 << LED5));   /* Data Direction Registers */
    PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
        (1 << LED5));   /* Initial Pin Configuration */
    Uart_Init();    /* call the USART function */
    
    /* Loop */
    while(1) {
        letterInput = toupper(Uart_Getc());     /* capitalize the letter */
        Uart_Putc(letterInput);     /* print out the letter */
        switch (letterInput) {
            case 'A':
                PORTB ^= (1 << LED1);   /* toggle LED1 */
                break;
            case 'B':
                PORTB ^= (1 << LED2);   /* toggle LED2 */
                break;
            case 'C':
                PORTB ^= (1 << LED3);   /* toggle LED3 */
                break;
            case 'D':
                PORTB ^= (1 << LED4);   /* toggle LED4 */
                break;
            case 'E':
                PORTB ^= (1 << LED5);   /* toggle LED5 */
                break;
            default:
                break;
        }   /* end of switch condition */
    }   /* end of while loop */
}   /* end of main function */