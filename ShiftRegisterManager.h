#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>

//Classe ShiftRegister:
class ShiftRegisterManager{
	
	private:
	int SER_Pin;	// Pin de VALEUR
	int RCLK_Pin;	// Pin du VALIDATEUR
	int SRCLK_Pin;	// Pin du passage au SUIVANT
	int *bus;		// Le bus de valeur (la file)
	int *real_bus;	// Le bus réel qui correspond à la réalisation physique
	int bus_length;	// La taille du bus
	int real_bus_length;	//La taille réelle du bus
	
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
	
	//Fonction d'initialisation des GPIO:
	int init(){
		//initialisation de wiringPi
		if(wiringPiSetup()==-1)
			return 0;
		
		pinMode(SER_Pin, OUTPUT);
		pinMode(RCLK_Pin, OUTPUT);
		pinMode(SRCLK_Pin, OUTPUT);
		return 1;
	}
	
	//Fonction d'écriture du bus sur le shift register:
	void writeRegister(){
		//récupération du bus réel et complétion du surplus avec des 0:
		for(int i=0; i<bus_length; i++){
			real_bus[i]=bus[i];
		}
		for(int i=bus_length; i<real_bus_length; i++){
			real_bus[i] = 0;
		}
		//Mise en attente du shift:
		digitalWrite(RCLK_Pin, 0);
		//Préparation de la file:
		for(int i=real_bus_length-1; i>=0; i--){
			//En attente de valeur:
			digitalWrite(SRCLK_Pin, 0);
			int val = real_bus[i];
			//Ajout de la valeur:
			digitalWrite(SER_Pin, val);
			//On pousse les valeurs:
			digitalWrite(SRCLK_Pin, 1);
		}
		//Passage des valeurs en simultanné sur le shift:
		digitalWrite(RCLK_Pin, 1);
		//Message de debug (si necessaire):
		//printf("write registers done \n");
	}
	
	//Fonction de réinitialisation des bus:
	void clearBus(){
		for(int i=0; i<bus_length; i++){
			bus[i]=0;
		}
		writeRegister();
	}
	
	//Récupération de la taille du bus
	int getBusLength(){
		return bus_length;
	}
	
	//Paramétrage de la taille du bus
	void setBusLength(int bus_l){
		bus_length = bus_l;
	}
	
	//Récupération du bus
	int *getBus(){
		return bus;
	}
	
	//Paramétrage du bus
	void setBus(int *b, int tb){
		for(int i=tb-1; i>=0; i--){
			bus[i] = b[i];
		}
	}
	
	//Passage d'un pin à 1
	void setPinOn(int position){
		if(position >= 0 && position < bus_length){
			bus[position] = 1;
		}
	}
	
	//Passage d'un pin à 0
	void setPinOff(int position){
		if(position >= 0 && position < bus_length){
			bus[position] = 0;
		}
	}
	
	//Passage de tout le bus à 1
	void setAllPinOn(){
		for(int i=0; i<bus_length; i++){
			bus[i] = 1;
		}
	}
	
	//Passage de tout le bus à 0
	void setAllPinOff(){
		for(int i=0; i<bus_length; i++){
			bus[i] = 0;
		}
	}
	
};
