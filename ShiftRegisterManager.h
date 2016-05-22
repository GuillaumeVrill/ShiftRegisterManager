#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>

//Classe ShiftRegister:
class ShiftRegisterManager{
	
	private:
	int SER_Pin;	// VALUE Pin
	int RCLK_Pin;	// VALIDATOR Pin
	int SRCLK_Pin;	// Next Pin
	int *bus;		// Value bus (contains the 1 and 0 values the user want to output)
	int *real_bus;	// Real bus (length is dividable by 8), contain the values that will be printed, invisible for user
	int bus_length;	// Bus length for user
	int real_bus_length;	// Real bus length (invisible for the user, dividable by 8)
	
	public:
	ShiftRegisterManager(int bus_l, int Pin_value, int Pin_validator, int Pin_next){
		bus_length = bus_l;
		SER_Pin = Pin_value;
		RCLK_Pin = Pin_validator;
		SRCLK_Pin = Pin_next;
		bus = new int[bus_length];
		real_bus_length = bus_length;
		while(real_bus_length%8 != 0){
			real_bus_length++;
		}
		real_bus = new int[real_bus_length];
		init();
		clearBus();
	}
	
	//Initialisation of the GPIO and libraries:
	int init(){
		//wiringPi init
		if(wiringPiSetup()==-1)
			return 0;
		
		pinMode(SER_Pin, OUTPUT);
		pinMode(RCLK_Pin, OUTPUT);
		pinMode(SRCLK_Pin, OUTPUT);
		return 1;
	}
	
	//Writing function of the Shift Register (print the outputs)
	void writeRegister(){
		//updating the real bus to print the outputs:
		for(int i=0; i<bus_length; i++){
			real_bus[i]=bus[i];
		}
		for(int i=bus_length; i<real_bus_length; i++){
			real_bus[i] = 0;
		}
		//put the shift waiting:
		digitalWrite(RCLK_Pin, 0);
		//preparing the values to output (reverse reading of the bus):
		for(int i=real_bus_length-1; i>=0; i--){
			//waiting for value:
			digitalWrite(SRCLK_Pin, 0);
			int val = real_bus[i];
			//add value to the shift (actual output):
			digitalWrite(SER_Pin, val);
			//go to next value (next output):
			digitalWrite(SRCLK_Pin, 1);
		}
		//put the shift ON (displaying the outputs):
		digitalWrite(RCLK_Pin, 1);
	}
	
	//reset the bus (user bus):
	void clearBus(){
		for(int i=0; i<bus_length; i++){
			bus[i]=0;
		}
		writeRegister();
	}
	
	//Get the bus length:
	int getBusLength(){
		return bus_length;
	}
	
	//set the bus length:
	void setBusLength(int bus_l){
		bus_length = bus_l;
	}
	
	//Get the bus
	int *getBus(){
		return bus;
	}
	
	//Set the bus
	void setBus(int *b, int bus_l){
		if(bus_l <= bus_length){
			for(int i=bus_l-1; i>=0; i--){
				bus[i] = b[i];
			}
		}
		else{
			printf("taille du bus incorrecte");
		}
	}
	
	//Set an output ON (to 1):
	void setPinOn(int position){
		if(position >= 0 && position < bus_length){
			bus[position] = 1;
		}
	}
	
	//Set an output OFF (to 0):
	void setPinOff(int position){
		if(position >= 0 && position < bus_length){
			bus[position] = 0;
		}
	}
	
	//Set all outputs ON:
	void setAllPinOn(){
		for(int i=0; i<bus_length; i++){
			bus[i] = 1;
		}
	}
	
	//Set all outputs OFF:
	void setAllPinOff(){
		for(int i=0; i<bus_length; i++){
			bus[i] = 0;
		}
	}
	
};
