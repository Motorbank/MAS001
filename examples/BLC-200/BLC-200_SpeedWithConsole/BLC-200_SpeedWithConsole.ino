#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0
#define SPD_SETTIME 1 // // Caution! Speed set time is (0.1*SPD_SETTIME) second
/*****************************************************************************/

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

int rated_speed;
int spd_input;
void setup() {
  Serial.begin(115200);

  Serial.println("*********************************************");
  Serial.println("* Speed control with Serial Console");
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
  Serial.print("Enter Motor speed (0 ~ "); Serial.print(rated_speed); Serial.print(") [RPM] : ");
  while(!Serial.available());
  
  spd_input = Serial.parseInt();

  if(spd_input > rated_speed) spd_input = rated_speed;
  else if(spd_input < -rated_speed) spd_input = -rated_speed;
  
  if(spd_input > 0) myDevice.set_SpeedWithTime(DEVICE_ID, 0, spd_input * 10, SPD_SETTIME);
  else myDevice.set_SpeedWithTime(DEVICE_ID, 1, -spd_input * 10, SPD_SETTIME);
  Serial.println(spd_input);
  while(Serial.available()) Serial.read();

}