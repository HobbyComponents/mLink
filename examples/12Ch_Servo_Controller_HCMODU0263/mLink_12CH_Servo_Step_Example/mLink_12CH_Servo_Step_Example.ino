/* FILE:    mLink_12CH_Servo_Step_Example.ino
   DATE:    18/12/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

 This sketch demonstrates how to control a servo's position. 
 It steps the first servo through its default range of 100 to 200.

 To extend the default range, refer to the range example sketch.

 Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x60                                  // Default I2C address


void setup() 
{
  mLink.init();                                       // Initialise the library

  mLink.servo0_On(I2C_ADD);                           // Enable output for the first servo
}


void loop() 
{
  for(uint8_t i = 100; i <= 200; i++)                 // Step forward though positions 100 to 200
  {
    mLink.servo0_Pos(I2C_ADD, i);   
    delay(10);
  }

  for(uint8_t i = 200; i >= 100; i--)                 // Step backward though positions 200 to 100
  {
    mLink.servo0_Pos(I2C_ADD, i);   
    delay(10);
  }
}
