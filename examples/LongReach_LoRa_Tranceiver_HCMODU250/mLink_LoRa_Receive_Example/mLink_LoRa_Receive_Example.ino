/* FILE:    mLink_LoRa_Receive_Example.ino
   DATE:    25/07/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to use the mLink RM95 LoRa module
to receive LoRa data.

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x5F                                  // Default I2C address

byte rxBuffer[255];                                   // Buffer to hold Rx data (max 255 bytes)



void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                                       // Initialise the library

  mLink.LORA_Mode(I2C_ADD, LORA_MODE_RXCONTINUOUS);   // Put the module into continuous receive mode
}


void loop() 
{
  boolean avail = mLink.LORA_Rx_Available(I2C_ADD);      // Check for new data

  if(avail)                                          
  { 
    byte size = mLink.LORA_Rx_Size(I2C_ADD);          // Get the length of the data in bytes

    mLink.LORA_Rx_Read(I2C_ADD, size, rxBuffer);      // Read the data into the buffer

    int rssi = mLink.LORA_RSSI(I2C_ADD);              // Get the signal strength (RSSI)

    Serial.print("Size = "); Serial.println(size);    // Print out the details
    Serial.print("RSSI = "); Serial.println(rssi);

    Serial.print("Data = ");                          // Print out the data in hex 
    for(byte i = 0; i < size; i++)
    {
      Serial.print(rxBuffer[i], HEX);
      Serial.print(":");
    }

    Serial.println(); Serial.println();
  }
}
