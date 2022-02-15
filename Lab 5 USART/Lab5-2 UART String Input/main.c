#include <avr/io.h>
#include <stdint.h>
#include <string.h>
#include "UART.h"

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define LED5 PB4

int32_t main(void) {
    /* Initialize Setup */
    uint8_t dataInput[10];
    const uint8_t *c = "";
    c = dataInput;
    int32_t STX;
    int32_t ETX;

    DDRB |= ((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
        (1 << LED5));   /* Data Direction Registers */
    PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
        (1 << LED5));   /* Initial Pin Configuration */
    Uart_Init();    /* call the USART function */
    
    /* Loop */
    while(1) {
        Uart_Gets(dataInput, 10);
        if ((dataInput[0] == '0') && (dataInput[1] == '2')) { /* first 2 bits */
            STX = 1;    /* STX condition */
        }
        else {
            STX = 0;
        }
        if ((dataInput[6] == '0') && (dataInput[7] == '3')) { /* last 2 bits */
            ETX = 1;    /* ETX condition */
        }
        else {
            ETX = 0;
        }
        if ((STX == 1) && (ETX == 1) && (dataInput[2] == '0') && (dataInput[4] == '0')) {
            if (dataInput[5] == '1') {
                switch (dataInput[3]) {
                    case '0':
                        PORTB |= (1 << LED1);   /* turn on LED1 */
                        break;
                    case '1':
                        PORTB |= (1 << LED2);   /* turn on LED2 */
                        break;
                    case '2':
                        PORTB |= (1 << LED3);   /* turn on LED3 */
                        break;
                    case '3':
                        PORTB |= (1 << LED4);   /* turn on LED4 */
                        break;
                    case '4':
                        PORTB |= (1 << LED5);   /* turn on LED5 */
                        break;
                    default:
                        break;
                }
            }
            else if (dataInput[5] == '0') {
                switch (dataInput[3]) {
                    case '0':
                        PORTB &= ~(1 << LED1);  /* turn off LED1 */
                        break;
                    case '1':
                        PORTB &= ~(1 << LED2);  /* turn off LED2 */
                        break;
                    case '2':
                        PORTB &= ~(1 << LED3);  /* turn off LED3 */
                        break;
                    case '3':
                        PORTB &= ~(1 << LED4);  /* turn off LED4 */
                        break;
                    case '4':
                        PORTB &= ~(1 << LED5);  /* turn off LED5 */
                        break;
                    default:
                        break;
                }
            }
        }   /* end of nested if condition */
    }   /* end of while loop */
}   /* end of main function */