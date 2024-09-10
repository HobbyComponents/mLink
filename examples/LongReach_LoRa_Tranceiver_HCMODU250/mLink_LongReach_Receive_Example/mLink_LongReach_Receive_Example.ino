/* FILE:    mLink_LongReach_Receive_Example.ino
   DATE:    25/07/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to use the mLink RM95 LoRa module
to receive LongReach data packets sent by other Hobby Components
LongReach modules.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x5F                                  // Default I2C address

char rxBuffer[32];                                    // Buffer to hold Rx data (max 32 bytes)


void setup() 
{
  Serial.begin(9600);
  
  mLink.init();                                       // Initialise the library

  mLink.LORA_LR_Mode(I2C_ADD, LR_MODE_ON);            // Put the module into LongReach mode
                                                      // Module will now receive data from other LongReach devices
  
  mLink.LORA_Mode(I2C_ADD, LORA_MODE_RXCONTINUOUS);   // Put the module into continuous receive mode
}


void loop() 
{
  boolean avail = mLink.LORA_Rx_Available(I2C_ADD);      // Check for new data

  if(avail)                                          
  { 
    byte size = mLink.LORA_Rx_Size(I2C_ADD);          // Get the length of the data in bytes

    if(size > 32)                                     // Make sure data does not exceed buffer size
      size = 32;

    mLink.LORA_Rx_Read(I2C_ADD, size, rxBuffer);      // Read the data into the buffer

    int16_t rssi = mLink.LORA_RSSI(I2C_ADD);          // Get the signal strength (RSSI)

    byte address = mLink.LORA_Rx_Address(I2C_ADD);    // Get the address of the module that sent the data address

    Serial.print("Size = "); Serial.println(size);    // Print out the details
    Serial.print("RSSI = "); Serial.println(rssi);
    Serial.print("Address = "); Serial.println(address);

    Serial.print("Data = ");                          // Print out the data as ASCII 
    for(byte i = 0; i < size; i++)
    {
      Serial.print(rxBuffer[i]);
    }
    
    Serial.println(); Serial.println();
  }
}
