/* FILE:    Set_Relay_On_Time.ino
   DATE:    04/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to set the relays on time. Setting the on time
of a relay will cause the relay to stay energised for the specified amount of time.
Relay on times are stored in the modules non-volatile memory and so will be retained 
even after power is removed from the module.

To set the required time for each relay change the following lines on the sketch from 
the default 0 to the required time in seconds:

#define RELAY_0_ON_TIME    0
#define RELAY_1_ON_TIME    0
#define RELAY_2_ON_TIME    0
#define RELAY_3_ON_TIME    0

Setting an on time to 0 seconds will disable the on timer for that relay causing it to 
revert back to normal operating mode.

This sketch can be used with one of the following modules:

mLink 1 Channel relay module (SKU: HCMODU0182)
mLink 2 Channel relay module (SKU: HCMODU0183)
mLink 4 Channel relay module (SKU: HCMODU0184)


Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"          // Include the library

mLink mLink;                // Create an instance of the library

#define I2C_ADD 0x52        // Default I2C address


// Set the on times in seconds here:
#define RELAY_0_ON_TIME    0
#define RELAY_1_ON_TIME    0
#define RELAY_2_ON_TIME    0
#define RELAY_3_ON_TIME    0


void setup() 
{
  Serial.begin(9600);
  
  mLink.init();             // Initialise the library

  // Write the on times to the module
  mLink.RLY0_SetOnTime(I2C_ADD, RELAY_0_ON_TIME);
  mLink.RLY1_SetOnTime(I2C_ADD, RELAY_1_ON_TIME);
  mLink.RLY2_SetOnTime(I2C_ADD, RELAY_2_ON_TIME);
  mLink.RLY3_SetOnTime(I2C_ADD, RELAY_3_ON_TIME);

  Serial.print("Relay 0 ON time set to ");
  Serial.print(RELAY_0_ON_TIME);
  Serial.println(" seconds");

  Serial.print("Relay 1 ON time set to ");
  Serial.print(RELAY_1_ON_TIME);
  Serial.println(" seconds");

  Serial.print("Relay 2 ON time set to ");
  Serial.print(RELAY_2_ON_TIME);
  Serial.println(" seconds");

  Serial.print("Relay 3 ON time set to ");
  Serial.print(RELAY_3_ON_TIME);
  Serial.println(" seconds");
}


void loop() 
{
  // Nothing to do !
}
