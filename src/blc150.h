#ifndef __BLC_150_H__
#define __BLC_150_H__

#include "mas001.h"

class BLC150{
public:
	BLC150();

	void enable(uint8_t value);
	void direction(uint8_t value);
};

#endif