#include "mas001.h"
#include "blc200.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID   0
#define RATED_SPEED 4000 // [RPM]
#define RESOLUTION  1000
#define REDUCTION_RATIO 10 // Caution! Input ratio is (0.1*REDUCTION_RATIO) : 1
#define POSITION_MODE 0 // 0 : Absolute Control | 1 : Relative Control
#define POSITION_DIR  0 // 0 : CCW | 1 : CW
/*****************************************************************************/

MAS001 myShield;
BLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

void setup() {
  Serial.begin(115200);
}

void loop() {

  Serial.println("*********************************************");
  Serial.println("* Motor Driver Setting Start                *");
  Serial.println("*********************************************");
    
  // [[ Set Motor Rated Speed ]]
  Serial.print("* Set Rated Speed [RPM] : "); Serial.println(RATED_SPEED);
  myDevice.set_RatedSpeed(DEVICE_ID, RATED_SPEED);  

  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    Serial.print("\t→ Rated Speed [RPM] : ");
    Serial.print((uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]);
    if(RATED_SPEED == (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]) Serial.println("... OK!");
    else{
      Serial.println("...Fail");
      while(1);  
    }
  }
  
  // [[ 1. Set Resolution ]]
  Serial.print("* Set Sensor Resolution : "); Serial.println(RESOLUTION);
  myDevice.set_Resolution(DEVICE_ID, RESOLUTION);

  if(myDevice.get_Feedback(DEVICE_ID, 0xA7)){
    Serial.print("\t→ Sensor Resolution : ");
    Serial.print((uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]);
    if(RESOLUTION == (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]) Serial.println("... OK!");
    else{
      Serial.println("...Fail");
      while(1);  
    }
  }

  // [[ Set Reduction Ratio ]]
  Serial.print("* Set Reduction Ratio : "); Serial.println(REDUCTION_RATIO);
  myDevice.set_ReductionRatio(DEVICE_ID, REDUCTION_RATIO);

  if(myDevice.get_Feedback(DEVICE_ID, 0xA8)){
    Serial.print("\t→ Reduction Ratio : ");
    Serial.print((uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]);
    if(REDUCTION_RATIO == (uint16_t)myDevice.blcData[1] << 8 | (uint16_t)myDevice.blcData[2]) Serial.println("... OK!");
    else{
      Serial.println("...Fail");
      while(1);  
    }
  }

  // [[ Set Position Control Mode ]]
  Serial.print("* Set Position Mode : "); Serial.println(POSITION_MODE == 0 ? "Absolute" : "Relative");
  myDevice.set_PositionMode(DEVICE_ID, POSITION_MODE);

  if(myDevice.get_Feedback(DEVICE_ID, 0xAA)){
    Serial.print("\t→ Position Mode : ");
    Serial.print(myDevice.blcData[1] == 0 ? "Absolute" : "Relative");
    if(POSITION_MODE == myDevice.blcData[1]) Serial.println("... OK!");
    else{
      Serial.println("...Fail");
      while(1);  
    }
  }  

  // [[ Set Control Direction ]]
  Serial.print("* Set Control Direction : "); Serial.println(POSITION_DIR == 0 ? "CCW" : "CW");
  myDevice.set_PositionDirection(DEVICE_ID, POSITION_DIR);

  if(myDevice.get_Feedback(DEVICE_ID, 0xAB)){
    Serial.print("\t→ Position Mode : ");
    Serial.print(myDevice.blcData[1] == 0 ? "CCW" : "CW");
    if(POSITION_DIR == myDevice.blcData[1]) Serial.println("... OK!");
    else{
      Serial.println("...Fail");
      while(1);  
    }
  }  

  Serial.println("** Finish !! **");
  
  while(1);
}