#include "mas001.h"
#include "blc200.h"

#define DEVICE_ID  0

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint8_t set_time;
uint16_t pos_output;
void setup() {
  Serial.begin(115200);
}

void loop() {
  
  set_time = (uint8_t)(myShield.getPot() >> 2);

  if(myShield.button1Clicked()){
    // ID = 0, CCW, POS = 180 DEGREE, TIME = (set_time/10)s
    myDevice.set_PositionWithTime(DEVICE_ID, 0, 18000, set_time); 
  }else{
    // ID = 0, CW, POS = 180 DEGREE, TIME = (set_time/10)s
    myDevice.set_PositionWithTime(DEVICE_ID, 1, 18000, set_time); 
  }

  // Get Current position
  if(myDevice.get_Feedback(DEVICE_ID, 0xA1)){
    pos_output = (uint16_t)myDevice.blcData[2] << 8 | (uint16_t)myDevice.blcData[3];
    Serial.println(pos_output);
  }
  
  delay(100);
  
}
