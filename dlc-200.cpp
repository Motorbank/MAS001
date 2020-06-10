#include "dlc-200.h"
#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial dlc485(RS485_RX, RS485_TX);

DLC200::DLC200(uint16_t baudrate, long timeout = 1000){
	sendframe[0] = 0xFF;
	sendframe[1] = 0xFE;

	dlc485.begin(baudrate);
	dlc485.setTimeout(timeout);
	pinMode(RS485_DE, OUTPUT);
	RS485_DIS;
}

void DLC200::set_PositionWithSpeed(uint8_t ID, uint8_t CW, uint16_t POS, uint16_t SPD){
	// Create frame
	sendframe[2] = ID;
	sendframe[3] = 0x07;
	sendframe[5] = 0x01;
	sendframe[6] = CW & 0x01;
	sendframe[7] = (uint8_t)(POS >> 8);
	sendframe[8] = (uint8_t)POS;
	sendframe[9] = (uint8_t)(SPD >> 8);
	sendframe[10] = (uint8_t)SPD;

	tx_len = 11;
	getChecksum();

	transmitReceive(false);
}

void DLC200::set_PositionWithTime(uint8_t ID, uint8_t CW, uint16_t POS, uint8_t TIME){
	// Create frame
	sendframe[2] = ID;
	sendframe[3] = 0x06;
	sendframe[5] = 0x02;
	sendframe[6] = CW & 0x01;
	sendframe[7] = (uint8_t)(POS >> 8);
	sendframe[8] = (uint8_t)POS;
	sendframe[9] = TIME;

	tx_len = 10;
	getChecksum();

	transmitReceive(false);
}

void DLC200::set_SpeedWithTime(uint8_t ID, uint8_t CW, uint16_t SPD, uint8_t TIME){
	// Create frame
	sendframe[2] = ID;
	sendframe[3] = 0x06;
	sendframe[5] = 0x03;
	sendframe[6] = CW & 0x01;
	sendframe[7] = (uint8_t)(SPD >> 8);
	sendframe[8] = (uint8_t)SPD;
	sendframe[9] = TIME;

	tx_len = 10;
	getChecksum();

	transmitReceive(false);
}

void DLC200::set_FactorySetting(uint8_t ID){
	// Create frame
	sendframe[2] = ID;
	sendframe[3] = 0x02;
	sendframe[5] = 0x10;

	tx_len = 6;
	getChecksum();

	transmitReceive(false);
}

bool DLC200::get_Feedback(uint8_t ID, uint8_t Mode){
	rx_len = 5;
	switch(Mode){
		case 0xA0: rx_len += 1; break;
		case 0xA1: rx_len += 7; break;
		case 0xA2: rx_len += 7; break;
		case 0xA3: rx_len += 5; break;
		case 0xA4: rx_len += 5; break;
		case 0xA5: rx_len += 2; break;
		case 0xA6: rx_len += 3; break;
		case 0xA7: rx_len += 3; break;
		case 0xA8: rx_len += 3; break;
		case 0xA9: rx_len += 2; break;
		case 0xAA: rx_len += 2; break;
		case 0xAB: rx_len += 2; break;
		case 0xCD: rx_len += 2; break;
		default : return false;
	}

	sendframe[2] = ID;
	sendframe[3] = 0x02;
	sendframe[5] = Mode;

	tx_len = 6;
	getChecksum();

	return transmitReceive(true);
}

void DLC200::getChecksum(){
	uint8_t i;
	uint8_t checksum = 0x00;
	for(i = 2; i < tx_len; i++){
		if(i != 4) checksum += sendframe[i];
	}
	sendframe[4] = ~checksum;
}

bool DLC200::transmitReceive(bool recv){
	RS485_EN;
	dlc485.write(sendframe, tx_len);
	RS485_DIS;

	if(!recv) return true;

	dlc485.readBytes(readframe, rx_len);

	// Check frame
	if(readframe[0] != 0xFF) return false;
	if(readframe[1] != 0xFE) return false;
	if(readframe[2] != sendframe[2]) return false;

	if(readframe[3] + 4 != rx_len) return false;

	uint8_t checksum = 0;
	uint8_t i;
	for(i = 2; i < rx_len; i ++){
		if(i != 4) checksum += readframe[i];
	}
	if(readframe[4] != (uint8_t)(~checksum)) return false;

	// Copy data
	memset(dlcData, 0x00, BUFF_LEN);
	memcpy(dlcData, readframe + 5, rx_len - 5);

	while(dlc485.available() > 0) dlc485.read(); // Flush buffer 

	return true;
}