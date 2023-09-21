/* FILE:    mLink_Home_Sensor_Sleep_Example.ino
   DATE:    07/01/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   
This sketch demonstrates how to use the modules low power sleep mode.
The sketch will wake the module from sleep, trigger a temp/hum
measurement, and when complete read the result before finally putting 
the module back to sleep again.  

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
}


void loop()
{
  mLink.wake(I2C_ADD);                          // Wake the module
  mLink.HSense_Start_Meas(I2C_ADD);             // Trigger a new temp/hum measurement
  while(mLink.busy(I2C_ADD));                   // Wait for the measurement to complete

  // Read the sensors
  float temp = mLink.HSens_Temp(I2C_ADD);
  float hum = mLink.HSens_Hum(I2C_ADD);

  mLink.sleep(I2C_ADD);                          // Put the module back to sleep

  // Print out the results
  Serial.print("Temperature: "); Serial.println(temp, 1);
  Serial.print("Humidity: "); Serial.println(hum, 1);
  
  Serial.println();
 
  delay(1000);
}
