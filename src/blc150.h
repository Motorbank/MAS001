#ifndef __BLC_150_H__
#define __BLC_150_H__

#include "mas001.h"

class BLC150{
public:
	BLC150();
	
	void turnOn();
	void turnOff();
	void changeDirection(uint8_t dir);
};

#endif