#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0
#define SPD_SETTIME 1 // Caution! Speed set time is (0.1*SPD_SETTIME) second
/*****************************************************************************/

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint8_t dir;
uint16_t cnt;
uint16_t sub_cnt;
uint16_t rated_speed;
uint16_t pos_input;
void setup() {
  Serial.begin(115200);
  
  // [[ Read rated speed from driver ]]
  Serial.print("Read rated speed [RPM] : ");
  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    rated_speed = (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2];
    Serial.println(rated_speed);
  }else{
    Serial.println("Fail..");
    while(1);
  }
}

void loop() {

  cnt ++;
  if(cnt < 100){
    
    // [[ Position Control ]]
    sub_cnt ++;
    if(sub_cnt % 10 == 0) pos_input += 9000;
    myDevice.set_PositionWithSpeed(DEVICE_ID, 0, pos_input, rated_speed / 4); 
    
  }else if(cnt < 200){
    
    // [[ Speed Control ]]
    sub_cnt ++;
    if(sub_cnt % 50 == 0) dir = dir == 0 ? 1 : 0;
    myDevice.set_SpeedWithTime(DEVICE_ID, dir, rated_speed * 5, SPD_SETTIME * 10);
    
  }else{
    cnt = 0;  
    sub_cnt = 0;
    pos_input = 0;
    myDevice.set_SpeedWithTime(DEVICE_ID, dir, 0, SPD_SETTIME * 10);
    delay(1000);
    myDevice.set_PositionInit(DEVICE_ID);
  }
  
  delay(50);
}