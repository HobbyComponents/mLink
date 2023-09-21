/* FILE:    mLink_12864_GFX_LCD_Hello_World.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to print some text at a particular location on the
mLink GLCD module.

Supported mLink products:

mLink 128x64 Graphics LCD (SKU: HCMODU0189)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x57                    // Default I2C address


void setup() 
{
  mLink.init();                         // Initialise the library

  mLink.gLCD_clear(I2C_ADD);            // Clear the display
}


void loop() 
{
  mLink.gLCD_cursor(I2C_ADD, 49, 20);   // Set the cursor to col 48 row 20
  mLink.gLCD_print(I2C_ADD, "Hello");   // Print something

  
  mLink.gLCD_cursor(I2C_ADD, 46, 36);   // Set the cursor to col 46 row 36
  mLink.gLCD_print(I2C_ADD, "World!");  // Print something

  while(1);
}
