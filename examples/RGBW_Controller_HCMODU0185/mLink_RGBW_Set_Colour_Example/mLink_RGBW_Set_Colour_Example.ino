/* FILE:    mLink_RGBW_Set_Colour_Example.ino
   DATE:    08/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies


This sketch demonstrates how to control the brightness of the individual red,
green, blue, and white LEDs on an RGB/RGBW LED strip. The sketch will step
through each colour in sequence. Supported mLink products:

mLink RGBW light controller (SKU: HCMODU0185)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                      // Include the library

mLink mLink;                                            // Create an instance of the library

#define I2C_ADD 0x53                                    // Default I2C address


void setup() 
{
  mLink.init();                                         // Initialise the library

  mLink.write(I2C_ADD, RGBW_BRIGHTNESS, 255);           // Set brightness to maximum
}


void loop() 
{
  mLink.write(I2C_ADD, RGBW_R_LEVEL, 255);              // Turn just the red LEDs on
  mLink.write(I2C_ADD, RGBW_G_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_B_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_W_LEVEL, 0);

  delay(1000);

  mLink.write(I2C_ADD, RGBW_R_LEVEL, 0);                // Turn just the green LEDs on
  mLink.write(I2C_ADD, RGBW_G_LEVEL, 255);
  mLink.write(I2C_ADD, RGBW_B_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_W_LEVEL, 0);

  delay(1000);

  mLink.write(I2C_ADD, RGBW_R_LEVEL, 0);                // Turn just the blue LEDs on
  mLink.write(I2C_ADD, RGBW_G_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_B_LEVEL, 255);
  mLink.write(I2C_ADD, RGBW_W_LEVEL, 0);

  delay(1000);

  mLink.write(I2C_ADD, RGBW_R_LEVEL, 0);                // Turn just the white LEDs on
  mLink.write(I2C_ADD, RGBW_G_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_B_LEVEL, 0);
  mLink.write(I2C_ADD, RGBW_W_LEVEL, 255);

  delay(1000);
}