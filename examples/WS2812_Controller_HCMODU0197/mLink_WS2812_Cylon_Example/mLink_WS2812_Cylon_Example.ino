/* FILE:    mLink_WS2812_Cylon_Example.ino
   DATE:    22/03/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to sweep a single red LED back
and forth.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                      // Include the library

mLink mLink;                                            // Create an instance of the library

#define I2C_ADD 0x5E                                    // Default I2C address

#define NUMBEROFLEDS 16                                 // Sets the number of LEDs in your strip

void setup() 
{
  mLink.init();                                         // Initialise the library

  mLink.WS2812_Max(I2C_ADD, NUMBEROFLEDS);              // Tell the module how many LEDs are connected to the module (max 200)
  
  //mLink.WS2812_Order(I2C_ADD, WS2812_ORDER_GRB);       // Uncomment if your LED order is GRB
}

void loop() 
{
  // Sweep the LEDs forward
  for(int i = 0; i < NUMBEROFLEDS; i++)
  {
    mLink.WS2812_Clear(I2C_ADD);                        // Set all LED RGB levels to 0
    mLink.WS2812_Index(I2C_ADD, i);                     // Set the LED index to write to
    mLink.WS2812_Red(I2C_ADD, 0xFF);                    // Set the LED at the above index to red
    mLink.WS2812_Refresh(I2C_ADD);                      // Update the LEDs
    delay(50);
  }

  // Sweep the LEDs in reverse
  for(int i = NUMBEROFLEDS; i ; i--)
  {
    mLink.WS2812_Clear(I2C_ADD);
    mLink.WS2812_Index(I2C_ADD, i);
    mLink.WS2812_Red(I2C_ADD, 0xFF);
    mLink.WS2812_Refresh(I2C_ADD);
    delay(50);
  }
}
