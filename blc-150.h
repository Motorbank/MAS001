#ifndef __BLC_150_H__
#define __BLC_150_H__

#include "mas-001.h"

#define EN_PIN	6
#define DIR_PIN	5

class BLC150{
public:
	BLC150();
	
	void turnOn();
	void turnOff();
	void changeDirection(uint8_t dir);
};

#endif