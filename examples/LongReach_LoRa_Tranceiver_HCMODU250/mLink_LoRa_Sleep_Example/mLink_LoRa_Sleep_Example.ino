/* FILE:    mLink_LoRa_Sleep_Example.ino
   DATE:    06/09/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to use the mLink RM95 LoRa module
to transmit LoRa data and then go into a low power sleep mode.

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x5F                                  // Default I2C address

char data[] = "Hello!";                               // Some example data to send

void setup() 
{
  mLink.init();                                       // Initialise the library
}


void loop() 
{
  mLink.wake(I2C_ADD);                                // Wake up if asleep
  
  mLink.LORA_Tx_Load(I2C_ADD, sizeof(data), data);    // Load the data into the Tx buffer

  mLink.LORA_Tx_Send(I2C_ADD);                        // Send it

  while(!mLink.LORA_Tx_Done(I2C_ADD));                // Wait for module to finish transmitting

  // Lets go to sleep !
  mLink.LORA_Mode(I2C_ADD, LORA_MODE_SLEEP);          // Put the radio into sleep mode
  mLink.sleep(I2C_ADD);                               // Put the mLink module to sleep
  
  delay(10000);                                       // Wait a little before sending again
}
