#include "mas001.h"
#include "sbd14.h"

MAS001 myShield;

SBD14 myDevice(100); // Serial timeout = 100ms;
SBD14_INSTANCE motor;

void setup() {
  Serial.begin(115200);
  Serial.println("Start Scanning SBD-14 driver...");
}

void loop() {
  
  int i;
  for(i = 0; i < 128; i++){
    Serial.print("[");
    Serial.print(i);
    Serial.print("] ");
    motor.id = i;
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
  }
  
  Serial.println("Finish scanning!");

  while(1);  
}