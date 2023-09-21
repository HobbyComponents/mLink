/* FILE:    mLink_12864_GFX_LCD_Backlight_Levels.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch repeatedly steps through each backlight level where
0 = off and 10 = max

Supported mLink products:

mLink 128x64 Graphics LCD (SKU: HCMODU0189)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                            // Include the library

mLink mLink;                                  // Create an instance of the library

#define I2C_ADD 0x57                          // Default I2C address


void setup() 
{
  mLink.init();                               // Initialise the library

  mLink.gLCD_clear(I2C_ADD);                  // Clear the display

  mLink.gLCD_cursor(I2C_ADD, 30, 28);  
  mLink.gLCD_print(I2C_ADD, "Backlight: "); 
}


void loop() 
{
  for(byte i = 0; i <= 10; i++)               // Loop through each BL level (0 to 10)
  {
    mLink.gLCD_backlight(I2C_ADD, i);         // Set the level
    
    mLink.gLCD_cursor(I2C_ADD, 90, 28);       // Print the backlight level
    mLink.gLCD_print(I2C_ADD, i);  

    delay(1000);                              // Wait for a second before moving to the next level

    mLink.gLCD_erase(I2C_ADD, 90,28,106,36);
  }
}
