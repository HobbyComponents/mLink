/* FILE:    mLink_LongReach_Transmit_Example.ino
   DATE:    29/07/24
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to use the mLink RM95 LoRa module
to transmit commands to LongReach modules such at the LongReach
4CH relay module (HCMODU0249).

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD 0x5F                                  // Default I2C address

char switchON[] = "SW0=1";                            // Example LongReach command to turn switch 0 on
char switchOFF[] = "SW0=0";                           // Example LongReach command to turn switch 0 off


void setup() 
{
  mLink.init();                                       // Initialise the library

  mLink.LORA_LR_Mode(I2C_ADD, LR_MODE_ON);            // Turn on LongReach mode (LR_MODE_OFF to turn off)
}


void loop() 
{
  mLink.LORA_Tx_Load(I2C_ADD, 5, switchON);           // Load the Tx buffer with the switch on command
  mLink.LORA_Tx_LR_Send(I2C_ADD, 0);                  // Send it to LongReach module(s) with address 0
  delay(2000);

  mLink.LORA_Tx_Load(I2C_ADD, 5, switchOFF);          // Load the Tx buffer with the switch off command
  mLink.LORA_Tx_LR_Send(I2C_ADD, 0);                  // Send it to LongReach module(s) with address 0
  delay(2000);
}
