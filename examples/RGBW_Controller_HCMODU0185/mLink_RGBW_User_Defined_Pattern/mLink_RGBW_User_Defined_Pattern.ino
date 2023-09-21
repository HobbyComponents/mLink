/* FILE:    mLink_RGBW_User_Defined_Pattern.ino
   DATE:    08/10/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies

This sketch demonstrates how to load a user defined pattern into the modules
pattern buffer. The sketch will load 3 colours (red, green, & blue) into the
buffer and then tells the module to make 255 between each
transition with each step taking 10ms.

Supported mLink products:

mLink RGBW light controller (SKU: HCMODU0185)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                      // Include the library

mLink mLink;                                            // Create an instance of the library

#define I2C_ADD 0x53                                    // Default I2C address


// Create an array with 3 colours (maximum is 8) to load into the pattern buffer
byte colours[][3] = {{255,0,0}, // Red
                     {0,255,0}, // Green
                     {0,0,255}  // Blue
                     };


void setup() 
{
  mLink.init();                                         // Initialise the library


  mLink.write(I2C_ADD, RGBW_CYCLE(colours));            // Load the colours into the buffer

  mLink.write(I2C_ADD, RGBW_BRIGHTNESS, 255);           // Set brightness to maximum
  mLink.write(I2C_ADD, RGBW_CYCLE_COLOURS, 3);          // There are 3 colors to cycle though
  mLink.write(I2C_ADD, RGBW_CYCLE_STEPS, 255);          // Make 255 steps between each colour
  mLink.writeInt(I2C_ADD, RGBW_CYCLE_STEP_SPEED, 10);   // Wait 10ms between each step


  // Uncomment the following to save the above pattern into the module non-volatile memory
  //mLink.write(I2C_ADD, RGBW_SAVE);
}


void loop() 
{
}
