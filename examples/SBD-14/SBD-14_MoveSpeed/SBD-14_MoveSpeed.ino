#include "mas001.h"
#include "sbd14.h"

/*****************************************************************************/
// User Configuration
#define DEVICE_ID 0     // Current ID
/*****************************************************************************/

MAS001 myShield;

SBD14 myDevice(100); // Serial timeout = 100ms;
SBD14_INSTANCE motor;

void setup() {
  Serial.begin(115200);
  Serial.println("Start SBD-14 Speed mode");

  motor.id = DEVICE_ID;
  motor.settings.opt1_enable = false;
  motor.settings.opt2_enable = false;
  
}

void loop() {
  // Set speed
  if(myShield.button2Clicked()) motor.settings.speed = 0;
  else motor.settings.speed = myShield.getPot() * 5;
  myDevice.set_Speed(&motor);

  // Move motor
  motor.settings.direction = myShield.button1Clicked();
  myDevice.move_Speed(&motor);
}