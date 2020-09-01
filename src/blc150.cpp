#include "blc150.h"

#define EN_PIN	6
#define DIR_PIN	5

BLC150::BLC150(){
	pinMode(EN_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
}

void BLC150::enable(uint8_t value){
	digitalWrite(EN_PIN, value);
}

void BLC150::direction(uint8_t value){
	digitalWrite(DIR_PIN, value);
}