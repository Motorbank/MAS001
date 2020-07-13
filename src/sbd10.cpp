#include "sbd10.h"

#define EN_PIN	5
#define DIR_PIN	6
#define STP_PIN	9

volatile static uint32_t pulse_cnt = 0;

void SBD10::init(){
	pinMode(EN_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	digitalWrite(EN_PIN, LOW);
	digitalWrite(DIR_PIN, LOW);

	// Init Timer 1
	pinMode(STP_PIN, OUTPUT);
	TCCR1A = 0B10000010;  // Clear OC1A on compare match / Fast PWM
    TCCR1B = 0B00011010; // Fast PWM / timer_clock = (16/64)MHz = 250kHz
	TCNT1 = 0;
	OCR1A = 0;
	ICR1 = 0xFFFF;
}

void SBD10::enable(uint8_t value){
	digitalWrite(EN_PIN, value);
}

void SBD10::direction(uint8_t value){
	digitalWrite(DIR_PIN, value);
}

void SBD10::continuousPulse(uint16_t pulse_us){
	if(pulse_us == 0){
		ICR1 = 0xFFFF;
		OCR1A = 0;
		return;
	}

	if(pulse_us > 0x3FFF) pulse_us = 0x3FFF;
	ICR1 = (pulse_us << 2) - 1;
	OCR1A = ICR1 >> 1;
  	
}

void SBD10::burstPulse(uint16_t pulse_us, uint32_t cnt = 0){
	ICR1 = 0xFFFF;
	OCR1A = 0;
	if(pulse_us == 0) return;
	if(pulse_us > 0x3FFF) pulse_us = 0x3FFF;

	pulse_cnt = 0;
	noInterrupts();
	TIMSK1 = 1;
	ICR1 = (pulse_us << 2) - 1;
	OCR1A = ICR1 >> 1;
	interrupts();

	while(pulse_cnt < cnt + 1);

	TIMSK1 = 0;
	ICR1 = 0xFFFF;
	OCR1A = 0;

}

ISR(TIMER1_OVF_vect){
	pulse_cnt ++;
}