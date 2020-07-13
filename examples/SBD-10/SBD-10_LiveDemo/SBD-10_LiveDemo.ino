#include "mas001.h"
#include "sbd10.h"

MAS001 myShield;
SBD10 myDevice;
void setup() {
  myDevice.init();
  Serial.begin(115200);
}

uint8_t dir;
uint8_t loopCnt;
void loop() {

  if(myShield.button1Clicked()){
    myDevice.enable(LOW);
    myDevice.direction(dir);
    myDevice.continuousPulse(1000);
  }else{
    myDevice.enable(HIGH);
    myDevice.continuousPulse(0);
    loopCnt = 0;
    dir = LOW;
  }

  loopCnt ++;
  if(loopCnt >= 80){
    loopCnt = 0;
    dir = (dir == HIGH) ? LOW : HIGH;
    Serial.println(dir);
  }
  
  delay(50);
}