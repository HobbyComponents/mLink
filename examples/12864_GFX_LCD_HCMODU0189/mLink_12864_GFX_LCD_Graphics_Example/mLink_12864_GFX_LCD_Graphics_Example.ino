/* FILE:    mLink_12864_GFX_LCD_Graphics_Example.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how draw graphics and different sized 
text to the display.

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
}


void loop() 
{
  // Draw some random lines in normal draw mode
  mLink.gLCD_clear(I2C_ADD);
  mLink.gLCD_drawMode(I2C_ADD, GLCD_DRAW_MODE_NORMAL);
  
  for(byte i = 0; i < 254; i++)
  {
    int x1 = random(0, 128);
    int y1 = random(0, 64);
    int x2 = random(0, 128);
    int y2 = random(0, 64);

    mLink.gLCD_line(I2C_ADD, x1, y1, x2, y2);
  }


  // Draw some random rectangles with invert mode turned on
  mLink.gLCD_clear(I2C_ADD);        
  mLink.gLCD_drawMode(I2C_ADD, GLCD_DRAW_MODE_INVERT);
  
  for(byte i = 0; i < 254; i++)
  {
    int x1 = random(0, 128);
    int y1 = random(0, 64);
    int x2 = random(0, 128);
    int y2 = random(0, 64);

    mLink.gLCD_rect(I2C_ADD, x1, y1, x2, y2);
  }


  // Draw random sized text with text background mode on
  mLink.gLCD_clear(I2C_ADD);            // Clear the display
  mLink.gLCD_drawMode(I2C_ADD, GLCD_DRAW_MODE_NORMAL);
  mLink.gLCD_bgMode(I2C_ADD, GLCD_BG_ON);

  for(byte i = 0; i < 254; i++)
  {
    int x = random(-50, 128);
    int y = random(-10, 64);

    byte dx = random(1, 5);
    byte dy = random(1, 5);

    mLink.gLCD_scaleXY(I2C_ADD, dx, dy);
    mLink.gLCD_cursor(I2C_ADD, x, y);
    mLink.gLCD_print(I2C_ADD, "Hello!");
  }
}
