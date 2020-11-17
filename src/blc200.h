#ifndef __BLC_200_H__
#define __BLC_200_H__

#include "mas001.h"

#define BUFF_LEN	16

class BLC200{
public:
	BLC200(uint16_t baudrate, long timeout = 1000);

	uint8_t blcData[BUFF_LEN];

	// Protocol MC-RS485_V1.0.1
	void set_PositionWithSpeed(uint8_t ID, uint8_t CW, uint16_t POS, uint16_t SPD);	// 1. 위치, 속도제어 (송신)
	void set_PositionWithTime(uint8_t ID, uint8_t CW, uint16_t POS, uint8_t TIME);	// 2. 가감속 위치제어 (송신)
	void set_SpeedWithTime(uint8_t ID, uint8_t CW, uint16_t SPD, uint8_t TIME);	// 3. 가감속 속도제어 (송신)
	//void set_PositionController(); 		// 4. 위치제어기 설정 (송신)
	//void set_SpeedController(); 		// 5. 속도제어기 설정 (송신)
	void set_ID(uint8_t ID, uint8_t target_ID); // 6. ID 설정 (송신)
	//void set_Buadrate(); 				// 7. 통신속도 설정 (송신)
	//void set_ResponseTime(); 			// 8. 통신 응답시간 설정 (송신)
	void set_RatedSpeed(uint8_t ID, uint16_t RPM);	// 9. 모터 정격속도 설정 (송신)
	void set_Resolution(uint8_t ID, uint16_t resolution);	// 10. 분해능 설정 (송신)
	void set_ReductionRatio(uint8_t ID, uint16_t reductionRatio);	// 11. 감속비 설정 (송신)
	//void set_ControllerOn(); 			// 12. 제어 On/Off 설정 (송신)
	void set_PositionMode(uint8_t ID, uint8_t MODE);	// 13. 위치제어 모드 설정 (송신)
	void set_PositionDirection(uint8_t ID, uint8_t DIR);	// 14. 제어 방향 설정 (송신)
	void set_PositionInit(uint8_t ID); // 15. 위치 초기화 (송신)
	void set_FactorySetting(uint8_t ID);												// 16. 공장 초기화 (송신)

	bool get_Feedback(uint8_t ID, uint8_t Mode); 				// 17. 피드백 요청 (송신)

private:
	uint8_t sendframe[BUFF_LEN];
	uint8_t readframe[BUFF_LEN];
	uint8_t tx_len, rx_len;
	bool transmitReceive(bool recv);
	void getChecksum();
};

#endif