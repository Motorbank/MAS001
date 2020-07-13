#include "mas001.h"
#include "sbd10.h"

MAS001 myShield;
SBD10 myDevice;
void setup() {
  myDevice.init();
  Serial.begin(115200);
}

void loop() {

  if(myShield.button1Clicked()){
    myDevice.enable(LOW);
    myDevice.direction(HIGH);
    myDevice.burstPulse(500, 3000);
    myDevice.direction(LOW);
    myDevice.burstPulse(250, 1000);
    myDevice.burstPulse(0);
    delay(200);
    myDevice.burstPulse(250, 1000);
    myDevice.burstPulse(0);
    delay(200);
    myDevice.burstPulse(250, 1000);
    myDevice.burstPulse(0);
    delay(200);
  }else{
    myDevice.enable(HIGH);
    myDevice.continuousPulse(0);
  }

  delay(50);
}