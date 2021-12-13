#ifndef __BDD_240_H__
#define __BDD_240_H__

#include "mas001.h"

class BDD240{
public:
	void init();
	void enable(uint8_t value);
	void setSpeed(float duty);
};

#endif