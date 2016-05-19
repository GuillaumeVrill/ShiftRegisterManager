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
	int *bus;		//Le bus de valeur (la file)
	int taille_bus;	//La taille du bus
	
	public:
	//constructeur:
	ShiftRegisterManager(int taille_bus, int Pin_valeur, int Pin_validateur, int Pin_suivant){
		this.taille_bus = taille_bus;
		this.SER_Pin = Pin_valeur;
		this.RCLK_Pin = Pin_validateur;
		this.SRCLK_Pin = Pin_suivant;
		this.bus = new int[this.taille_bus];
		init();
		clearBus();
	}
	
	//Fonction d'initialisation des GPIO:
	void init(){
		pinMode(SER_Pin, OUTPUT);
		pinMode(RCLK_Pin, OUTPUT);
		pinMode(SRCLK_Pin, OUTPUT);
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
		writeRegisters();
	}
	
	//Fonctions de manipulation du Bus:
	int getTaileBus(){
		return this.taille_bus;
	}
	
	void seTailleBus(int t_bus){
		this.taille_bus = t_bus;
	}
	
	
	
}
