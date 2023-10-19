/* FILE:    mLink_IR_Trans_NEC_Rx.ino
   DATE:    16/10/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read the add and command
bytes from an NEC compatible IR remote control.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x5C                        // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library
}


void loop() 
{
  // Check if a code has been received
  byte count = mLink.IR_Count(I2C_ADD);

  if(count)
  {
    // Is it a valid NEC code?
    if(mLink.IR_NEC_Valid(I2C_ADD))
    {
      // If so then get the codes address and command bytes
      byte address = mLink.IR_Read_NEC_Add(I2C_ADD);
      byte command = mLink.IR_Read_NEC_Command(I2C_ADD);

      Serial.print("Address = 0x"); Serial.println(address, HEX);
      Serial.print("Command = 0x"); Serial.println(command, HEX);
      Serial.print("Repeated = "); Serial.println(count - 1);
      Serial.println();
    }
  }

  delay(100);                              // Wait a moment before reading again
}
