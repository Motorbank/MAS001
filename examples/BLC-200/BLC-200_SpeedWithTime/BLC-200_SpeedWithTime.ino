#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0
#define SPD_SETTIME 1 // // Caution! Speed set time is (0.1*SPD_SETTIME) second
/*****************************************************************************/

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint16_t rated_speed;
float spd_input;
uint16_t spd_output;
void setup() {
  Serial.begin(115200);

  Serial.println("*********************************************");
  Serial.println("* Speed Controller Start");
  Serial.println("*********************************************");

  // [[ Read rated speed from driver ]]
  Serial.print("Read rated speed [RPM] : ");
  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    rated_speed = (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2];
    Serial.println(rated_speed);
  }else{
    Serial.println("Reading Fail...");
    while(1);
  }

}

void loop() {
  
  // [[ Mapping potentiometer value to motor speed ]]
  spd_input = (float)myShield.getPot() / 1024.0f;
  spd_input *= (float)rated_speed * 10.0f;

  if(myShield.button1Clicked()){
    if(myShield.button2Clicked()){
      myDevice.set_SpeedWithTime(DEVICE_ID, 0, (uint16_t)spd_input, SPD_SETTIME); 
    }else{
      myDevice.set_SpeedWithTime(DEVICE_ID, 1, (uint16_t)spd_input, SPD_SETTIME); 
    }     
  }else{
    myDevice.set_SpeedWithTime(DEVICE_ID, 1, 0, SPD_SETTIME); 
  }

  // Get Current speed
  if(myDevice.get_Feedback(DEVICE_ID, 0xA2)){
    spd_output = (uint16_t)myDevice.blcData[2] << 8 | (uint16_t)myDevice.blcData[3];
    Serial.println(spd_output);
  }
  
  delay(50);
  
}
