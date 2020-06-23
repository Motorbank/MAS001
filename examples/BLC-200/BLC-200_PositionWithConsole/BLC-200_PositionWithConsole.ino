#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0
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

}

void loop() {
  Serial.print("Enter Motor Position (0 ~ 65533) [0.01Degree] : ");
  while(!Serial.available());
  pos_input = Serial.parseInt();
  if(myShield.button2Clicked()){
    myDevice.set_PositionWithSpeed(DEVICE_ID, 1, pos_input, rated_speed * 10);
  }else{
    myDevice.set_PositionWithSpeed(DEVICE_ID, 0, pos_input, rated_speed * 10);
  }
  
  Serial.println(pos_input);
  while(Serial.available()) Serial.read();

}
