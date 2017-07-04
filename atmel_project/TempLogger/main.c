//#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include <stdbool.h>
#include <stdint.h>


#include "../USART/usart.h"
#include "../DHT11/dht11.h"


//char String[]="123\n\r";    //String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text
//#define LED_DDR DDRD
#define LED_PORT PORTD

void led_init(void) {
	DDRD |= 0xFC; // all pins as output, except PD0 and PD1
	DDRB |= 0x03; // set PB0 and PB1 as output
}

void show_led(const uint8_t data) {
	PORTD = 0xFC & data;
	PORTB = 0x03 & data;
}

int main(void){
	led_init();
	USART_init();
	
	stdout = &mystdout;
	
	while(1){
		dht11_data_t data;
		data = DHT11_GetData();
		
		if (data.valid) {	
			printf("%u %u\r\n", data.temperature, data.humidity);
			
			show_led(data.temperature);
			_delay_ms(1000);
			show_led(data.humidity);
			_delay_ms(1000);
			show_led(0);
		}
		
		_delay_ms(3000);
	}	
	return 0;
}