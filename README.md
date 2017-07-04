# atmega_datalogger

Datalogger project using an Atmega328p connected to RPi via USART. 
Uses a DHT11 sensor connected via GPIO. Uses the USART to send data to the RPi. 
On the RPi a small Python scripts parses the serial data and publishes it to 
Adafruit I/O
