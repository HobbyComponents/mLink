/* FILE:    mLink_IR_Trans_NEC_Tx.ino
   DATE:    16/10/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to send an NEC compatible
address and command code each time your Arduino is reset. 
To get an address and command byte to send just run the 
mLink_IR_Trans_NEC_Rx sketch first and press an appropriate 
button on your IR remote control.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x5C                        // Default I2C address

byte NEC_Add =      0x00;                   // The NEC address byte to send
byte NEC_Command =  0x0A;                   // The NEC command byte to send


void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library

  // Write the NEC address and command
  mLink.IR_Write_NEC(I2C_ADD, NEC_Add, NEC_Command);

  // Send it one time
  mLink.IR_Send(I2C_ADD, 1);
}


void loop() 
{
  // Nothing to do here
}
