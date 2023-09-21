/* FILE:    Matrix_4x4_Keypad_Read_Key.ino
   DATE:    31/03/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the status of a key on the mLink
4x4 matrix keypad (SKU: HCMODU0188). The result will be output to the serial
monitor window.

The keypad status is read using the mLink.read(I2C_ADD, KEYPAD_4X4_KEY)
function. This function will return 0 if no key is pressed or the ASCII value 
of the key if a key is pressed. Note that the function will return 0 on the 
next read even if the key is still pressed.
 
If you wish to know if the key is still pressed you can read the key state 
reg using the following function:

boolean keyState = mLink.Keypad_4x4_Key_Down(I2C_ADD);

This will return a 1 if a key is pressed or a 0 if no key is pressed

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x55                                  // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                                       // Initialise the library
}


void loop() 
{  
  char key = mLink.read(I2C_ADD, KEYPAD_4X4_KEY);     // Read the key status

  if(key)                                             // Has a key been pressed ?
  { 
    Serial.print("Key: ");                            // If so then output the key to the serial monitor
    Serial.println(key);
  };
}