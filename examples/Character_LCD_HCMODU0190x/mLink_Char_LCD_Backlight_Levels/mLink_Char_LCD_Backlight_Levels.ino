/* FILE:    mLink_Char_LCD_Backlight_Levels.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch repeatedly steps through each backlight level where
0 = off and 10 = max

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x56                        // Default I2C address


void setup() 
{
  mLink.init();                             // Initialise the library
}


void loop() 
{
  for(byte i = 0; i <= 10; i++)                 // Loop through each BL level (0 to 10)
  {
    mLink.cLCD_backlight(I2C_ADD, i);               // Set the level
    
    mLink.cLCD_cursor(I2C_ADD, 0, 0);           // Print the backlight level
    mLink.cLCD_print(I2C_ADD, "Backlight: ");  
    mLink.cLCD_print(I2C_ADD, i);  

    delay(500);
  }

  mLink.cLCD_clear(I2C_ADD);
}