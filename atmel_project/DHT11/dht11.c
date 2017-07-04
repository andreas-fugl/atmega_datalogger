/*
 * DHT11.c
 *
 *  Created on: 02-01-2013
 *      Author: mentos
 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "dht11.h"

dht11_data_t DHT11_GetData(void) {
	dht11_data_t data;
	uint8_t bits[5];
	uint8_t i, j = 0;

	//reset port
	DHT11_DDR |= (1 << DHT11_INPUTPIN); //output
	DHT11_PORT |= (1 << DHT11_INPUTPIN); //high
	_delay_ms(100);

	//send request
	DHT11_PORT &= ~(1 << DHT11_INPUTPIN); //low
	_delay_ms(18);
	DHT11_PORT |= (1 << DHT11_INPUTPIN); //high
	_delay_us(1);
	DHT11_DDR &= ~(1 << DHT11_INPUTPIN); //input
	_delay_us(39);

	//check start condition 1
	if ((DHT11_PIN & (1 << DHT11_INPUTPIN))) {
		data.valid = false;
		return data;
	}
	_delay_us(80);
	//check start condition 2
	if (!(DHT11_PIN & (1 << DHT11_INPUTPIN))) {
		data.valid = false;
		return data;
	}
	_delay_us(80);

	//read the data
	for (j = 0; j < 5; j++) { //read 5 byte
		uint8_t result = 0;
		for (i = 0; i < 8; i++) { //read every bit
			while (!(DHT11_PIN & (1 << DHT11_INPUTPIN)))
				; //wait for an high input
			_delay_us(30);
			if (DHT11_PIN & (1 << DHT11_INPUTPIN)) //if input is high after 30 us, get result
				result |= (1 << (7 - i));
			while (DHT11_PIN & (1 << DHT11_INPUTPIN))
				; //wait until input get low
		}
		bits[j] = result;
	}

	//reset port
	DHT11_DDR |= (1 << DHT11_INPUTPIN); //output
	DHT11_PORT |= (1 << DHT11_INPUTPIN); //low
	_delay_ms(100);

	//check checksum
	
	if (bits[0] + bits[1] + bits[2] + bits[3] == bits[4]) {
		data.valid = true;
		data.temperature = bits[2];
		data.humidity = bits[0];
	}
	else {
		data.valid = false;
	}

	return data;
}