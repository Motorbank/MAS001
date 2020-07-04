#include "mas001.h"
#include "dmd150.h"

MAS001 myShield;
DMD150 myMotor;

void setup() {

}

int val;
void loop() {
  val = myShield.getPot();
  
  if(myShield.button1Clicked()){
  	myMotor.floating(); // Use floating function to soft stop
  	// myMotor.brake(); // Use brake function to hard stop
  }else if(myShield.button2Clicked()){
  	// rotation funtion takes input from -255 ~ 255
  	myMotor.rotation(-val / 4);
  }else{
  	myMotor.rotation(val / 4);
  }
}