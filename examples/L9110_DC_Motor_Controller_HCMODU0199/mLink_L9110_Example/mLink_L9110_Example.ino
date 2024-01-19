/* FILE:    mLink_L9110_Example.ino
   DATE:    15/01/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to control the speed and direction 
of two DC motors connected to the modules two driver outputs.

To use this sketch connect the first motor to terminals 1A & 1B and
the second motor to terminals 2A & 2B. Connect power for the motors
to the positive 1+ and 2+ terminals respectively and 0V to the GND 
terminals.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x5D                        // Default I2C address


void setup() 
{
  mLink.init();                             // Initialise the library

  // Stop both motors
  mLink.L9110_M1_Stop(I2C_ADD);
  mLink.L9110_M2_Stop(I2C_ADD);
}


void loop() 
{
  // MOTOR 1 FORWARD
  mLink.L9110_M1_Dir(I2C_ADD, FORWARD);
  mLink.L9110_M1_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M1_Speed(I2C_ADD, 255); delay(2000);  // Full speed
  mLink.L9110_M1_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M1_Speed(I2C_ADD, 0);   delay(2000);  // Stop

  // MOTOR 1 REVERSE
  mLink.L9110_M1_Dir(I2C_ADD, REVERSE);
  mLink.L9110_M1_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M1_Speed(I2C_ADD, 255); delay(2000);  // Full speed
  mLink.L9110_M1_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M1_Speed(I2C_ADD, 0);   delay(2000);  // Stop

  // MOTOR 2 FORWARD
  mLink.L9110_M2_Dir(I2C_ADD, FORWARD);
  mLink.L9110_M2_Speed(I2C_ADD, 127); delay(2000);  // Half speed
  mLink.L9110_M2_Speed(I2C_ADD, 255); delay(2000);  // Full speed
  mLink.L9110_M2_Speed(I2C_ADD, 127); delay(2000);  // Half speed
  mLink.L9110_M2_Speed(I2C_ADD, 0);   delay(2000);  // Stop

  // MOTOR 2 REVERSE
  mLink.L9110_M2_Dir(I2C_ADD, REVERSE);
  mLink.L9110_M2_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M2_Speed(I2C_ADD, 255); delay(2000);  // Full speed
  mLink.L9110_M2_Speed(I2C_ADD, 128); delay(2000);  // Half speed
  mLink.L9110_M2_Speed(I2C_ADD, 0);   delay(2000);  // Stop
}
