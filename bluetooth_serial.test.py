#! /usr/bin/python

import serial
from time import sleep

bluetoothSerial = serial.Serial("/dev/rfcomm1", baudrate=9600)

count = None

while count == None:
    try:
        count = int(raw_input("Please enter a number"))
    except:
        pass # Ignore any error and try again

bluetoothSerial.write(str(count) + chr(13) + chr(10))
print bluetoothSerial.readline()

