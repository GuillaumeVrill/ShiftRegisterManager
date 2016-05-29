# ShiftRegisterManager

A C++ Class based on wiringPi library (made by Gordon Hendersons >> https://projects.drogon.net/raspberry-pi/wiringpi/ ).
It allows an easier manipulation of the "74HC595N" shift registers with the fonctions i defined.
-- Soon i'll try to make this class independent of wiringPi library, and maybe i'll translate those into Python --
 
 
## Description
 
The 74HC595N SR (SR for shift Register) allows the raspberry Pi to have "unlimited" outputs to control. 
With only 3 of the controllable outputs (GPIO) of the raspberry pi, the GND and the 5V Pins, we can control 8 outputs on one SR.
But we can extend this to 65536 (maximum supported electronically), with the possibility of cascading the SRs. 
That's really powerfull, but they need to be used as a programming file ("first in, first out").
That's why we need some algorithms to use it properly, and i decided to make some fonctions to simplify it. 
 
 
## My configuration
 
 Note: Normally, it should function with every Raspberry Pi, but if this is not the case, here is my hardware and software configuration:
 
	- Raspberry Pi B
	- wiringPi installed
	- Compilation with g++ (not gcc): g++ ShiftRegisterManagerTest.cpp -o testSR -l wiringPi
	- I used GPIO7, GPIO6, and GPIO5 in the .cpp test file.
	- You'll find a picture of the electronic configuration i used in the files i placed on GitHub. 
	
 For more informations, go to this website on witch i based my work on (french): http://blog.idleman.fr/raspberry-pi-20-creer-un-tableau-de-bord-connect-au-net/
 
 
## Installation
 
- For the C++ class, you need to link it at the top of your .cpp file: include "ShiftRegisterManager.h"
- For the Python file that contains the functions: comming soon...
 
 
## C++ Class Functions
 
First to know, when you'll declare and define a ShitRegisterManager in your code, you'll need to declare an object:
ShiftRegisterManager *mySRM = new ShiftRegisterManager(8, 7, 6, 5);
So when you'll call a function, don't forget the arrow: mySRM->clearBus();
 
	- void writeRegister(): after configuring the outputs bus with the values you want to send to the SR, call this function. 
		Example: mySRManager->setPinOn(5); mySRManager->writeRegister();
		Explanation: We put the output number 5 of the SR ON, and then we send this to the SR using writeRegister().
	 
	- void clearBus(): Put all the outputs OFF.
	 
	- int getBusLength(): Know the length of the actual bus.
	 
	- void setBusLength(int bus_l): Change the length of the actual bus to bus_l, and clear the Bus then (create a new bus, called in the constructor)
	 
	- void setPinOn(int position): set the Pin at the position given ON.
	 
	- void setPinOff(int position): set the Pin at the position given OFF.
	 
	- void setAllPinOn(): set all the pins OF THE BUS ON.
	 
	- void setAllPinOf(): set all the pins OF THE BUS OFF.

 Don't forget to call writeRegister() after every modification (except for clearBus() that already calls it). 


## Next to come

- A C++ class without wiringPi needed. 
- A Python file containing the functions and variables i used in C++. 
