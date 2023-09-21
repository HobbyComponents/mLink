/* FILE:    mLink_Char_LCD_Up_Time_Example.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how use print a floating point number by
using the Arduinos millis timer as an example.

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x56                        // Default I2C address

float time;

void setup() 
{
  mLink.init();                             // Initialise the library

  mLink.cLCD_clear(I2C_ADD);                // Clear the screen
  
  mLink.cLCD_print(I2C_ADD, "Uptime: ");    // Print some text
}


void loop() 
{
  time = (float)millis() / 1000;            // Get the Arduinos 'up time' and conver it to seconds

  mLink.cLCD_cursor(I2C_ADD, 10, 0);        // Set the cursor to col 10 row 0
  mLink.cLCD_printFloat(I2C_ADD, time, 3);  // Print the uptime to 3 decimal places
 
  delay(1);
}
