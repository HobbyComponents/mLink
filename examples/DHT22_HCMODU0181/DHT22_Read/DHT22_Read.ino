/* FILE:    DHT22_Read.ino
   DATE:    24/09/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the temperature (in oC) an humidity 
(in RH%) from the mLink DHT22 sensor module (SKU: HCMODU0181).

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"          // Include the library

mLink mLink;                // Create an instance of the library

#define I2C_ADD 0x51        // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();             // Initialise the library
}


void loop() 
{
  mLink.write(I2C_ADD, DHT22_START_MEAS);  // Trigger a new measurement
  
  while(mLink.busy(I2C_ADD));                 // Wait for the new measurement

  float temp = mLink.DHT22_Temp(I2C_ADD);     // Get the temperature in oC
  float hum =  mLink.DHT22_Hum(I2C_ADD);      // Get the humidity in %RH
  
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity:    "); Serial.println(hum);
  
  delay(1000);
}