/* FILE:    mLink_Char_LCD_Custom_Animation.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how use a custom character to create an 
animated icon

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x56                    // Default I2C address


// Battery icon bitmaps for each charge state
byte Battery[6][8] = {{0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},  // 0%
                      {0x0E,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},  // 20%
                      {0x0E,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},  // 40%
                      {0x0E,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},  // 60%
                      {0x0E,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},  // 80%
                      {0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}}; // 100%


void setup() 
{
  mLink.init();                             // Initialise the library

  mLink.cLCD_clear(I2C_ADD)                 // Clear the screen

  mLink.cLCD_print(I2C_ADD, "Charging: ");  //Print some text

  // Write the 0% charge icon to custom character 0 and print it to the screen
  mLink.cLCD_setCust0(I2C_ADD, Battery[0]);
  mLink.cLCD_cursor(I2C_ADD, 10, 0);
  mLink.cLCD_printCust(I2C_ADD, 0);
}


void loop() 
{
  // Loop through each icon bitmap and write it to custom character 0.
  // Custom character 0 is already printed to the screen and will automatically 
  // update so no need to reprint it.
  for(byte i = 0; i < 6; i++)
  {
    mLink.cLCD_setCust0(I2C_ADD, Battery[i]);
  
    delay(500);
  }
}
