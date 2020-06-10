#include "blc150.h"

BLC150::BLC150(){
	pinMode(EN_PIN, INPUT);
	pinMode(DIR_PIN, INPUT);
}

void BLC150::turnOn(){
	digitalWrite(EN_PIN, HIGH);
}

void BLC150::turnOff(){
	digitalWrite(EN_PIN, LOW);
}

void BLC150::changeDirection(uint8_t dir){
	if(dir == 1) digitalWrite(DIR_PIN, HIGH);
	else if(dir == 0) digitalWrite(DIR_PIN, LOW);
}