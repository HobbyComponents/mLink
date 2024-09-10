/* FILE:    mLink_I2C_Scanner.ino
   DATE:    27/03/24
   VERSION: 2.0.0
   AUTHOR:  Andrew Davies
   

This sketch uses the mLink library to scan the I2C bus for attached mLink modules.
If found, the sketch will then print out the module's details to the monitor window.

Supported mLink products:

mLink 12 Bit port expander (SKU: HCMODU0180)
mLink DHT22 temperature and humidity sensor (SKU: HCMODU0181)
mLink 1 channel relay module (SKU: HCMODU0182)
mLink 2 channel relay module (SKU: HCMODU0183)
mLink 4 channel relay module (SKU: HCMODU0184)
mLink RGBW light controller (SKU: HCMODU0185)
mLink NTC Temperature sensor module (SKU: HCMODU0186)
mLink Matrix 4x4 Keypad (SKU: HCMODU0188)
mLink 1602 & 2004 Character LCD (SKU: HCMODU0190A & HCMODU0190B)
mLink 12864 Graphics LCD (SKU: HCMODU0189)
mLink 6 Button Keypad (SKU: HCMODU0193)
mLink Home Sensor (SKU: HCMODU0198)
mLink IR Transceiver (SKU: HCMODU0195)
mLink L9110 DC Motor Controller (SKU: HCMODU0199)
mLink TMP36 Temperature Sensor (HCMODU0187)
mLink WS2812 RGB LED controller (HCMODU0197)
mLink LongReach LoRa Transceiver (HCMODU0250)


If your mLink module is not listed above then please update this sketch & library
to the latest version via our support forum (forum.hobbycompoents.com).

Please see Licence.txt in the library folder for terms of use.
*/

#include "mLink.h"

mLink mLink;

void setup() 
{
  mLink.init();
  Serial.begin(9600);
}

void loop() 
{
  // Start scanning
  Serial.println("Scanning for mLink modules....\r");
  Serial.println();

  // Step through each I2C and check if there is an mLink module there.
  for(byte i = 1; i <= 127; i++)
  {
    // Read the address register
    byte add = mLink.read(i, MLINK_ADD_REG);

    // If the contents of the address register matches the scanned I2C
    // address then it is probably a valid mLink module so output its
    // Address, type, subtype, and firmware version.
    if(i == add)
    {
      Serial.println("Found mLink module:");
      Serial.print("I2C address: 0x"); Serial.println(add, HEX);
      Serial.print("mLink Type: "); printType(add);
      Serial.print("mLink Subtype: "); printSubType(add);
      Serial.print("Firmware Version: "); printVersion(add);
      Serial.println();
    }
  }
  while(1);
}



// Prints the module type
void printType(byte add)
{
  byte type = mLink.read(add, MLINK_MOD_TYPE_REG);

  switch(type)
  {
    case 0x00:
      Serial.print("Digital IO");
      break;

     case 0x01:
      Serial.print("Sensor");
      break;

     case 0x02:
      Serial.print("Relay");
      break;

     case 0x03:
      Serial.print("Light controller");
      break;

     case 0x04:
      Serial.print("Input");
      break;
	  
	 case 0x05:
      Serial.print("Display");
      break;
	 
	 case 0x06:
	  Serial.print("Wireless");
	  break;
	 
	 case 0x07:
	  Serial.print("Motor controller");

     default:
      Serial.print("Unkown: 0x");
      Serial.print(type, HEX);
      break;
  }

  Serial.println();
}



// Prints the module subtype
void printSubType(byte add)
{
  byte type = mLink.read(add, MLINK_MOD_TYPE_REG);
  byte subType = mLink.read(add, MLINK_MOD_SUBTYPE_REG);

  switch(type)
  {
    case 0x00:
      switch(subType)
      {
        case 0x00:
          Serial.print("12 Pin IO");
          break;
      }
      break;

    case 0x01:
      switch(subType)
      {
        case 0x00:
          Serial.print("DHT22 Temp/Hum");
          break;

        case 0x01:
          Serial.print("NTC Temperature");
          break;

        case 0x03:
          Serial.print("Home Sensor");
          break;
      }
      break;

    case 0x02:
      switch(subType)
      {
        case 0x00:
          Serial.print("1 Channel Relay");
          break;

        case 0x01:
          Serial.print("2 Channel Relay");
          break;

        case 0x02:
          Serial.print("4 Channel Relay");
          break;
      }
      break; 

    case 0x03:
      switch(subType)
      {
        case 0x00:
          Serial.print("RGBW PWM LED Controller");
          break;
		
		case 0x01:
		  Serial.print("WS2812 RGB LED Controller");
      }
      break;

    case 0x04:
      switch(subType)
      {
        case 0x00:
          Serial.print("Matrix 4x4 Keypad");
          break;

        case 0x01:
          Serial.print("6 Button Keypad");
          break;
      }
      break;
	  
	case 0x05:
	  switch(subType) 
	  {
		case 0x00:
	      Serial.print("1602 LCD");
		  break;
		
	    case 0x01:
		  Serial.print("2004 LCD");
		  break;
	  }
	  break;
	
	case 0x06:
	  switch(subType) 
	  {
		case 0x00:
	      Serial.print("NEC IR Transceiver");
		  break;
		 
		 case 0x01:
	      Serial.print("LongReach LoRa Tranceiver");
		  break;
	  }
	  break;
	
	case 0x07:
	  switch(subType) 
	  {
		case 0x00:
	      Serial.print("L9110 DC Motor Controller");
		  break;
	  }
	  break;
	  
    default:
      Serial.print("Unkown: 0x");
      Serial.print(subType, HEX);
      break;
  }
  Serial.println();
}


// Prints the firmware version
void printVersion(byte add)
{
  byte ver = mLink.read(add, MLINK_SW_VER_REG);

  Serial.print(ver >> 4);
  Serial.print(".");
  if((ver & 0x0F) < 10)
    Serial.print(0);
  Serial.println(ver & 0x0F);  
}