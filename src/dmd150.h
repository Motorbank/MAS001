#ifndef __DMD_150_H__
#define __DMD_150_H__

#include "mas001.h"

#define IN1_PIN	5
#define IN2_PIN	6
#define PWM_PIN	9

class DMD150{
public:
	DMD150();

	void brake();
	void floating();
	void rotation(int16_t spd);
};

#endif