#include "mas001.h"
#include "sbd14.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0     // Current ID
#define TARGET_ID 1     // Target ID
#define SPEED     6400  // [step/s]
/*****************************************************************************/

MAS001 myShield;

SBD14 myDevice(100); // Serial timeout = 100ms;
SBD14_INSTANCE motor;

void setup() {
  Serial.begin(115200);
  Serial.println("Press button 1 to start device setting.");
  while(!myShield.button1Clicked());
}

void loop() {

  // [[ 1. Check device is available ]]
  motor.id = DEVICE_ID;
  if(!myDevice.read_State(&motor)){
    Serial.println("* No device found.");
    while(1);
  }else{
    Serial.println("* Target device found.");
  }

  // [[ 2. Change id ]]
  Serial.print("* ID setting ");
  if(!myDevice.set_ID(&motor, TARGET_ID)){
    Serial.println("fail.");
    while(1);
  }else{
    Serial.println("success.");
  }

  // [[ 3. Set speed ]]
  motor.settings.speed = SPEED;
  
  Serial.print("* Speed setting ");
  if(!myDevice.set_Speed(&motor)){
    Serial.println("fail.");
    while(1);
  }else{
    Serial.println("success.");
  }
  
  // [[ 4. Check parameters ]]
  Serial.println("----------------------------------------");
  if(myDevice.read_State(&motor)){
    Serial.print("condition : ");
    Serial.print(motor.state.abnormal ? "abnormal" : "normal");
    Serial.print(" | opt1 : ");
    Serial.print(motor.state.opt1 ? "High" : "Low");
    Serial.print(" | opt2 : ");
    Serial.print(motor.state.opt2 ? "High" : "Low");
    Serial.print(" | speed [step/s] : ");
    Serial.println(motor.state.speed);
  }else{
      Serial.println("Not available");
  } 
  
  Serial.println("Finish device setting!");

  while(1);  
}