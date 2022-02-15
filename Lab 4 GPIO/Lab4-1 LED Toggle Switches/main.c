#include <avr/io.h>
#include <util/delay.h>

#define LED0    PD7     /* Pin  7 */
#define LED1    PD6     /* Pin  6 */
#define LED2    PD5     /* Pin  5 */
#define LED3    PD4     /* Pin  4 */
#define SW0     PC0     /* Pin A0 */
#define SW1     PC1     /* Pin A1 */
#define SW2     PC2     /* Pin A2 */
#define SW3     PC3     /* Pin A3 */

#define DELAY1  250     /* button debounce */

int16_t main(void) {
    /* Initialize Setup */
    uint8_t hold0 = 0; /* counter for push button */
    uint8_t hold1 = 0;
    uint8_t hold2 = 0;
    uint8_t hold3 = 0;

    /* Data Direction Registers */
    DDRD |= ((1 << LED0) | (1 << LED1) | (1 << LED2) |
            (1 << LED3));       /* set pins as LED output */
    DDRC &= ~((1 << SW0) | (1 << SW1) | (1 << SW2) |
            (1 << SW3));        /* set pins as push button input */
    
    /* Initial Pin Configuration */
    PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
            (1 << LED3));       /* LED turn off */
    PORTC &= ~((1 << SW0) | (1 << SW1) | (1 << SW2) |
            (1 << SW3));        /* external pull-up resistor */

    /* Loop */
    while(1) {
        /* LED0 */
        switch (hold0) {
            case 0:
                PORTD &= ~(1 << LED0);      /* turn off LED0 */
                break;
            case 1:
                PORTD |= (1 << LED0);       /* turn on LED0 */
                break;
            case 2:
                hold0 = 0;
                break;
            default:
                break;
        }
        
        /* LED1 */
        switch (hold1) {
            case 0:
                PORTD &= ~(1 << LED1);      /* turn off LED0 */
                break;
            case 1:
                PORTD |= (1 << LED1);       /* turn on LED0 */
                break;
            case 2:
                hold1 = 0;
                break;
            default:
                break;
        }  

        /* LED2 */
        switch (hold2) {
            case 0:
                PORTD &= ~(1 << LED2);      /* turn off LED0 */
                break;
            case 1:
                PORTD |= (1 << LED2);       /* turn on LED0 */
                break;
            case 2:
                hold2 = 0;
                break;
            default:
                break;
        }

        /* LED3 */
        switch (hold3) {
            case 0:
                PORTD &= ~(1 << LED3);      /* turn off LED0 */
                break;
            case 1:
                PORTD |= (1 << LED3);       /* turn on LED0 */
                break;
            case 2:
                hold3 = 0;
                break;
            default:
                break;
        }

        /* SW0 */
        if ((PINC & (1 << SW0)) == 0) {
            ++hold0;
            _delay_ms(DELAY1);
        }
        
        /* SW1 */
        if ((PINC & (1 << SW1)) == 0) {
            ++hold1;
            _delay_ms(DELAY1);
        }
        
        /* SW2 */
        if ((PINC & (1 << SW2)) == 0) {
            ++hold2;
            _delay_ms(DELAY1);
        }
        
        /* SW3 */
        if ((PINC & (1 << SW3)) == 0) {
            ++hold3;
            _delay_ms(DELAY1);
        }
    }
    return 0;           /* end of main function */
}