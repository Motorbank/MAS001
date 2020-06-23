#include "mas001.h"
#include "blc200.h"

#define DEVICE_ID  0

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint16_t pos_input;
uint16_t pos_output;
void setup() {
  Serial.begin(115200);
}

void loop() {
  
  pos_input = myShield.getPot() * 16;

  if(myShield.button1Clicked()){
    // ID = 0, CCW, POS = (pos_input/100)DEGREE, SPD = 100RPM
    myDevice.set_PositionWithSpeed(DEVICE_ID, 0, pos_input, 1000); 
  }else{
    // ID = 0, CW, POS = (pos_input/100)DEGREE, SPD = 100RPM
    myDevice.set_PositionWithSpeed(DEVICE_ID, 1, pos_input, 1000); 
  }

  // Get Current position
  if(myDevice.get_Feedback(DEVICE_ID, 0xA1)){
    pos_output = (uint16_t)myDevice.blcData[2] << 8 | (uint16_t)myDevice.blcData[3];
    Serial.println(pos_output);
  }
  
  delay(100);
  
}
