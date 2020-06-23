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
uint16_t spd_output;
uint16_t spd_input;
uint16_t prop_gain;

void setup() {
  Serial.begin(115200);

  // [[ Read rated speed from driver ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    rated_speed = (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2];
  }else while(1);

  prop_gain = rated_speed / 1000;
}

void loop() {

  // [[ Mapping potentiometer value to motor speed ]]
  spd_input = myShield.getPot() * prop_gain;
  
  if(myShield.button1Clicked()){
    if(myShield.button2Clicked()){
      myDevice.set_SpeedWithTime(DEVICE_ID, 0, spd_input * 10, SPD_SETTIME); 
    }else{
      myDevice.set_SpeedWithTime(DEVICE_ID, 1, spd_input * 10, SPD_SETTIME); 
    }     
  }else{
    myDevice.set_SpeedWithTime(DEVICE_ID, 1, 0, SPD_SETTIME); 
  }   
  
  // [[ Get Current speed ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA1)){
    spd_output = (uint16_t)myDevice.blcData[4] << 8 | (uint16_t)myDevice.blcData[5];
    Serial.print(spd_input); Serial.print("\t"); Serial.println(spd_output / 10);
  }
  
  delay(100);
  
}