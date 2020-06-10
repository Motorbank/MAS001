#include "mas001.h"
#include "dlc200.h"

#define DEVICE_ID 0

MAS001 myShield;
DLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint16_t spd_input;
uint16_t spd_output;
void setup() {
  Serial.begin(115200);
}

void loop() {
  
  spd_input = myShield.getPot();

  if(myShield.button1Clicked()){
    if(myShield.button2Clicked()){
      // ID = 0, CCW, SPD = (spd_input/10)RPM, TIME = 0.1s
      myDevice.set_SpeedWithTime(DEVICE_ID, 0, spd_input, 1); 
    }else{
      // ID = 0, CW, SPD = (spd_input/10)RPM, TIME = 0.1s
      myDevice.set_SpeedWithTime(DEVICE_ID, 1, spd_input, 1); 
    }     
  }else{
    myDevice.set_SpeedWithTime(DEVICE_ID, 1, 0, 1); 
  }

  // Get Current speed
  if(myDevice.get_Feedback(DEVICE_ID, 0xA2)){
    spd_output = (uint16_t)myDevice.dlcData[2] << 8 | (uint16_t)myDevice.dlcData[3];
    Serial.println(spd_output);
  }
  
  delay(100);
  
}
