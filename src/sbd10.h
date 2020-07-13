#ifndef __SBD_10_H__
#define __SBD_10_H__

#include "mas001.h"

class SBD10{
public:
	void init();
	void enable(uint8_t value);
	void direction(uint8_t value);
	void continuousPulse(uint16_t pulse_us);
	void burstPulse(uint16_t pulse_us, uint32_t cnt = 0);
};

#endif