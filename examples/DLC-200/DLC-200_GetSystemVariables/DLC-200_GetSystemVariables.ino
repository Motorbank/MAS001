#include "mas-001.h"
#include "dlc-200.h"

#define DEVICE_ID 0

MAS001 myShield;
DLC200 myDevice(9600, 100); // Baudrate = 9600, Serial timeout = 100ms

uint16_t spd;
void setup() {
  Serial.begin(115200);
}

void loop() {

  Serial.println("*********************************************");
  
  // [[ 1. Send Ping ]]
  Serial.print("Send ping frame ...");
  if(!myDevice.get_Feedback(DEVICE_ID, 0xA0)){
    Serial.println("Fail...");
    while(1);
  }
  Serial.println("OK!");

  // [[ 2. Get Position controller feedback ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA3)){
    Serial.println("* Position Controller Feedback");
    Serial.print("\tKp : "); Serial.println(myDevice.dlcData[1]);
    Serial.print("\tKi : "); Serial.println(myDevice.dlcData[2]);
    Serial.print("\tKd : "); Serial.println(myDevice.dlcData[3]);
    Serial.print("\tRated Current [A] : "); Serial.println((float)myDevice.dlcData[4] * 0.1);
  }

  // [[ 3. Get Speed controller feedback ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA4)){
    Serial.println("* Speed Controller Feedback");
    Serial.print("\tKp : "); Serial.println(myDevice.dlcData[1]);
    Serial.print("\tKi : "); Serial.println(myDevice.dlcData[2]);
    Serial.print("\tKd : "); Serial.println(myDevice.dlcData[3]);
    Serial.print("\tRated Current [A] : "); Serial.println((float)myDevice.dlcData[4] * 0.1);
  }  

  // [[ 4. Get Response time ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA5)){
    Serial.print("* Communication Response Time [ms] : ");
    Serial.println((float)myDevice.dlcData[1] * 0.1);
  }

  // [[ 5. Get Rated speed ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA6)){
    Serial.print("* Motor Rated Speed [RPM] : ");
    Serial.println((uint16_t)myDevice.dlcData[1] << 8 | (uint16_t)myDevice.dlcData[2]);
  }

  // [[ 6. Get Resolution ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA7)){
    Serial.print("* Sensor resolution : ");
    Serial.println((uint16_t)myDevice.dlcData[1] << 8 | (uint16_t)myDevice.dlcData[2]);    
  }

  // [[ 6. Get Reduction ratio ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xA8)){
    Serial.print("* Reduction Ratio : ");
    Serial.println((uint16_t)myDevice.dlcData[1] << 8 | (uint16_t)myDevice.dlcData[2]);    
  }

  // [[ 7. Get Position control mode ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xAA)){
    Serial.print("* Position Control Mode : ");
    if(myDevice.dlcData[1] == 0x00) Serial.println("Absolute");
    else if(myDevice.dlcData[1] == 0x01) Serial.println("Relative");  
  }

  // [[ 8. Get Control direction ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xAB)){
    Serial.print("* Control Direction : ");
    if(myDevice.dlcData[1] == 0x00) Serial.println("CCW");
    else if(myDevice.dlcData[1] == 0x01) Serial.println("CW");  
  }

  // [[ 9. Get Firmware version ]]
  if(myDevice.get_Feedback(DEVICE_ID, 0xCD)){
    Serial.print("* Firmware Version : ");
    Serial.println(myDevice.dlcData[1]);
  }  
  
  while(1);
}
