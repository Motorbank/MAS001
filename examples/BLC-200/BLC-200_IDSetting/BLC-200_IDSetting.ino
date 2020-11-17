#include "blc200.h"

#define ID          0x00
#define ID_TARGET   0x01

BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Driver ID example.");
}

void loop() {

  myDevice.set_ID(ID, ID_TARGET);
  delay(500);
  if(myDevice.get_Feedback(ID_TARGET, 0xA0)) Serial.println("Success!");
  else Serial.println("Fail to change id..");

  while(1);
}
