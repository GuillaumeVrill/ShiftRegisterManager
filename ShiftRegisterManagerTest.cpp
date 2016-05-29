#include "ShiftRegisterManager.h"

int main(void){
	
	ShiftRegisterManager *srm = new ShiftRegisterManager(6, 7, 6, 5);
	
	srm->setAllPinOff();
	srm->writeRegister();
	delay(2000);
	srm->setAllPinOff();
	srm->setPinOn(0);
	srm->setPinOn(4);
	srm->setPinOn(5);
	srm->writeRegister();
	delay(2000);
	
	srm->setAllPinOff();
	srm->writeRegister();
	delay(2000);
	
	return 0;
	
}
