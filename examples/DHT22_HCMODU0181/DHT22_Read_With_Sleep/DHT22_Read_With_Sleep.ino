/* FILE:    DHT22_Read_With_Sleep.ino
   DATE:    10/09/24
   VERSION: 1.1.1
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the temperature (in oC) an humidity 
(in RH%) from the mLink DHT22 sensor module (SKU: HCMODU0181). Once the sensor 
has been read the sketch will then put the module back into a low power sleep mode.

Version 1.1: Added wake() function in main loop to support improved sleep mode in
V1.0 firmware. 

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
  mLink.wake(I2C_ADD);						  // Wake the device up
	 
  mLink.DHT22_Start(I2C_ADD);                 // Trigger a new measurement

  while(mLink.busy(I2C_ADD));                 // Wait for the new measurement

  float temp = mLink.DHT22_Temp(I2C_ADD);     // Get the temperature in oC
  float hum =  mLink.DHT22_Hum(I2C_ADD);      // Get the humidity in %RH
  
  mLink.sleep(I2C_ADD);                       // Put the module to sleep
  
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity:    "); Serial.println(hum);

  delay(10000);                               // Wait 10 seconds before reading again
}