#! /usr/bin/python

import serial
from time import sleep

ending = chr(13) + chr(10);

bluetoothSerial = serial.Serial("/dev/rfcomm1", baudrate=9600)

command = "SN"; #send data
count = 1;

while True:
	print "C " + str(count) + ":"
	bluetoothSerial.write(command + str(count) + ending)
	response = bluetoothSerial.readline()
	print response
	count = count + 1
#sleep(1);

