/* FILE:    mLink_Home_Sensor_PIR_Example.ino
   DATE:    07/01/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies

This sketch reads the current state of the PIR sensor and the PIR trigger 
counter. The trigger counter is useful for checking if the PIR has been 
triggered without having to constantly monitor the state of the PIR. It will 
record up to 1024 triggers and can be reset using the HSens_Clear_Trigs() 
library macro.

Supported mLink products:

mLink Home Sensor (SKU: HCMODU0198)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                              // Include the library

#define I2C_ADD 0x5B                            // Default I2C address

mLink mLink;                                    // Create an instance of the library


void setup()
{
  Serial.begin(9600);
  mLink.init();                                 // Initialise the library

  mLink.HSens_Clear_Trigs(I2C_ADD);             // Clear the PIR trigger counter
}


void loop()
{
 
  // Read the PIR status
  boolean PIR = mLink.HSens_PIR(I2C_ADD);
  unsigned int triggers = mLink.HSens_Trigs(I2C_ADD);

  Serial.print("PIR state = ");
  PIR ? Serial.println("TRIGGERED! ") : Serial.println("IDLE ");
  Serial.print("Triggers since last reset = "); Serial.println(triggers);
  Serial.println("");
  delay(1000);
}
