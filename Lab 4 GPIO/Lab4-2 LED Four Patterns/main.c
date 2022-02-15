#include <avr/io.h>
#include <util/delay.h>

#define LED0    PD7     /* Pin  7 */
#define LED1    PD6     /* Pin  6 */
#define LED2    PD5     /* Pin  5 */
#define LED3    PD4     /* Pin  4 */
#define LED4    PD3     /* Pin  3 */
#define LED5    PD2     /* Pin  2 */

#define SW0     PC0     /* Pin A0 */
#define SW1     PB0     /* Pin 8 */
#define DELAY0  100     /* 0.1 seconds, blinking delay */
#define DELAY1  250     /* 0.25 seconds, blinking delay */
#define DELAY2  500     /* 0.5 seconds, blinking delay */
#define DELAY3  1000    /* 1 second */

int16_t main(void) {
    /* Initialize Setup */
    uint8_t pattern = 0;

    /* Data Direction Registers */
    DDRD |= (((1 << LED0) | (1 << LED1) | (1 << LED2)) | (1 << LED3) |
            (1 << LED4) | (1 << LED5));    /* set pins as LED output */
    DDRC &= ~(1 << SW1);                   /* set pin as push button input */
    
    /* Initial Pin Configuration */
    PORTD &= ~(((1 << LED0) | (1 << LED1) | (1 << LED2)) | (1 << LED3) |
            (1 << LED4) | (1 << LED5));    /* LED turn off */
    PORTC &= ~(1 << SW1);                  /* external pull up resistor */

    /* Loop */
    while(1) {
        switch (pattern) {      /* switch condition to determine pattern */
        case 0:             /* turn off everything */
            PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
                    (1 << LED3) | (1 << LED4) | (1 << LED5));
            break;
        
        case 1:         /* group blink */
            PORTD |= ((1 << LED0) | (1 << LED1) | (1 << LED2) |
                    (1 << LED3) | (1 << LED4) | (1 << LED5));
            _delay_ms(DELAY1);
            PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
                    (1 << LED3) | (1 << LED4) | (1 << LED5));
            _delay_ms(DELAY1);
            break;

        case 2:     /* blink to center */
            PORTD |= (1 << LED0);
            _delay_ms(DELAY1);
            PORTD |= (1 << LED5);
            _delay_ms(DELAY1);
            PORTD |= (1 << LED1);
            _delay_ms(DELAY1);
            PORTD |= (1 << LED4);
            _delay_ms(DELAY1);
            PORTD |= (1 << LED2);
            _delay_ms(DELAY1);
            PORTD |= (1 << LED3);
            _delay_ms(DELAY1);
            PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
            (1 << LED3) | (1 << LED4) | (1 << LED5));
            _delay_ms(DELAY1);
            break;

        case 3:     /* scrolling lights */
            PORTD |= (1 << LED0);
            PORTD &= ~(1 << LED1);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED1);
            PORTD &= ~(1 << LED0);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED2);
            PORTD &= ~(1 << LED1);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED3);
            PORTD &= ~(1 << LED2);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED4);
            PORTD &= ~(1 << LED3);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED5);
            PORTD &= ~(1 << LED4);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED4);
            PORTD &= ~(1 << LED5);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED3);
            PORTD &= ~(1 << LED4);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED2);
            PORTD &= ~(1 << LED3);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED1);
            PORTD &= ~(1 << LED2);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED0);
            PORTD &= ~(1 << LED1);
            _delay_ms(0);
            break;

        case 4:
            PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
            (1 << LED3) | (1 << LED4) | (1 << LED5));
            _delay_ms(DELAY0);
            
            /* ascend on */
            PORTD |= (1 << LED0);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED1);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED2);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED3);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED4);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED5);
            _delay_ms(DELAY0);

            /* ascend off */
            PORTD &= ~(1 << LED0);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED1);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED2);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED3);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED4);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED5);
            _delay_ms(DELAY0);

            PORTD &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) |
            (1 << LED3) | (1 << LED4) | (1 << LED5));
            _delay_ms(DELAY0);

            /* descend on */
            PORTD |= (1 << LED5);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED4);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED3);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED2);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED1);
            _delay_ms(DELAY0);
            PORTD |= (1 << LED0);
            _delay_ms(DELAY0);

            /* descend off */
            PORTD &= ~(1 << LED5);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED4);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED3);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED2);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED1);
            _delay_ms(DELAY0);
            PORTD &= ~(1 << LED0);
            _delay_ms(DELAY0);
            break;
        
        case 5:     /* reset */
            pattern = 1;
            _delay_ms(DELAY0);
            break;

        default:
            break;
        }
        
        if ((PINC & (1 << SW1)) == 0) {
            ++pattern;
            _delay_ms(DELAY1);
        }

    }
    return 0;
}