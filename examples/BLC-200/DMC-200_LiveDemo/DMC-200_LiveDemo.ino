#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0
#define GEAR_RATIO 100 // Caution! Reduction ratio is (0.1*GEAR_RATIO)
/*****************************************************************************/

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint16_t rated_speed;
uint16_t pos_input;
void setup() {
  Serial.begin(115200);

  Serial.println("*********************************************");
  Serial.println("* Position control with Serial Console");
  Serial.println("*********************************************");
  
  // [[ Read rated speed from driver ]]
  Serial.print("Read rated speed [RPM] : ");
  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    rated_speed = (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2];
    Serial.println(rated_speed);
  }else{
    Serial.println("Fail..");
    while(1);
  }

  myDevice.set_ReductionRatio(DEVICE_ID, GEAR_RATIO);

}

void loop() {
  pos_input = myShield.getPot() * 64; // 1024 to 65536
  if(myShield.button1Clicked()){
    myDevice.set_PositionWithSpeed(DEVICE_ID, 1, pos_input, rated_speed * 10);
  }else if(myShield.button2Clicked()){
    myDevice.set_PositionWithSpeed(DEVICE_ID, 1, 0, rated_speed * 10);
  }else{
    myDevice.set_PositionWithSpeed(DEVICE_ID, 0, pos_input, rated_speed * 10);
  }

  delay(10);
}