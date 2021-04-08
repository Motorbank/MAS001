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
  Serial.println("Start SBD-14 Position mode");

  motor.id = DEVICE_ID;
  motor.settings.speed = 6400;
  motor.settings.opt1_enable = false;
  motor.settings.opt2_enable = false;
  myDevice.set_Speed(&motor);
}

void loop() {
  motor.settings.position = 16000;
  motor.settings.direction = true;
  myDevice.move_Position(&motor);

  delay(3000);
  
  motor.settings.position = 16000;
  motor.settings.direction = true;
  myDevice.move_Position(&motor);

  delay(3000);
  
  motor.settings.position = 32000;
  motor.settings.direction = false;
  myDevice.move_Position(&motor);

  delay(6000);
}