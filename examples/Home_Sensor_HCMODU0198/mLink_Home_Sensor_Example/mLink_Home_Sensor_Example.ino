/* FILE:    mLink_Home_Sensor_Example.ino
   DATE:    07/01/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies

This sketch demonstrates how to read the module sensors.
Note, to read the current temperature and humidity a new measurement
must first be triggered. Once triggered the modules busy state can
be checked to see when the measurement is complete (busy = false).

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
  mLink.HSense_Start_Meas(I2C_ADD);             // Trigger a new temp/hum measurement
  while(mLink.busy(I2C_ADD));                   // Wait for the measurement to complete

  // Read the sensors
  float temp = mLink.HSens_Temp(I2C_ADD);
  float hum = mLink.HSens_Hum(I2C_ADD);
  byte LDR = mLink.HSens_LDR(I2C_ADD);
  boolean PIR = mLink.HSens_PIR(I2C_ADD);

  // Print out the results
  Serial.print("Temperature: "); Serial.println(temp, 1);
  Serial.print("Humidity: "); Serial.println(hum, 1);
  Serial.print("Light: "); Serial.println(LDR);
  Serial.print("PIR: ");
  PIR ? Serial.println("Triggered!") : Serial.println("Idle");

  Serial.println();
 
  delay(1000);
}
