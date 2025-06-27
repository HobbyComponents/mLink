/* FILE:    mLink_IR_Data_Rx.ino
   DATE:    16/10/23
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to read all 4 bytes of a
received NEC IR transmission. If you have 2 mLink NEC IR modules
you can use this sketch in conjunction with the mLink_NEC_IR_Data_Tx
sketch to send data from one Arduino to another.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                          // Include the library

mLink mLink;                                // Create an instance of the library

#define I2C_ADD 0x5C                        // Default I2C address

byte data[4];                               // Array to store the received data.

void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                             // Initialise the library
}


void loop() 
{
  byte count = mLink.IR_Count(I2C_ADD);     // Check if new data has been received

  if(count)
  {
      mLink.IR_Read(I2C_ADD, data);         // Get the data

      Serial.print(data[0], HEX);
      Serial.print(" : ");
      Serial.print(data[1], HEX);
      Serial.print(" : ");
      Serial.print(data[2], HEX);
      Serial.print(" : ");
      Serial.println(data[3], HEX);
  }
  
  delay(100);                              // Wait a little before reading again
}
