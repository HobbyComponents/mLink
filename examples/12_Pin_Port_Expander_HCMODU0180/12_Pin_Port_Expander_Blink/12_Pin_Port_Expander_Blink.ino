/* FILE:    12_Pin_Port_Expander_Blink.ino
   DATE:    24/09/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink to 'blink' digital pin 0 on an mLink 12 pin digital
port expander module (SKU: HCMODU0180).

To use this sketch connect an LED with a suitable current limiting resistor in
series to pin D0 and GND. The LED should then flash slowly.

Please see Licence.txt in the library folder for terms of use.
*/



#include "mLink.h"      // Include the library

mLink mLink;            //Create an instance of the library

#define I2C_ADD 0x50    //Default I2C address

void setup() 
{
  mLink.init();

  // Set pin D0 to an output
  mLink.writeBit(I2C_ADD, DIO12_D0_OUTPUT);
}


void loop() 
{
  mLink.writeBit(I2C_ADD, DIO12_D0, HIGH);    // Set pin D0 HIGH
  delay(1000);                                // Wait for a second
  mLink.writeBit(I2C_ADD, DIO12_D0, LOW);     // Set pin D0 LOW
  delay(1000);                                // Wait for a second
}