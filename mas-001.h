#ifndef __MAS_001_H__
#define __MAS_001_H__

#include "Arduino.h"

#define RS485_RX	10
#define RS485_TX	2
#define RS485_DE	3

#define MAS_BTN1	13
#define MAS_BTN2	12
#define MAS_POT		A0


class MAS001{
public:
	MAS001();

	bool button1Clicked();
	bool button2Clicked();
	uint16_t getPot();
};

#endif