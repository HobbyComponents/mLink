/* FILE:    mLink_Char_LCD_Custom_Characters.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to set and use the 8 custom characters of
the LCD.

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x56                    // Default I2C address


// Bitmaps for each custom character
byte Battery[] =        {0x0E, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};
byte LeftArrow[] =      {0x00, 0x04, 0x0C, 0x1F, 0x0C, 0x04, 0x00, 0x00};
byte UpArrow[] =        {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04};
byte DownArrow[] =      {0x04, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04};
byte RightArrow[] =     {0x00, 0x04, 0x06, 0x1F, 0x06, 0x04, 0x00, 0x00};
byte PadLockLocked[] =  {0x0E, 0x11, 0x11, 0x1F, 0x1B, 0x1B, 0x1F, 0x00};
byte PadLockOpen[] =    {0x0E, 0x10, 0x10, 0x1F, 0x1B, 0x1B, 0x1F, 0x00};
byte Ohmega[] =         {0x00, 0x0E, 0x11, 0x11, 0x11, 0x0A, 0x1B, 0x00};


void setup() 
{
  mLink.init();                         // Initialise the library

  mLink.cLCD_clear(I2C_ADD)             // Clear the screen
}


void loop() 
{
  // Write the bitmaps to the LCDs 8 custom characters
  mLink.cLCD_setCust0(I2C_ADD, Battery);
  mLink.cLCD_setCust1(I2C_ADD, LeftArrow);
  mLink.cLCD_setCust2(I2C_ADD, UpArrow);
  mLink.cLCD_setCust3(I2C_ADD, DownArrow);
  mLink.cLCD_setCust4(I2C_ADD, RightArrow);
  mLink.cLCD_setCust5(I2C_ADD, PadLockLocked);
  mLink.cLCD_setCust6(I2C_ADD, PadLockOpen);
  mLink.cLCD_setCust7(I2C_ADD, Ohmega);

  // Print out each custom character
  mLink.cLCD_printCust(I2C_ADD, 0);
  mLink.cLCD_printCust(I2C_ADD, 1);
  mLink.cLCD_printCust(I2C_ADD, 2);
  mLink.cLCD_printCust(I2C_ADD, 3);
  mLink.cLCD_printCust(I2C_ADD, 4);
  mLink.cLCD_printCust(I2C_ADD, 5);
  mLink.cLCD_printCust(I2C_ADD, 6);
  mLink.cLCD_printCust(I2C_ADD, 7);

  while(1);
}
