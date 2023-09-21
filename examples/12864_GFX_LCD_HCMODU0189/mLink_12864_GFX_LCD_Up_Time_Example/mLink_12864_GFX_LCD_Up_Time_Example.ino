/* FILE:    mLink_12864_GFX_LCD_Up_Time_Example.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how use print a floating point number by
using the Arduinos millis timer as an example.

Supported mLink products:

mLink 128x64 Graphics LCD (SKU: HCMODU0189)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                      // Include the library

mLink mLink;                                            // Create an instance of the library

#define I2C_ADD 0x57                                    // Default I2C address

float time;

void setup() 
{
  mLink.init();                                         // Initialise the library

  mLink.gLCD_clear(I2C_ADD);                            // Clear the screen

  mLink.gLCD_drawMode(I2C_ADD, GLCD_DRAW_MODE_INVERT);  // Set the draw mode to XOR

  mLink.gLCD_cursor(I2C_ADD, 25, 28);                   // Set the cursor to col 25 row 28 
  mLink.gLCD_print(I2C_ADD, "Uptime: ");                // Print some text
}


void loop() 
{
  time = (float)millis() / 1000;                        // Get the Arduinos 'up time' and convert it to seconds

  mLink.gLCD_cursor(I2C_ADD, 70, 28);                   // Set the cursor to col 70 row 28
  mLink.gLCD_printFloat(I2C_ADD, time, 1);              // Print the uptime to 1 decimal place
 
  delay(100);

  mLink.gLCD_cursor(I2C_ADD, 70, 28);                   // Erase the last up time printed by writing the 
  mLink.gLCD_printFloat(I2C_ADD, time, 1);              // time again in invert mode
}
