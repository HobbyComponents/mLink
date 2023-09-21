/* FILE:    mLink_12864_GFX_LCD_Custom_Characters.ino
   DATE:    07/06/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to set and use the 8 custom characters of
the LCD.

Supported mLink products:

mLink 128x64 Graphics LCD (SKU: HCMODU0189)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                      // Include the library

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x57                    // Default I2C address


// Bitmaps for each custom character
byte Battery[] =        {0x7F, 0xC1, 0xC1, 0xC1, 0x7F, 0x00};
byte LeftArrow[] =      {0x10, 0x38, 0x7C, 0xFE, 0x10, 0x10, 0x10, 0x10, 0x00};
byte UpArrow[] =        {0x08, 0x0C, 0x0E, 0xFF, 0x0E, 0x0C, 0x08, 0x00};
byte DownArrow[] =      {0x10, 0x30, 0x70, 0xFF, 0x70, 0x30, 0x10, 0x00};
byte RightArrow[] =     {0x10, 0x10, 0x10, 0x10, 0xFE, 0x7C, 0x38, 0x10, 0x00};
byte PadLockLocked[] =  {0x7F, 0x9F,  0x91, 0x9F, 0x7F, 0x00};
byte PadLockOpen[] =    {0x1F, 0x9F, 0x91, 0x9F, 0x7F, 0x00};
byte Ohmega[] =         {0x7A, 0x86, 0x80, 0x86, 0x7A, 0x00};
byte Centigrade[] =     {0x40, 0xA0, 0x40, 0x00, 0x3C, 0x42, 0x42, 0x24, 0x00};
byte Pi[] =             {0x42, 0x7C, 0x40, 0x40, 0x78, 0x46, 0x00};
byte Mu[] =             {0x7F, 0x08, 0x08, 0x70, 0x08, 0x00};
byte Sqrt[] =           {0x08, 0x0C, 0x02, 0xFE, 0x80, 0x80, 0x00};
byte Copyright[] =      {0x3C, 0x42, 0x99, 0xA5, 0xA5, 0x42, 0x3C, 0x00};
byte Scissors[] =       {0xC6, 0xAA, 0x6C, 0x10, 0x28, 0x6C, 0xC6, 0x82, 0x00};
byte Tick[] =           {0x08, 0x0C, 0x06, 0x0E, 0x38, 0x60, 0xC0, 0x80, 0x00};
byte Euro[] =           {0x28, 0x7C, 0xAA, 0xAA, 0x82, 0x44, 0x00};


void setup() 
{
  mLink.init();                         // Initialise the library

  mLink.gLCD_clear(I2C_ADD);             // Clear the screen
}


void loop() 
{
  // Write the bitmaps to the LCDs 16 custom characters
  mLink.gLCD_setCustBitmap0(I2C_ADD, Battery);
  mLink.gLCD_setCustBitmap1(I2C_ADD, LeftArrow);
  mLink.gLCD_setCustBitmap2(I2C_ADD, UpArrow);
  mLink.gLCD_setCustBitmap3(I2C_ADD, DownArrow);
  mLink.gLCD_setCustBitmap4(I2C_ADD, RightArrow);
  mLink.gLCD_setCustBitmap5(I2C_ADD, PadLockLocked);
  mLink.gLCD_setCustBitmap6(I2C_ADD, PadLockOpen);
  mLink.gLCD_setCustBitmap7(I2C_ADD, Ohmega);
  mLink.gLCD_setCustBitmap8(I2C_ADD, Centigrade);
  mLink.gLCD_setCustBitmap9(I2C_ADD, Pi);
  mLink.gLCD_setCustBitmap10(I2C_ADD, Mu);
  mLink.gLCD_setCustBitmap11(I2C_ADD, Sqrt);
  mLink.gLCD_setCustBitmap12(I2C_ADD, Copyright);
  mLink.gLCD_setCustBitmap13(I2C_ADD, Scissors);
  mLink.gLCD_setCustBitmap14(I2C_ADD, Tick);
  mLink.gLCD_setCustBitmap15(I2C_ADD, Euro);

  // Assign ASCCI codes to each custom character
  mLink.gLCD_setCustCode0(I2C_ADD, 'A');
  mLink.gLCD_setCustCode1(I2C_ADD, 'B');
  mLink.gLCD_setCustCode2(I2C_ADD, 'C');
  mLink.gLCD_setCustCode3(I2C_ADD, 'D');
  mLink.gLCD_setCustCode4(I2C_ADD, 'E');
  mLink.gLCD_setCustCode5(I2C_ADD, 'F');
  mLink.gLCD_setCustCode6(I2C_ADD, 'G');
  mLink.gLCD_setCustCode7(I2C_ADD, 'H');
  mLink.gLCD_setCustCode8(I2C_ADD, 'I');
  mLink.gLCD_setCustCode9(I2C_ADD, 'J');
  mLink.gLCD_setCustCode10(I2C_ADD, 'K');
  mLink.gLCD_setCustCode11(I2C_ADD, 'L');
  mLink.gLCD_setCustCode12(I2C_ADD, 'M');
  mLink.gLCD_setCustCode13(I2C_ADD, 'N');
  mLink.gLCD_setCustCode14(I2C_ADD, 'O');
  mLink.gLCD_setCustCode15(I2C_ADD, 'P');

  // Print the custom characters to the display
  mLink.gLCD_print(I2C_ADD, "ABCDEFGHIJKLMNOP");

  while(1);
}
