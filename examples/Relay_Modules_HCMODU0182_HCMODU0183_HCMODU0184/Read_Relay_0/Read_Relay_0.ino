/* FILE:    Read_Relay_0.ino
   DATE:    04/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the current state of relay 0 and output
the result to the serial monitor. To use this sketch simply open the serial monitor
window (Tools->Serial Monitor) and then toggle the state of relay 0 via the modules
RL0 pin.

This sketch can be used with one of the following modules:

mLink 1 Channel relay module (SKU: HCMODU0182)
mLink 2 Channel relay module (SKU: HCMODU0183)
mLink 4 Channel relay module (SKU: HCMODU0184)

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library


#define I2C_ADD 0x52                    // Default I2C address

boolean lastState;

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                         // Initialise the library

  lastState = mLink.READ_RLY0(add);     // Get the current state of relay 0
}


void loop() 
{
  if(mLink.READ_RLY0(add) != lastState) // Check if relay state has changed
  {
    lastState = mLink.READ_RLY0(add);   // If so store new state...
    
    Serial.print("Relay 0 = ");         // and output the new state to the serial monitor

    if(lastState == 1)
      Serial.println("ON");
    else
      Serial.println("OFF");
  }  
}
