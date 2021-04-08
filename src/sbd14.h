#ifndef __SBD_10_H__
#define __SBD_10_H__

#include "mas001.h"

struct SBD14_SETTINGS{
	// Settings
	bool direction;
	bool opt1_enable;
	bool opt1_stop_on_high;

	bool opt2_enable;
	bool opt2_stop_on_high;

	uint16_t speed;
	uint32_t position;
};

struct SBD14_STATE{
	// State
	bool abnormal;
	bool opt1;
	bool opt2;
	uint16_t speed;	
};

typedef struct{
	uint8_t id;
	struct SBD14_SETTINGS settings;
	struct SBD14_STATE state;
}SBD14_INSTANCE;

class SBD14{
public:
	SBD14(long timeout = 1000);

	bool set_ID(SBD14_INSTANCE *motor, uint8_t target_id);
	bool set_Speed(SBD14_INSTANCE *motor);
	bool read_State(SBD14_INSTANCE *motor);
	bool move_Speed(SBD14_INSTANCE *motor);
	bool move_Position(SBD14_INSTANCE *motor);

private:
	uint8_t sendframe[10];
	uint8_t readframe[10];
	uint8_t rx_len;

	bool transmitReceive(uint8_t id);
};

#endif