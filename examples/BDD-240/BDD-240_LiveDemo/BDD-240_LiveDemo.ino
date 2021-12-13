#include "mas001.h"
#include "bdd240.h"

MAS001 myShield;
BDD240 myDevice;

float spd;
bool dir;

void setup() {
  myDevice.init();
  Serial.begin(115200);

  spd = 0;
  dir = true;
}

void loop() {

  if(myShield.button1Clicked()){

    if(dir){
      spd += 1;
      if(spd > 100) dir = false;
    }else{
      spd -= 1;
      if(spd < -100) dir = true;
    }
    
    myDevice.enable(LOW);
    myDevice.setSpeed(spd);
    
  }else{
    spd = 0;    
    myDevice.enable(HIGH);
    myDevice.setSpeed(0);
  }

  delay(25);
}