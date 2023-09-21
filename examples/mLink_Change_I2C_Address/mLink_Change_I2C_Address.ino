/* FILE:    mLink_Change_I2C_Address.ino
   DATE:    24/09/21
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch will use the mLink library to change the I2C address of an mLink
module. 

To use this sketch set  CURRENT_I2C_ADD to the current I2C address of your module.
Then set NEW_I2C_ADD to the address you wish to change the address to.

Run the sketch and the result will be output to the serial monitor.

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h" 

mLink mLink;

#define CURRENT_I2C_ADD 0x50    // Current I2C address
#define NEW_I2C_ADD     0x51    // New I2C address


void setup() 
{
  Serial.begin(9600);
  
  mLink.init();  

  // First check to made sure an mLink module at the new address does'nt alread exist
  if(checkAddress(NEW_I2C_ADD))
    Serial.println("Error: There is alread an mLink module at the new address!");
  else
  {
    // If the new address is free, write it to the current module. 
    // But first we need to unlock the address register by writing 
    // 0x55 then 0xAA to it...
    mLink.write(CURRENT_I2C_ADD, MLINK_ADD_REG, 0x55);
    mLink.write(CURRENT_I2C_ADD, MLINK_ADD_REG, 0xAA);
    
    // ...then we can write the new address:
    mLink.write(CURRENT_I2C_ADD, MLINK_ADD_REG, NEW_I2C_ADD);
    delay(10);

    // Now check the new address to confirm it changed
    if(checkAddress(NEW_I2C_ADD))
      Serial.println("Address change worked!");
    else
      Serial.println("Error: Addrees change failed!");
  }
}

void loop() 
{
}


// Function checks an I2C address to see if there is an mLink module there
boolean checkAddress(byte add)
{
  if(mLink.read(add, MLINK_ADD_REG) == add)
    return true;
  else
    return false;
}