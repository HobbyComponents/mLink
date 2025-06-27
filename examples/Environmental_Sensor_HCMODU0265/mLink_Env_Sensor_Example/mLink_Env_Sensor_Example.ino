/* FILE:    mLink_Env_Sensor_Example.ino
   DATE:    23/06/25
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to repeatedly read the
sensors of the mLink environmental sensor module and output
the result to the serial monitor.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x61                        // Default I2C address


void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library
}


void loop() 
{
  mLink.wake(I2C_ADD);                      // Wake device

  mLink.envSens_Trigger(I2C_ADD);           // Trigger a measurement

  while(mLink.busy(I2C_ADD));               // Wait until done

  float tmp = mLink.envSens_Temp(I2C_ADD);  // Get new temperature (oC)
  float hum = mLink.envSens_Hum(I2C_ADD);   // Get new humidity (%RH)
  float prs = mLink.envSens_Pres(I2C_ADD);  // Get new pressure (mbar/hPa)
  float amb = mLink.envSens_Amb(I2C_ADD);   // Get new ambient light (lux)
  float wht = mLink.envSens_Wht(I2C_ADD);   // Get new white light (lux)

  mLink.sleep(I2C_ADD);                     // Go back to sleep

  // Print the results
  Serial.print("Temp:\t"); Serial.println(tmp);
  Serial.print("Hum:\t"); Serial.println(hum);
  Serial.print("Pres:\t"); Serial.println(prs);
  Serial.print("Amb:\t"); Serial.println(amb);
  Serial.print("White:\t"); Serial.println(wht);
  Serial.println("");
  
  delay(2000);
}
