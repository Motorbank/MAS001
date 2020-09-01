#include "mas001.h"
#include "blc150.h"

MAS001 myShield;
BLC150 myDevice;

void setup() {

}

void loop() {

  if(myShield.button1Clicked()) myDevice.enable(LOW);
  else myDevice.enable(HIGH);

  if(myShield.button2Clicked()) myDevice.direction(LOW);
  else myDevice.direction(HIGH);

  delay(50);
}
