#include "mas001.h"
#include "bdd240.h"

MAS001 myShield;
BDD240 myDevice;

void setup() {
  myDevice.init();
  Serial.begin(115200);
}

void loop() {

  if(myShield.button1Clicked()){
    myDevice.enable(LOW);

    if(myShield.button2Clicked()){
      myDevice.setSpeed((float)myShield.getPot() * 0.098); // [0 ~ 1024] to [0 ~ 100]
    }else{
      myDevice.setSpeed(-(float)myShield.getPot() * 0.098); // [0 ~ 1024] to [0 ~ 100]
    }
    
  }else{
    myDevice.enable(HIGH);
    myDevice.setSpeed(0);
  }

  delay(100);
}