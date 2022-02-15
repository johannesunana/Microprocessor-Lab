#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#define USART_HAS_DATA  ((UCSR0A & (1 << RXC0)) == 1)
#define USART_READY     ((UCSR0A & (1 << UDRE0) == 1)
#define BAUD            9600

void Uart_Init(void);
void Uart_Putc(uint8_t data );
uint8_t Uart_Getc(void);

void Uart_Puts(const int8_t *s);
void Uart_Gets(int8_t *Buffer, int32_t MaxLen);

#endif