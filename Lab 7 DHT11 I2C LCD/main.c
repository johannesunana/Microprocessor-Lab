#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <util/delay.h>

#include "lib/dht.h"
#include "lib/lcdpcf8574.h"

int32_t main(void) {            /* Initialize Setup */
    int8_t temperature = 0;     /* temperature variable */
    int8_t humidity = 0;        /* humidity variable */
    int8_t printbuff[100];      /* string buffer */

    lcd_init(LCD_DISP_ON);      /* initialize LCD */
    lcd_led(0);                 /* enable backlight */
    lcd_puts("Starting up");
    _delay_ms(500);
    lcd_clrscr();               /* clear LCD screen */
    
    while(1) {                  /* Loop */
        if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {
            itoa(temperature, printbuff, 10);   /* convert integer to string */
            
            lcd_home();         /* go to top left LCD location */
            if (temperature < 10) {  /* check if temperature is single digit */
                lcd_puts("Temperature:  ");
                lcd_puts(printbuff);    /* display temperature value */
            }
            else {
                lcd_puts("Temperature: ");
                lcd_puts(printbuff);
            }
            lcd_puts("C");
            lcd_puts("\n");

            itoa(humidity, printbuff, 10);
            if (humidity < 10) {     /* check if humidity is single digit */
                lcd_puts("Humidity:     ");
                lcd_puts(printbuff);    /* display humidity value */
            }
            else {
                lcd_puts("Humidity:    ");
                lcd_puts(printbuff);
            }
            lcd_puts("%");
            _delay_ms(1500);    /* 1.5 second delay before repeating loop*/
        }   /* end of if condition */

        else {  /* display message when sensor is warming up or not detected */
            lcd_puts("Check connection\n");
            lcd_puts("                ");
        }
    }   /* end of while loop */
}   /* end of main function */