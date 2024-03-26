/* FILE:    mLink.cpp
   DATE:    23/03/24
   VERSION: 2.0.0
   AUTHOR:  Andrew Davies
   
24/09/21 version 1.0.0: Original version
24/03/22 version 1.1.0: Added support for mLink NTC Temperature sensor module (HCMODU0186)
31/03/22 version 1.2.0: Added support for mLink matrix 4x4 keypad (HCMODU0188)
20/04/22 version 1.3.0: Added support for mLink character LCDs (HCMODU0190x)
08/06/22 version 1.4.0: Added support for mLink 12864 graphics LCD (HCMODU0189)
19/08/22 version 1.5.0: Added support for mLink 6 Button Keypad (SKU: HCMODU0193)
07/01/23 version 1.6.0: Added support for mLink Home Sensor (SKU: HCMODU0198)
16/10/23 version 1.7.0: Added support for mLink IR Transceiver (SKU: HCMODU0195)
20/10/23 version 1.7.1: Minor modification to mLink IR transceiver register naming
28/10/23 version 1.7.2: ExplicitChimp:  Forked repos, Added #include <avr/dtostrf.h> @ line 43 and corrected 
					lines 225 to 228 (inclusive) to read "readBit(RLY_I2C_ADD, ...)"
16/01/23 version 1.7.3: ExplicitChimp:  Corrected lines 225 to 228 (inclusive) to read "readBit(add, ...)"
17/01/23 version 1.7.4: ExplicitChimp:  Correct some issues I created with version history.  Removed #include 
					<avr/dtostrf.h> from line 43, and added a #ifdef statement to capture 
     					none AVR boards requiring <avr/dtostrf.h>.
19/01/24 version 1.8.0: Added support for mLink L9110 DC Motor Driver (SKU: HCMODU0199)
22/01/24 version 1.9.0: Added support for mLink TMP36 temperature sensor (SKU: HCMODU0187)
22/01/24 version 1.9.1: Minor fix to TMP36 default address definition
25/03/24 version 2.0.0:	Added support for mLink WS2812 RGB LED controller (HCMODU0197)


This library adds hardware support for the Hobby Components mLink range of 
serial I2C modules to the Arduino IDE. 
Current supported boards:

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

Please see Licence.txt in the library folder for terms of use.
*/


#include "mLink.h"
#include <Wire.h>

/* I2C Constructor to initialise the GPIO and library */
mLink::mLink(void)
{
	
}




// Initialise the library (init the SPI interface)
void mLink::init(void)
{
	Wire.begin(); 
}




// Wake a module up from sleep mode. Not all modules support this!
void mLink::wake(uint8_t add)
{
	Wire.beginTransmission(add);
	Wire.write(0);
	Wire.write(0);
	Wire.endTransmission(true);
}




/* Puts a module into sleep mode. Not all modules support this!

 PARAMETERS:

 add: byte value containing I2C address of the mLink module.

 RETURNS: 
 Void  
*/
void mLink::sleep(uint8_t add)
{
	_I2CWriteReg(add, MLINK_SLEEP_REG, 1);
}




/* Reads the state of the busy bit in the satus register. Not all modules support 
 this!

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 
 
 
 RETURNS: 
 A boolean value representing the state of the busy bit. 
*/
boolean mLink::busy(uint8_t add)
{
	//uint8_t data;
	
	return _I2CReadReg(add, MLINK_STATUS_REG) & MLINK_STATUS_REG_BUSY;
}




/* Writes to a bit in one of the mLink modules 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to. 

 bit: byte value containing the bit number within the specified register to write to. Valid values are 0 to 7.

 state: boolean value containing the state to set the specified bit to.

 RETURNS: 
 Void 
*/
void mLink::writeBit(uint8_t add, uint8_t reg, uint8_t bit, boolean state, boolean wait)
{
	uint8_t data;

	data = _I2CReadReg(add, reg);
	
	data = (data & ~(1 << bit)) | (state << bit);
	
	_I2CWriteReg(add, reg, data);
	
	if(wait)
		while(busy(add));
}




/* Writes to one of the mLink modules 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to. 

 data: byte value containing the data to write to the register.

 RETURNS: 
 Void 
*/
void mLink::write(uint8_t add, uint8_t reg, uint8_t data)
{
	_I2CWriteReg(add, reg, data);
}



/* Writes to one of the mLink modules 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to. 

 data: byte value containing the data to write to the register.

 RETURNS: 
 Void 
*/
void mLink::writewb(uint8_t add, uint8_t reg, uint8_t data)
{
	_I2CWriteReg(add, reg, data);

	while(busy(add));
}



/* Writes an unsigned integer to two consecutive 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.

 data: unsigned int value containing the data to write to the register.

 RETURNS: 
 Void 
*/
void mLink::writeInt(uint8_t add, uint8_t reg, uint16_t data)
{
	_I2CWriteReg(add, reg, 2, (uint8_t *)&data);
}




/* Writes an unsigned long to four consecutive 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.

 data: unsigned long value containing the data to write to the register.

 RETURNS: 
 Void 
*/
/*void mLink::writeLong(uint8_t add, uint8_t reg, uint32_t data)
{
	_I2CWriteReg(add, reg, 4, (uint8_t *)&data);
}*/




/* Writes two unsigned integers to four consecutive 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.

 a: unsigned int value containing the data to write to the first two registers.
 
 b: unsigned int value containing the data to write to the second two registers.
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.

 RETURNS: 
 Void 
*/
void mLink::write(uint8_t add, uint8_t reg, uint16_t a, uint16_t b, boolean wait)
{
	uint8_t data[4];
	
	data[0] = a;
	data[1] = a >> 8;
	data[2] = b;
	data[3] = b >> 8;
	
	_I2CWriteReg(add, reg, 4, data);
	
	if(wait)
		while(busy(add));
}




/* Writes four unsigned integers to eight consecutive 8 bit registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.

 a: unsigned int value containing the data to write to the first two registers.
 
 b: unsigned int value containing the data to write to the second two registers.
 
 c: unsigned int value containing the data to write to the third two registers.
 
 d: unsigned int value containing the data to write to the fourth two registers.
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.

 RETURNS: 
 Void 
*/
void mLink::write(uint8_t add, uint8_t reg, uint16_t a, uint16_t b, uint16_t c, uint16_t d, boolean wait)
{
	uint8_t data[8];
	
	data[0] = a;
	data[1] = a >> 8;
	data[2] = b;
	data[3] = b >> 8;
	data[4] = c;
	data[5] = c >> 8;
	data[6] = d;
	data[7] = d >> 8;
	
	_I2CWriteReg(add, reg, 8, data);
	
	if(wait)
		while(busy(add));
}




/* Writes data to multiple sequential registers.

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.
 
 bytes: the number of bytes (registers) to be written
 
 *data: A pointer to the start of the data to write to the registers
 
 RETURNS: 
 Void 
*/
void mLink::write(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data)
{
	_I2CWriteReg(add, reg, bytes, data);
}




/* Reads the state of a bit from one of the mLink modules 8 bit registers and      
 returns the result as a boolean value.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to read. 

 bit: byte value containing the bit number within the specified register to read. Valid values are 0 to 7.

 RETURNS: 
 A boolean value representing the state of the bit. 
*/
boolean mLink::readBit(uint8_t add, uint8_t reg, uint8_t bit)
{
	uint8_t data;
	
	data  = _I2CReadReg(add, reg);

	return data & (1 << bit);
}




/* Reads the state of one of the mLink modules 8 bit registers and returns the    
 result as a byte.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to read. 


 RETURNS: 
 A byte value representing the state of the register. 
*/
uint8_t mLink::read(uint8_t add, uint8_t reg)
{
	uint8_t data;
  
	data = _I2CReadReg(add, reg);
	
	return data;
}




/* Reads the state of two consecutive 8 bit registers and returns the result 
 as an unsigned int.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to read. 


 RETURNS: 
 An unsigned int containing both registers where the low byte is the first register and the high byte is the second register.
*/
uint16_t mLink::readuInt(uint8_t add, uint8_t reg)
{
	uint16_t data;
	_I2CReadReg(add, reg, 2, (uint8_t *)&data);
	return data;
}




/* Reads the state of two consecutive 8 bit registers and returns the result 
 as a signed int.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to read. 


 RETURNS: 
 An signed int containing both registers where the low byte is the first register and the high byte is the second register.
*/
int16_t mLink::readInt(uint8_t add, uint8_t reg)
{
	int16_t data;
	_I2CReadReg(add, reg, 2, (uint8_t *)&data);
	return data;
}





/* Reads the state of multiple sequential registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to read. 

 bytes: the number of bytes (registers) to be read
 
 *data: A pointer to the start of the memory to write the data to
 
 RETURNS: 
 Void
*/
void mLink::read(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data)
{
	_I2CReadReg(add, reg, bytes, data);	
}





/* Writes an 8 bit walue of type char to an mLink register

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 c: the char value to write to the register
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::print(uint8_t add, uint8_t reg, char c, boolean wait)
{
	write(add, reg, c, wait);	
}




/* Writes a null terminated character array to an mLink registr

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 *str: a null terminated character array containing the data to write
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::print(uint8_t add, uint8_t reg, char *str, boolean wait)
{
	_cout(add, reg, str, wait);
}




/* Writes an unsigned integer as an ASCII string to one of the mLink registers

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 val: the unsigned integer
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::print(uint8_t add, uint8_t reg, uint16_t val, boolean wait)
{
	char str[20];

	dtostrf(val, 0, 0, str);
	
	_cout(add, reg, str, wait);	
}




/* Writes a signed integer as an ASCII string to one of the mLink registers

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 val: the signed integer
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::print(uint8_t add, uint8_t reg, int16_t val, boolean wait)
{
	char str[20];

	dtostrf(val, 0, 0, str);
	
	_cout(add, reg, str, wait);
}




/* Writes a floating point value as an ASCII string to one of the mLink registers

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 val: the floating point value
 
 dp: optional parameter that specifies the number of decimal places to convert the 
     floating point value to.
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::print(uint8_t add, uint8_t reg, float val, uint8_t dp, boolean wait)
{
	char str[20];

	dtostrf(val, 0, dp, str);
	
	_cout(add, reg, str, wait);

}




/* Private function that writes to one of the mLinks registers.
 
 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.

 data: byte value containing the data to write to the register.

 RETURNS: 
 Void 
*/
void mLink::_I2CWriteReg(uint8_t add, uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(add);
  Wire.write(reg);  
  Wire.write(data);
  Wire.endTransmission(true);
}




/* Private function that writes data to multiple sequential registers.

 PARAMETERS:
 
 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the first register number to write to.
 
 bytes: the number of bytes (register) to be written
 
 *data: A pointer to the start of the data to write to the registers
 
 RETURNS: 
 Void 
*/
void mLink::_I2CWriteReg(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data)
{
  Wire.beginTransmission(add);
  Wire.write(reg);

  for(uint8_t i = 0; i < bytes; i++)
  {
    Wire.write(data[i]);
  }

  Wire.endTransmission(true);
}




/* Private function that reads the state of one of the mLink modules 8 bit   
 registers and returns the result as a byte.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to read. 


 RETURNS: 
 A byte value representing the state of the register. 
*/
uint8_t mLink::_I2CReadReg(uint8_t add, uint8_t reg)
{
  uint8_t Data = 0xFF;

  Wire.beginTransmission(add);
  Wire.write(reg);  
  Wire.endTransmission(true);
  
  Wire.requestFrom((int)add, 1,true);

  Data = Wire.read();

  return Data;
}




/* Private function that reads the state of multiple sequential registers.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to read. 

 bytes: the number of bytes (registers) to be read
 
 *data: A pointer to the start of the memory to write the data to
 
 RETURNS: 
 Void
*/
void mLink::_I2CReadReg(uint8_t add, uint8_t reg, uint16_t bytes, uint8_t *data)
{
  uint16_t i = 0;

  Wire.beginTransmission(add);
  Wire.write(reg);  
  Wire.endTransmission(true);

  
  Wire.requestFrom((int)add, bytes, true);
  do
  {
    data[i] = Wire.read();
    i++;
  }while (Wire.available());
  
}




/* Private function that writes a null terminated character array to an mLink 
   register.

 PARAMETERS:

 add: byte value containing I2C address of the mLink module. 

 reg: byte value containing the register number to write to.
 
 *str: a null terminated character array containing the data to write
 
 wait: optional boolean value that when set to 1 causes the function to wait for
       the busy bit to clear before exiting the function.
 
 RETURNS: 
 Void 
*/
void mLink::_cout(uint8_t add, uint8_t reg, char *str, boolean wait)
{
	uint8_t i = 0;
	
	while(str[i] != '\0')
	{
		write(add, reg, str[i++]);	
		
		if(wait)
			while(busy(add));
	}
}




// Converts a floating point number to string. 
//
// n is the floating point number to convert to a string
//
// *res is a pointer to where store the string to
//
// decimalPlaces is the number of decial places to display the number to 
/*uint8_t mLink::_ftoa(float n, char *res, uint8_t decimalPlaces) 
{ 
		uint8_t k, i;
		uint16_t expo = 1;
		
		// Extract integer part 
    int ipart = (int)n; 
		
    // Extract floating part 
    float fpart = n - (float)ipart; 
		
		// If number is negative the remove the sign
		if(fpart < 0)
			fpart *= -1;
  
	
    // convert integer part to string 
    i = _intToStr(ipart, res, 1); 
  
	
    // Shoud the fractional part be displayed ? 
    if (decimalPlaces != 0) 
    { 
        res[i] = '.';  // Add the decimal point 
  
        // Get the value of fraction part up to given no. 
        // of points after dot. The third parameter is needed 
        // to handle cases like 233.007 
				for(k = 0; k < decimalPlaces; k++)
					expo *= 10;
				
        fpart = fpart * expo;
  
        i = i + 1 + _intToStr((int)fpart, res + i + 1, decimalPlaces); 
    } 
		
	return i;
} */




// Converts an integer to a string.
//
// x is the integer to convert
//
// *str is a pointer to where to save the string to
//
// d is the number of digits required in output. 
// If d is more than the number of digits in x, then 0s are 
// added at the beginning. 
/*int8_t mLink::_intToStr(int16_t x, char *str, uint8_t d) 
{ 
	uint8_t minus = 0;
	int i = 0; 
		
	// If x is negative the add a '-'	
	if(x < 0)
	{
		str[i] = '-';
		str++;
		x *= -1;
		minus = 1;
	}
		
	// Store each digit	
  while(x) 
  //do 
	{ 
    str[i++] = (x%10) + '0'; 
    x = x/10; 
	}//while(x); 
  
	
	// If number of digits required is more, then 
	// add 0s at the beginning 
	while (i < d) 
		str[i++] = '0'; 
  
	// Number has been stored in reverse order to flip it
	_reverse(str, i); 
	
	// Add null terminator
	str[i] = '\0'; 

	return i + minus; 
} */




// reverses a string 'str' of length 'len' 
/*void mLink::_reverse(char *str, uint8_t len) 
{ 
    int i=0, j=len-1, temp; 
    while (i<j) 
    { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; j--; 
    } 
} */