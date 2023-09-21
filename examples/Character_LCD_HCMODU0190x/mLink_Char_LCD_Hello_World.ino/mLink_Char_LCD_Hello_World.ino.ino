/* FILE:    mLink_Char_LCD_Hello_World.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to print some text at a particular location on one
of the mLink character LCD modules.

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x56                    // Default I2C address


void setup() 
{
  mLink.init();                         // Initialise the library
}

void loop() 
{
  mLink.cLCD_cursor(I2C_ADD, 5, 0);     // Set the cursor to col 5 row 0
  mLink.cLCD_print(I2C_ADD, "Hello");   // Print something

  
  mLink.cLCD_cursor(I2C_ADD, 5, 1);     // Set the cursor to col 5 row 1
  mLink.cLCD_print(I2C_ADD, "World");   // Print something

  while(1);
}
