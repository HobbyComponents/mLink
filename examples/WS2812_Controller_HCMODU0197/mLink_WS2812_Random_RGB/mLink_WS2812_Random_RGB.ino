/* FILE:    mLink_WS2812_Random_RGB.ino
   DATE:    22/03/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to set the LEDs to random
colours. The sketch will continuously loop, each time picking
a random LED and setting it to a random colour.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                       // Include the library

mLink mLink;                                             // Create an instance of the library

#define I2C_ADD 0x5E                                     // Default I2C address

#define NUMBEROFLEDS 16                                  // Sets the number of LEDs in your strip


void setup() 
{
  mLink.init();                                          // Initialise the library
  
  mLink.WS2812_Max(I2C_ADD, NUMBEROFLEDS);               // Tell the module how many LEDs are connected to the module (max 200)
  mLink.WS2812_Brightness(I2C_ADD, 100);                 // Set the maximum brightness (max = 255);
  //mLink.WS2812_Order(I2C_ADD, WS2812_ORDER_GRB);       // Uncomment if your LED order is GRB
}


void loop() 
{
  byte red, green, blue, ledIndex;

  red = random(0, 255);                                   // Set red to a random level
  green = random(0, 255);                                 // Set green to a random level
  blue = random(0, 255);                                  // Set blue to a random level
  ledIndex = random(0, NUMBEROFLEDS);                     // Pick a random LED

  mLink.WS2812_RGB(I2C_ADD, ledIndex, red, green, blue);  // Set the LED at ledIndex to the above levels
  
  mLink.WS2812_Refresh(I2C_ADD);
  delay(50);
}
