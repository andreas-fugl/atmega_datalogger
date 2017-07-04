#!/usr/bin/env python
from Adafruit_IO import Client
import serial

aio = Client('ce41a95f9b964ebabdc8f4da5af4eb25')
ser = serial.Serial('/dev/ttyAMA0', 9600)

while True:
	line = ser.readline()
	data = line.split()
	temp = data[0]
	rh = data[1]
	aio.send('Temperature', temp)
	aio.send('RH', rh)
