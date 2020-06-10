#include "blc200.h"

BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

void setup() {
  Serial.begin(115200);
  Serial.println("Start Scanning BLC driver series...");
}

void loop() {
  
  int i;
  
  for(i = 0; i < 256; i++){
    Serial.print("Device "); Serial.print(i); Serial.print(" : ");
    if(myDevice.get_Feedback(i, 0xA0)) Serial.println("OK");
    else Serial.println("Not exist");
  }

  Serial.println("Finish scanning!");

  while(1);
}
