#include "mas001.h"
#include "dmd150.h"

MAS001 myShield;
DMD150 myMotor;

void setup() {

}

int val;
void loop() {
  val = myShield.getPot();
  
  if(myShield.button1Clicked()) myMotor.floating();
  else if(myShield.button2Clicked()) myMotor.rotation(-val / 4);
  else myMotor.rotation(val / 4);
  
}