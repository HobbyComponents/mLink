/* FILE:    TMP36_Read.ino
   DATE:    01/12/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the temperature (in oC) 
from the mLink TMP36 Temperature sensor module (SKU: HCMODU0187).

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x58                        // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library
}


void loop() 
{
  float temp = mLink.TMP36_Temp(I2C_ADD);     // Get the temperature in oC
 
  Serial.print("Temperature: "); Serial.println(temp);
  
  delay(1000);                              // Wait a second before reading again
}
