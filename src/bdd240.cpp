#include "bdd240.h"

#define EN_PIN	5
#define DIR_PIN	6
#define FG_PIN	9

void BDD240::init(){
	pinMode(EN_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	pinMode(EN_PIN, HIGH);
	digitalWrite(DIR_PIN, LOW);

	// Init Timer 1
	pinMode(FG_PIN, OUTPUT);
	TCCR1A = 0B10000010;  // Clear OC1A on compare match / Fast PWM
    TCCR1B = 0B00011011; // Fast PWM / timer_clock = (16/64)MHz = 250kHz
	TCNT1 = 0;
	OCR1A = 0;
	ICR1 = 2499; // 100Hz

}

void BDD240::enable(uint8_t value){
	digitalWrite(EN_PIN, value);
}

void BDD240::setSpeed(float duty){
	if(duty < -100) duty = -100;
	else if(duty > 100) duty = 100;

	if(duty >= 0) digitalWrite(DIR_PIN, HIGH);
	else{
		digitalWrite(DIR_PIN, LOW);
		duty = -duty;
	}

	OCR1A = (uint16_t)(duty * 24.99f);
}