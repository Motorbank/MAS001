#include "mas001.h"

MAS001::MAS001(){
	pinMode(MAS_BTN1, INPUT);
	pinMode(MAS_BTN2, INPUT);
}

bool MAS001::button1Clicked(){
	if(digitalRead(MAS_BTN1) == LOW) return true;
	return false;
}

bool MAS001::button2Clicked(){
	if(digitalRead(MAS_BTN2) == LOW) return true;
	return false;
}

uint16_t MAS001::getPot(){
	return analogRead(MAS_POT);
}