#include "blc200.h"

#define ID          0x00
#define ID_TARGET   0x01

BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Driver ID example.");
}

void loop() {

  if(myDevice.get_Feedback(ID, 0xA0)){
  	Serial.println("There is no target device! Error..");
  }else{
  	myDevice.set_ID(ID, ID_TARGET);
    Serial.println("ID change command sended!. Please Turn the power of and on!");
  }

  while(1){

  	delay(1000);
  	Serial.print(".");
  	if(myDevice.get_Feedback(ID_TARGET, 0xA0)){
  		Serial.print("Success!");
  		while(1);
  	}
  	
  }
}
