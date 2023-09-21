/* FILE:    mLink_RGBW_Predefined_Cycle_Modes.ino
   DATE:    08/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies


This sketch demonstrates how to put the module into one of the pre-defined 
patterns. The sketch will constantly step through each pattern allowing the 
pattern to run for 20 seconds before moving onto the next.

Supported mLink products:

mLink RGBW light controller (SKU: HCMODU0185)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                      // Include the library

mLink mLink;                                            // Create an instance of the library

#define I2C_ADD 0x53                                    // Default I2C address


void setup() 
{
  mLink.init();                                         // Initialise the library

  Serial.begin(9600);

  mLink.write(I2C_ADD, RGBW_BRIGHTNESS, 255);           // Set brightness to maximum
}


void loop() 
{
  Serial.println("FAST RED-GREEN-BLUE CYCLE");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_FAST_RGB_COLOUR_CYCLE);
  delay(20000);

  Serial.println("MEDIUM RED-GREEN-BLUE CYCLE");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_MED_RGB_COLOUR_CYCLE);
  delay(20000);

  Serial.println("SLOW RED-GREEN-BLUE CYCLE");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_SLOW_RGB_COLOUR_CYCLE);
  delay(20000);

  Serial.println("FAST RED-GREEN CYCLE");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_FAST_RG_CYCLE);
  delay(20000);

  Serial.println("INTERMEDIATE RED PULSE ALARM");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_ALARM_INTER_PULSE);
  delay(20000);

  Serial.println("CONSTANT RED PULSE ALARM");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_ALARM_CONT_PULSE);
  delay(20000);

  Serial.println("CONSTANT RED-GREEN-BLUE PULE");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_RGB_CONT_PULSE);
  delay(20000);

  Serial.println("FLAME EFFECT");
  mLink.write(I2C_ADD, RGBW_LOAD_CYCLE, RGBW_CYCLE_FLAME);
  delay(20000);
}
