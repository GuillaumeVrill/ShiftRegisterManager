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
	int *bus;		//	Le bus de valeur (la file)
	int taille_bus;	//	La taille du bus
	
	public:
	//constructeur:
	ShiftRegisterManager(int taille_b, int Pin_valeur, int Pin_validateur, int Pin_suivant){
		taille_bus = taille_b;
		SER_Pin = Pin_valeur;
		RCLK_Pin = Pin_validateur;
		SRCLK_Pin = Pin_suivant;
		bus = new int[taille_bus];
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
		//Mise en attente du shift:
		digitalWrite(RCLK_Pin, 0);
		//Préparation de la file:
		for(int i=0; i<taille_bus; i++){
			//En attente de valeur:
			digitalWrite(SRCLK_Pin, 0);
			int val = bus[i];
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
		for(int i=taille_bus-1; i>=0; i--){
			bus[i]=0;
		}
		writeRegister();
	}
	
	//Fonctions de manipulation du Bus:
	int getTailleBus(){
		return taille_bus;
	}
	
	void setTailleBus(int t_bus){
		taille_bus = t_bus;
	}
	
	void setBus(int *b, int tb){
		for(int i=tb-1; i>=0; i--){
			bus[i] = b[i];
			//printf("%d \n",bus[i]);
		}
	}
	
};
