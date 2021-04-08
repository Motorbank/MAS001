#include "sbd14.h"
#include <SoftwareSerial.h>
#include <string.h>

#define RS485_EN	digitalWrite(RS485_DE, HIGH)
#define RS485_DIS	digitalWrite(RS485_DE, LOW)

SoftwareSerial comm485(RS485_RX, RS485_TX);

SBD14::SBD14(long timeout = 1000){

	sendframe[0] = 0x5A;
	sendframe[1] = 0xA5;

	comm485.begin(9600);
	comm485.setTimeout(timeout);
	pinMode(RS485_DE, OUTPUT);

	RS485_DIS;
}

bool SBD14::set_ID(SBD14_INSTANCE *motor, uint8_t target_id){

	sendframe[2] = 0x06;
	sendframe[3] = motor->id;
	sendframe[4] = 0x10;
	sendframe[5] = 0x10;
	sendframe[6] = 0x01;
	sendframe[7] = 0x00;
	sendframe[8] = target_id;

	rx_len = 8;

	if(!transmitReceive(target_id)) return false;

	if(readframe[6] != 0x00) return false;
	if(readframe[7] != target_id) return false;

	motor->id = target_id;

	return true;
}

bool SBD14::set_Speed(SBD14_INSTANCE *motor){

	sendframe[2] = 0x06;
	sendframe[3] = motor->id;
	sendframe[4] = 0x10;
	sendframe[5] = 0x14;
	sendframe[6] = 0x01;
	sendframe[7] = (uint8_t)(motor->settings.speed >> 8);
	sendframe[8] = (uint8_t)motor->settings.speed;

	rx_len = 8;

	if(!transmitReceive(motor->id)) return false;

	if(readframe[6] != sendframe[7]) return false;
	if(readframe[7] != sendframe[8]) return false;

	motor->state.speed = motor->settings.speed;
	return true;
}

bool SBD14::read_State(SBD14_INSTANCE *motor){

	sendframe[2] = 0x06;
	sendframe[3] = motor->id;
	sendframe[4] = 0x10;
	sendframe[5] = 0x19;
	sendframe[6] = 0x01;
	sendframe[7] = 0x00;
	sendframe[8] = 0x00;

	rx_len = 10;

	if(!transmitReceive(motor->id)) return false;

	if(readframe[6] != motor->id) return false;

	motor->state.opt1 = (readframe[7] & 0x01) != 0 ? true : false;
	motor->state.opt2 = (readframe[7] & 0x02) != 0 ? true : false;
	motor->state.abnormal = (readframe[7] & 0x04) != 0 ? true : false;
	motor->state.speed = ((uint16_t)readframe[8] << 8) | (uint16_t)readframe[9];

	return true;
}

bool SBD14::move_Speed(SBD14_INSTANCE *motor){

	sendframe[2] = 0x06;
	sendframe[3] = motor->id;
	sendframe[4] = 0x10;
	sendframe[5] = 0x21;
	sendframe[6] = 0x01;

	sendframe[7] = 0x00;
	sendframe[8]  = motor->settings.opt2_stop_on_high ? 0x01 : 0x00;
	sendframe[8] |= motor->settings.opt1_stop_on_high ? 0x02 : 0x00;
	sendframe[8] |= motor->settings.opt2_enable ? 0x04 : 0x00;
	sendframe[8] |= motor->settings.opt1_enable ? 0x08 : 0x00;
	sendframe[8] |= motor->settings.direction ? 0x10 : 0x00;

	rx_len = 8;

	if(!transmitReceive(motor->id)) return false;

	if(readframe[6] != 0x00) return false;
	if(readframe[7] != sendframe[8]) return false;

	return true;
}

bool SBD14::move_Position(SBD14_INSTANCE *motor){

	sendframe[2] = 0x08;
	sendframe[3] = motor->id;
	sendframe[4] = 0x10;
	sendframe[5] = 0x41;
	sendframe[6] = 0x02;

	sendframe[7]  = motor->settings.opt2_stop_on_high ? 0x01 : 0x00;
	sendframe[7] |= motor->settings.opt1_stop_on_high ? 0x02 : 0x00;
	sendframe[7] |= motor->settings.opt2_enable ? 0x04 : 0x00;
	sendframe[7] |= motor->settings.opt1_enable ? 0x08 : 0x00;
	sendframe[7] |= motor->settings.direction ? 0x10 : 0x00;


	sendframe[8]  = (uint8_t)(motor->settings.position >> 16);
	sendframe[9]  = (uint8_t)(motor->settings.position >> 8);
	sendframe[10] = (uint8_t)motor->settings.position;

	rx_len = 10;

	if(!transmitReceive(motor->id)) return false;

	if(readframe[6] != sendframe[7]) return false;
	if(readframe[7] != sendframe[8]) return false;
	if(readframe[8] != sendframe[9]) return false;
	if(readframe[9] != sendframe[10]) return false;

	return true;
}

bool SBD14::transmitReceive(uint8_t id){
	RS485_EN;
	comm485.write(sendframe, sendframe[2] + 3);
	RS485_DIS;

	comm485.readBytes(readframe, rx_len);

	delay(50); // 50ms delay needed

	int i;
	Serial.print("\n>> ");
	for(i = 0; i < rx_len; i++){
		Serial.print(readframe[i]);
		Serial.print(" ");
	}
	Serial.println("");

	// Check frame
	if(readframe[0] != 0x5A) return false;
	if(readframe[1] != 0xA5) return false;
	if(readframe[2] != (rx_len - 3)) return false;
	if(readframe[3] != id) return false;
	if(readframe[4] != sendframe[4]) return false;
	if(readframe[5] != sendframe[5]) return false;

	while(comm485.available() > 0)comm485.read(); // Flush bufer

	return true;
}