/* FILE:    NTC_Read_With_Sleep.ino
   DATE:    24/03/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the temperature (in oC) 
from the mLink NTC Temperature sensor module (SKU: HCMODU0186). Once the 
temperature has been read it will put the module into a low power sleep mode.
The module will then remain in sleep mode until the temperature is read from
from the module again.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x54                        // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library
}


void loop() 
{
  while(mLink.busy(I2C_ADD));               // Wait for the new measurement
  float temp = mLink.NTC_Temp(I2C_ADD);     // Get the temperature in oC
 
  mLink.sleep(I2C_ADD);                     // Put the module to sleep
  Serial.print("Temperature: "); Serial.println(temp);
  
  delay(1000);                              // Wait a second before reading again
}
