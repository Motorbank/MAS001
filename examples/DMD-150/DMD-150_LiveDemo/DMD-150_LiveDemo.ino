#include "mas001.h"
#include "dmd150.h"

MAS001 myShield;
DMD150 myMotor;

void setup() {

}

uint8_t upspd;
int spd;
void loop() {

  if(myShield.button1Clicked()){
    myMotor.floating();
    spd = 0;
  }else{
  
    if(upspd){
      spd ++;
      if(spd >= 255) upspd = 0;  
    }else{
      spd --;
      if(spd <= -255) upspd = 1;  
    }
  
    myMotor.rotation(spd);    
    
  }

  
  delay(10);
  
}