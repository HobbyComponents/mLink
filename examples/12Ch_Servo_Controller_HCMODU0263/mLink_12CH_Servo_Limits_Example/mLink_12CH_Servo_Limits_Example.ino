/* FILE:    mLink_12CH_Servo_Limits_Example.ino
   DATE:    18/12/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

 This sketch shows how to adjust the default upper and lower limits of a servo.
 If your servo supports a wider range than the default (100 to 200), you can 
 increase the limits using this example.

 To retain the servo limits after power is removed, use the 
 mLink.servo_Save_State() command to save the current settings. Alternatively, use
 mLink.servo_Save_Defaults() to restore the default settings.

 WARNING: Driving a servo beyond its maximum range can cause permanent damage.
 Use this sketch carefully!

 Please see Licence.txt in the library folder for terms of use.
*/

#define LOWER_LIMIT 80
#define UPPER_LIMIT 220

#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x60                                  // Default I2C address


void setup() 
{
  mLink.init();                                       // Initialise the library

  mLink.servo0_LimLow(I2C_ADD, LOWER_LIMIT);          // Set lower limit for servo 0
  mLink.servo0_LimHigh(I2C_ADD, UPPER_LIMIT);         // Set upper limit for servo 0 

  //mLink.servo_Save_State(I2C_ADD);                  // Uncomment to save the new limits to NVM

  mLink.servo0_On(I2C_ADD);                           // Enable output for the first servo
}


void loop() 
{
  for(uint8_t i = LOWER_LIMIT; i <= UPPER_LIMIT; i++) // Step forward though the new range
  {
    mLink.servo0_Pos(I2C_ADD, i);   
    delay(10);
  }

  for(uint8_t i = UPPER_LIMIT; i >= LOWER_LIMIT; i--) // Step backward though the new range
  {
    mLink.servo0_Pos(I2C_ADD, i);   
    delay(10);
  }
}