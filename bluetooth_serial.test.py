#! /usr/bin/python

import serial
from time import sleep

ending = chr(10);

bluetoothSerial = serial.Serial("/dev/rfcomm1", baudrate=9600)

command = "@$"
command += chr(1)
command += chr(8)
command += chr(2)
command += chr(5)
command += chr(3)
command += chr(6)
command += chr(7)
command += ending #send data

cmdSend = "@>" + ending

count = 1;


#while True:
print "C " + str(count) + ":"
bluetoothSerial.write(command)
response = bluetoothSerial.readline()
print response
count = count + 1
sleep(3);

while True:
	print "C " + str(count) + ":"
	bluetoothSerial.write(cmdSend)
	response = bluetoothSerial.readline()
	print response
	count = count + 1
	sleep(0.5);

