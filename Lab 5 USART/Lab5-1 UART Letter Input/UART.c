#include <avr/io.h>
#include "UART.h"
#include <util/setbaud.h>

void Uart_Init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif    
    UCSR0B = (1 << RXEN0) | (1<< TXEN0);  /* enable receiver and transmitter */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void Uart_Putc(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));     /* Wait for empty transmit buffer */
    UDR0 = data;                          /* send data */
}

uint8_t Uart_Getc(void) {
    while (!(UCSR0A & (1 << RXC0)));     /* Wait for incoming data */
    return UDR0;                         /* return register value */
}

void Uart_Puts(const int8_t *s) {
    while (*s) {
        Uart_Putc(*s++);
    }
}

/*  This is a modified Gets that will print back the inputed character while
    string is being saved. The string is terminated with a carriage return
    and the MaxLen  */

void Uart_Gets(int8_t *Buffer, int32_t MaxLen) {
    char NextChar;
    char StringLen = 0;

    NextChar = Uart_Getc();     /* gets the first character of the string */
    Uart_Putc(NextChar);        /* and prints it */

    /*  check if the maximum length has been reached or
        if carriage return has been detected  */
    while((NextChar != '\r') && (StringLen < MaxLen - 1)) {
        *Buffer++ = NextChar;
        StringLen++;
        NextChar = Uart_Getc();
        Uart_Putc(NextChar);
    }
    Buffer = '\0';
}
