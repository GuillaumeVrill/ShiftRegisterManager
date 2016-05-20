#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>
#include "ShiftRegisterManager.h"

int main(void){
	
	ShiftRegisterManager *srm = new ShiftRegisterManager(8, 7, 6, 5);
	
	int *b = new int[8];
	b[0] = 1;
	b[1] = 1;
	b[2] = 0;
	b[3] = 0;
	b[4] = 1;
	b[5] = 1;
	b[6] = 1;
	b[7] = 1;
	srm->setBus(b, 8);
	srm->writeRegister();
	delay(2000);
	for(int i=0; i<8; i++){
		b[i] = 0;
	}
	srm->setBus(b, 8);
	srm->writeRegister();
	
	return 0;
	
}
