/* FILE:    Alternative_Blink_Relay_0.ino
   DATE:    27/03/25
   VERSION: 1.0

   This sketch demonstrates an alternative way to control 
   the relays using the mLink library. It utilizes the RLY_ON() 
   and RLY_OFF() macros to turn a relay on or off by specifying 
   its index.

   Note: These commands are only compatible with module firmware 
   version 1.01 or higher.
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
  mLink.RLY_ON(I2C_ADD, 0); // Turn relay 0 on
  delay(10000);
  
  mLink.RLY_OFF(I2C_ADD, 0); // Turn relay 0 off
  delay(10000);
}
