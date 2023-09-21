/* FILE:    12_Pin_Port_Expander_Read_Pin.ino
   DATE:    24/09/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink to read the state of pin D1 on an mLink 12 pin digital
port expander module (SKU: HCMODU0180).

To use this sketch connect a push button to pin D1 and GND. The sketch will output
the pin state to the monitor window.

Please see Licence.txt in the library folder for terms of use.
*/



#include "mLink.h"      // Include the library

mLink mLink;            // Create an instance of the library

#define I2C_ADD 0x50    // Default I2C address

void setup() 
{
  Serial.begin(9600);
  mLink.init();

  // Set pin D1 to an input
  mLink.writeBit(I2C_ADD, DIO12_D1_INPUT);
}


void loop() 
{
  boolean result = mLink.readBit(I2C_ADD, DIO12_D1);  // Read pin D1

  Serial.println(result);     // Output the pin state to the serial monitor
  delay(500);                 // Wait a little
}