#ifndef USART_H
#define USART_H

#include <stdio.h>

#include <avr/io.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)


//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int
uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	//loop_until_bit_is_set(UCSRA, UDRE);
	//UDR = c;
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
	
	return 0;
}

#endif