import serial
import time

from programmercontrolCLI import *




###HOW TO USE THIS FILE:

#1-
#Set the serial port to whichever one your writeboi is currently using.
#This will usually be "COM3" on Windows, or "/dev/ttyUSB0" on Unix-based systems
#If in doubt, check with the Arduino IDE

serialport = "COM3";

programmer = serial.Serial(port=serialport, baudrate=115200,timeout=3);
time.sleep(4);


#2-
#Type in here the operation you would like to perform, then run the python interpreter.

###OPERATION GOES HERE

pass;

###


#Example commands:

##Read ROM header from catridge:
#printCartridgeHeader(programmer, interface="MBC");

##Read ROM header from file:
#printFileHeader(filename="file.gb")

##Read 32KB of ROM from cartridge, save to a file:
#chunkRead(programmer,filename="file.gb",numkb=32,interface="MBC5",targetIC="ROM"):

##Write 32KB from a file to the cartridge's flash memory:
#chunkWrite(programmer,filename="file.gb",numkb=32,interface="MBC5",targetIC="SST"):



#################################################################################

###Detailed description of possible commands:

##printCartridgeHeader(targetdevice, interface)
#reads the ROM header from a cartridge or flash IC, and prints it in a human-readable form
#Arguments:
#targetdevice: Serial port being used. For this file, should always be the programmer object defined above.
#interface: Physical interface for the programmer to use. Possible values: "MBC", "DIP"


##printFileHeader(filename)
#Reads the ROM header from a file, prints it in a human-readable form
#Note that the file must be at least 1KB long.
#Arguments:
#filename: file to read from


##chipErase(targetdevice,interface,targetIC)
#Fully erases a target flash IC.
#This is called automatically when performing flash write operations, unless you specifically set erase=False on them
#Arguments:
#targetdevice: Serial port being used. For this file, should always be the programmer object defined above.
#interface: Physical interface for the programmer to use. Possible values: "MBC1", "MBC5", "DIP"
#targetIC: Model of the chip to be erased. Possible values: "SST", "M29", "M29Chip2"
#Note that "M29Chip2" is only available when using the "MBC5" interface


##chunkRead(targetdevice,filename,numkb,interface,targetIC="ROM",startkb=0)
#Reads specified amount of data from a cartridge or flash IC, and saves it to a file.
#Arguments:
#targetdevice: Serial port being used. For this file, should always be the programmer object defined above.
#filename: filename to save as
#numkb: Amount of data to read, in kilobytes
#interface: Physical interface for the programmer to use. Possible values: "MBC1", "MBC5", "DIP"
#targetIC: Chip to read from. Possible values: "ROM", "RAM"
#startkb: position to start reading from, in kilobytes. Useful for reading just a section of a ROM


##chunkWrite(targetdevice,filename,numkb,interface,targetIC,erase=True,startoffset=0)
#Writes specified amount of data, from a file, to the target cartridge or flash IC.
#Arguments:
#targetdevice: Serial port being used. For this file, should always be the programmer object defined above.
#filename: name of the source file
#numkb: Amount of data to write, in kilobytes. Values above 2048 are only supported on MBC5.
#interface: Physical interface for the programmer to use. Possible values: "MBC1", "MBC5", "DIP"
#targetIC: Chip to read from. Possible values: "SST", "M29", "RAM"
#erase: Whether the chip should be erased before writing. Necessary for flash chips, has no effect on RAM
#startoffset: position to start writing from, in kilobytes. Useful for appending data to a partly-written ROM




