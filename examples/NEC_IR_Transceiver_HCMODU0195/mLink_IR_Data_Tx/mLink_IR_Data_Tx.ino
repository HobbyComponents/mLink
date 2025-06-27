/* FILE:    mLink_IR_Data_Tx.ino
   DATE:    16/10/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to send 4 bytes of data in a single
NEC IR transmission.

If you have 2 mLink NEC IR modules you can use this sketch in conjunction 
with the mLink_NEC_IR_Data_Rx sketch to send data from one Arduino to 
another.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x5C                        // Default I2C address

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library

  byte data[] = {0x00, 0x01, 0x02, 0x03};   // Array containing the 4 bytes of data to send.
  
  mLink.IR_Write_Data(I2C_ADD, data);       // Write the data to the module
}



void loop() 
{
  mLink.IR_Send(I2C_ADD, 1);                // Send the data
  
  delay(1000);                              // Wait a second before sending again
}
