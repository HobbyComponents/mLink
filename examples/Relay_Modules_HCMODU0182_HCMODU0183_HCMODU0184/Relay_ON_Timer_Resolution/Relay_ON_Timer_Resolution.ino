/* FILE:    Relay_ON_Timer_Resolution.ino
   DATE:    27/03/25
   VERSION: 1.0

   Relay Timer Resolution Configuration (Firmware v1.01+ only) 

   Version 1.01 of the module's firmware allows setting the relay ON timer  
   resolution to either:  
   - 1-second increments (default)  
   - 100-millisecond increments  

   Use the following mLink library macros to specify the increment time  
   for each relay:  

   RLY0_TIMER_RES(I2C_ADD, RLY_RES_1S);    // Relay 0: 1 second increments  
   RLY0_TIMER_RES(I2C_ADD, RLY_RES_100MS); // Relay 0: 100ms increments  

   RLY1_TIMER_RES(I2C_ADD, RLY_RES_1S);    // Relay 1: 1 second increments  
   RLY1_TIMER_RES(I2C_ADD, RLY_RES_100MS); // Relay 1: 100ms increments  

   RLY2_TIMER_RES(I2C_ADD, RLY_RES_1S);    // Relay 2: 1 second increments  
   RLY2_TIMER_RES(I2C_ADD, RLY_RES_100MS); // Relay 2: 100ms increments  

   RLY3_TIMER_RES(I2C_ADD, RLY_RES_1S);    // Relay 3: 1 second increments  
   RLY3_TIMER_RES(I2C_ADD, RLY_RES_100MS); // Relay 3: 100ms increments  

   Note: This setting is stored in the module’s non-volatile memory,  
   so it only needs to be set once.
*/


#include "mLink.h"                              // Include the library

mLink mLink;                                    // Create an instance of the library

#define I2C_ADD 0x52                            // Default I2C address


void setup() 
{
  mLink.init();                                 // Initialise the library

  mLink.RLY0_TIMER_RES(I2C_ADD, RLY_RES_100MS)  // Set relay 0 to 100ms increments

  mLink.RLY0_SetOnTime(I2C_ADD, 5);             // Set relay 0 on timer to 500ms

  mLink.RLY_ON(I2C_ADD, 0);                     // Trigger relay 0

}

void loop() 
{
  // Nothing to do !

}
