#include "dmd150.h"

#define IN1_PIN	5
#define IN2_PIN	6
#define PWM_PIN	9

DMD150::DMD150(){
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(PWM_PIN, OUTPUT);
}

void DMD150::brake(){
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, LOW);
	analogWrite(PWM_PIN, 0);
}

void DMD150::floating(){
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, HIGH);
	analogWrite(PWM_PIN, 0);	
}

void DMD150::rotation(int16_t spd){
	if(spd > 255) spd = 255;
	else if(spd < -255) spd = -255;

	if(spd > 0){
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		analogWrite(PWM_PIN, spd);
	}else{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		analogWrite(PWM_PIN, -spd);		
	}
	
}