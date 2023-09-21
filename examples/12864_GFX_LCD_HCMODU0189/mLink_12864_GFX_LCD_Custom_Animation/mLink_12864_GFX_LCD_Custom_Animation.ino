/* FILE:    mLink_12864_GFX_LCD_Custom_Animation.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how use a custom character to create an 
animated icon

Supported mLink products:

mLink 128x64 Graphics LCD (SKU: HCMODU0189)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x57                    // Default I2C address


// Battery icon bitmaps for each charge state
byte Battery[6][5] = {{0x7F, 0xC1, 0xC1, 0xC1, 0x7F},  // 0%
                      {0x7F, 0xC3, 0xC3, 0xC3, 0x7F},  // 20%
                      {0x7F, 0xC7, 0xC7, 0xC7, 0x7F},  // 40%
                      {0x7F, 0xCF, 0xCF, 0xCF, 0x7F},  // 60%
                      {0x7F, 0xDF, 0xDF, 0xDF, 0x7F},  // 80%
                      {0x7F, 0xFF, 0xFF, 0xFF, 0x7F}}; // 100%


void setup() 
{
  mLink.init();                             // Initialise the library

  mLink.gLCD_clear(I2C_ADD);                // Clear the screen

  mLink.gLCD_cursor(I2C_ADD, 30, 28);
  mLink.gLCD_print(I2C_ADD, "Charging: ");  // Print some text
  
  mLink.gLCD_setCustCode0(I2C_ADD, 0x80);   // Set the ASCII code for the custom character
}


void loop() 
{
  // Loop through each icon bitmap and write it to custom character 0
  // then reprint it.
  for(byte i = 0; i < 6; i++)
  {
    mLink.gLCD_setCustBitmap0(I2C_ADD, Battery[i]);
    mLink.gLCD_cursor(I2C_ADD, 90, 28);
    mLink.gLCD_print(I2C_ADD, (char)0x80);
  
    delay(500);
  }
  
  mLink.gLCD_erase(I2C_ADD, 90, 28, 94, 35);   // Erase the icon and start again.
}
