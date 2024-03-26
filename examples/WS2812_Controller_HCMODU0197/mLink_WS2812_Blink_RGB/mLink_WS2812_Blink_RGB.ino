/* FILE:    mLink_WS2812_Blink_RGB.ino
   DATE:    22/03/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to cycle a single LED through
the red, green, and blue colours.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x5E                                  // Default I2C address

#define NUMBEROFLEDS 16                               // Sets the number of LEDs in your strip


void setup() 
{
  mLink.init();                                       // Initialise the library
  
  mLink.WS2812_Max(I2C_ADD, NUMBEROFLEDS);            // Tell the module how many LEDs are connected to the module (max 200)
  
  //mLink.WS2812_Order(I2C_ADD, WS2812_ORDER_GRB);       // Uncomment if your LED order is GRB
}


void loop() 
{
  mLink.WS2812_RGB(I2C_ADD, 0, 255, 0, 0);            // Set LED at index 0 to red
  mLink.WS2812_Refresh(I2C_ADD);
  delay(1000);
  
  mLink.WS2812_RGB(I2C_ADD, 0, 0x00, 255, 0);         // Set LED at index 0 to green
  mLink.WS2812_Refresh(I2C_ADD);
  delay(1000);
  
  mLink.WS2812_RGB(I2C_ADD, 0, 0, 0, 255);            // Set LED at index 0 to blue
  mLink.WS2812_Refresh(I2C_ADD);
  delay(1000);
}
