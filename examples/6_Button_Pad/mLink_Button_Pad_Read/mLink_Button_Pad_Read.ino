/* FILE:    mLink_Button_Pad_Read.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to check the button pads
to see if a putton has been pressed and if so read it from
its buffer.

Supported mLink products:

mLink 6 Button Pad (SKU: HCMODU0193)

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD BPAD_I2C_ADD                          // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                                       // Initialise the library
}


void loop() 
{  
  byte empty = mLink.bPad_Empty(I2C_ADD);			  // Check to see if there is anything in the keypad buffer

  if(!empty)                                          
  { 
    byte key = mLink.read(I2C_ADD, BPAD_BUFFER);      // If so then read a key from the buffer and print it

    Serial.print("Key: ");                            
    Serial.println(key);
  }

  delay(100);
}