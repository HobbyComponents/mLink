/* FILE:    Blink_Relay_0.ino
   DATE:    04/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to control the state of relay 0 on one of the 
mLink relay modules. This sketch can be used with one of the following modules:

mLink 1 Channel relay module (SKU: HCMODU0182)
mLink 2 Channel relay module (SKU: HCMODU0183)
mLink 4 Channel relay module (SKU: HCMODU0184)

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"          // Include the library

mLink mLink;                // Create an instance of the library


#define I2C_ADD 0x52        // Default I2C address


void setup() 
{
  mLink.init();             // Initialise the library
}


void loop() 
{
  // Turn ON relay 0. Use SET_RLY1 for relay 1, SET_RLY2 for relay 2 etc
  mLink.SET_RLY0(I2C_ADD, HIGH);
  delay(10000);

  // Turn OFF relay 0
  mLink.SET_RLY0(I2C_ADD, LOW);
  delay(10000);
}
