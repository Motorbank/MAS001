#ifndef __DMD_150_H__
#define __DMD_150_H__

#include "mas001.h"

class DMD150{
public:
	DMD150();

	void brake();
	void floating();
	void rotation(int16_t spd);
};

#endif