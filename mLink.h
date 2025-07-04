/* FILE:    mLink.h
   DATE:    25/06/25
   VERSION: 2.3.0
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
06/08/24 version 2.1.0: Added support for LongReach LoRa Transceiver (HCMODU0250)
18/12/24 version 2.2.0: Added suppoer for mLink 12Ch servo controller (HCMODU0263)
						Added support for mLink realy module V1.01 firmware
13/02/25 version 2.2.1: Removed external reference to dtostrf.h and replaced with internal function to stop 
						incompatibility issues with non-standard/non-avr boards
						Added int and unsigned int overloads to the print function for boads where int != int16_t
						and unsigned int != uint16_t
19/05/25 version 2.2.2: Deprecated LORA_Tx_Done() and replaced it with LORA_Tx_Busy() as the former implied the 
						opposite logic levels.
27/05/25 version 2.2.3: Fixed minor bug in mLink Relay Read_Relay_0.ino sketch that caused a compile error.
25/06/25 version 2.3.0:	Added support for mLink environmental sensor (HCMODU0265)
						Added readFloat() function.



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
mLink LongReach LoRa Transceiver (HCMODU0250)
mLink 12 Channel Servo Controller (HCMODU0263)
mLink Environmental Sensor (HCMODU0265)

Please see Licence.txt in the library folder for terms of use.
*/


#ifndef MLINK_h
#define MLINK_h


#include "Arduino.h"


/***********************************************************
	 	MLINK REGISTERS COMMON TO ALL MLINK DEVICES
***********************************************************/
enum MLINK_STD_REGISTERS
{
  MLINK_STATUS_REG = 0,
  MLINK_ADD_REG = 1,
  MLINK_MOD_TYPE_REG = 2,
  MLINK_MOD_SUBTYPE_REG = 3,
  MLINK_SW_VER_REG = 4,
  MLINK_SLEEP_REG = 5
};
/**********************************************************/


/***********************************************************
  MLINK STATUS REGISTER BITS COMMON TO ALL MLINK DEVICES
***********************************************************/
#define MLINK_STATUS_REG_COM_ERROR 		(1 << 0)	//COM error
#define MLINK_STATUS_REG_ACCESS_ERROR 	(1 << 1)	//Reg acc error
#define MLINK_STATUS_REG_BUSY			(1 << 2)	//Device busy flag
/**********************************************************/


#ifndef OFF
	#define OFF							0
#endif
#ifndef ON
	#define ON							1
#endif

#ifndef REVERSE
	#define REVERSE						0
#endif
#ifndef FORWARD
	#define FORWARD						1
#endif

/***********************************************************
		MLINK 12 BIT PORT EXPANDER (HCMODU0180)
***********************************************************/

// Default I2C address
#define DIO12_I2C_ADD	0x50

// Module specific registers
enum MLINK_DIO12_REGISTERS
{
	MLINK_DIO12_DIR0_REG = 10,
	MLINK_DIO12_DIR1_REG = 11,
	MLINK_DIO12_DATA0_REG = 12,
	MLINK_DIO12_DATA1_REG = 13,
};

// I2C read and write command macros
#define DIO12_DIR0			MLINK_DIO12_DIR0_REG
#define DIO12_DIR1			MLINK_DIO12_DIR1_REG
#define DIO12_DATA0			MLINK_DIO12_DATA0_REG
#define DIO12_DATA1			MLINK_DIO12_DATA1_REG

#define DIO12_DIR			DIO12_DIR0
#define DIO12_DATA			DIO12_DATA0

#define MLINK_DIO12_DIR		MLINK_DIO12_DIR0_REG
#define MLINK_DIO12_DATA	MLINK_DIO12_DATA0_REG

#define DIO12_DIR_D0 		MLINK_DIO12_DIR0_REG, 0
#define DIO12_DIR_D1 		MLINK_DIO12_DIR0_REG, 1
#define DIO12_DIR_D2 		MLINK_DIO12_DIR0_REG, 2
#define DIO12_DIR_D3 		MLINK_DIO12_DIR0_REG, 3
#define DIO12_DIR_D4 		MLINK_DIO12_DIR0_REG, 4
#define DIO12_DIR_D5 		MLINK_DIO12_DIR0_REG, 5
#define DIO12_DIR_D6 		MLINK_DIO12_DIR0_REG, 6
#define DIO12_DIR_D7 		MLINK_DIO12_DIR0_REG, 7
#define DIO12_DIR_D8 		MLINK_DIO12_DIR1_REG, 0
#define DIO12_DIR_D9 		MLINK_DIO12_DIR1_REG, 1
#define DIO12_DIR_D10 		MLINK_DIO12_DIR1_REG, 2
#define DIO12_DIR_D11 		MLINK_DIO12_DIR1_REG, 3

#define DIO12_D0_OUTPUT		DIO12_DIR_D0, DIO12_OUTPUT
#define DIO12_D1_OUTPUT		DIO12_DIR_D1, DIO12_OUTPUT
#define DIO12_D2_OUTPUT		DIO12_DIR_D2, DIO12_OUTPUT
#define DIO12_D3_OUTPUT		DIO12_DIR_D3, DIO12_OUTPUT
#define DIO12_D4_OUTPUT		DIO12_DIR_D4, DIO12_OUTPUT
#define DIO12_D5_OUTPUT		DIO12_DIR_D5, DIO12_OUTPUT
#define DIO12_D6_OUTPUT		DIO12_DIR_D6, DIO12_OUTPUT
#define DIO12_D7_OUTPUT		DIO12_DIR_D7, DIO12_OUTPUT
#define DIO12_D8_OUTPUT		DIO12_DIR_D8, DIO12_OUTPUT
#define DIO12_D9_OUTPUT		DIO12_DIR_D9, DIO12_OUTPUT
#define DIO12_D10_OUTPUT	DIO12_DIR_D10, DIO12_OUTPUT
#define DIO12_D11_OUTPUT	DIO12_DIR_D11, DIO12_OUTPUT
#define DIO12_D0_INPUT		DIO12_DIR_D0, DIO12_INPUT
#define DIO12_D1_INPUT		DIO12_DIR_D1, DIO12_INPUT
#define DIO12_D2_INPUT		DIO12_DIR_D2, DIO12_INPUT
#define DIO12_D3_INPUT		DIO12_DIR_D3, DIO12_INPUT
#define DIO12_D4_INPUT		DIO12_DIR_D4, DIO12_INPUT
#define DIO12_D5_INPUT		DIO12_DIR_D5, DIO12_INPUT
#define DIO12_D6_INPUT		DIO12_DIR_D6, DIO12_INPUT
#define DIO12_D7_INPUT		DIO12_DIR_D7, DIO12_INPUT
#define DIO12_D8_INPUT		DIO12_DIR_D8, DIO12_INPUT
#define DIO12_D9_INPUT		DIO12_DIR_D9, DIO12_INPUT
#define DIO12_D10_INPUT		DIO12_DIR_D10, DIO12_INPUT
#define DIO12_D11_INPUT		DIO12_DIR_D11, DIO12_INPUT

#define DIO12_D0 			MLINK_DIO12_DATA0_REG, 0
#define DIO12_D1 			MLINK_DIO12_DATA0_REG, 1
#define DIO12_D2 			MLINK_DIO12_DATA0_REG, 2
#define DIO12_D3 			MLINK_DIO12_DATA0_REG, 3
#define DIO12_D4 			MLINK_DIO12_DATA0_REG, 4
#define DIO12_D5 			MLINK_DIO12_DATA0_REG, 5
#define DIO12_D6 			MLINK_DIO12_DATA0_REG, 6
#define DIO12_D7 			MLINK_DIO12_DATA0_REG, 7
#define DIO12_D8 			MLINK_DIO12_DATA1_REG, 0
#define DIO12_D9 			MLINK_DIO12_DATA1_REG, 1
#define DIO12_D10 			MLINK_DIO12_DATA1_REG, 2
#define DIO12_D11 			MLINK_DIO12_DATA1_REG, 3

#define DIO12_OUTPUT		0
#define DIO12_INPUT			1
/**********************************************************/


/***********************************************************
				MLINK DHT22 (HCMODU0181)
***********************************************************/

// Default I2C address
#define DHT22_I2C_ADD	0x51

// Module specific registers
enum MLINK_DHT22_REGISTERS
{
  //MLINK_DHT22_SLEEP_REG = 5,
  MLINK_DHT22_DHTREAD_REG = 10,
  MLINK_DHT22_TEMPL_REG = 11,
  MLINK_DHT22_TEMPH_REG = 12,
  MLINK_DHT22_HUML_REG = 13,
  MLINK_DHT22_HUMH_REG = 14,
};

// I2C read and write command macros
#define DHT22_START_MEAS  	MLINK_DHT22_DHTREAD_REG, 1
#define DHT22_READ_TEMP   	MLINK_DHT22_TEMPL_REG
#define DHT22_READ_HUM   	MLINK_DHT22_HUML_REG

#define DHT22_Start(add)	write(add, MLINK_DHT22_DHTREAD_REG, 1)
#define DHT22_Busy(add)		busy(add)
#define DHT22_Temp(add)		readInt(add, DHT22_READ_TEMP) / (float)10
#define DHT22_Hum(add)		readInt(add, DHT22_READ_HUM) / (float)10

/**********************************************************/


/***********************************************************
				MLINK 4CH RELAY (HCMODU0184)
***********************************************************/

// Default I2C address
#define RLY_I2C_ADD	0x52

// Module specific registers
enum MLINK_4CH_RELAY_REGISTERS
{
	MLINK_RELAY_STATE_REG = 10,
	MLINK_RLY0_ON_TIME_L = 11,
	MLINK_RLY0_ON_TIME_H = 12,
	MLINK_RLY1_ON_TIME_L = 13,
	MLINK_RLY1_ON_TIME_H = 14,
	MLINK_RLY2_ON_TIME_L = 15,
	MLINK_RLY2_ON_TIME_H = 16,
	MLINK_RLY3_ON_TIME_L = 17,
	MLINK_RLY3_ON_TIME_H = 18,
	MLINK_RLY_ON		 = 19,
	MLINK_RLY_OFF		 = 20,
	MLINK_RLY0_TIMER_RES = 21,
	MLINK_RLY1_TIMER_RES = 22,
	MLINK_RLY2_TIMER_RES = 23,
	MLINK_RLY3_TIMER_RES = 24
};

// I2C read and write command macros
#define RLY4CH_RLY0_OFF 			MLINK_RELAY_STATE_REG, 0, 0
#define RLY4CH_RLY0_ON 				MLINK_RELAY_STATE_REG, 0, 1
#define RLY4CH_RLY1_OFF 			MLINK_RELAY_STATE_REG, 1, 0
#define RLY4CH_RLY1_ON 				MLINK_RELAY_STATE_REG, 1, 1
#define RLY4CH_RLY2_OFF 			MLINK_RELAY_STATE_REG, 2, 0
#define RLY4CH_RLY2_ON 				MLINK_RELAY_STATE_REG, 2, 1
#define RLY4CH_RLY3_OFF 			MLINK_RELAY_STATE_REG, 3, 0
#define RLY4CH_RLY3_ON 				MLINK_RELAY_STATE_REG, 3, 1

#define RLY_RES_1S					0
#define RLY_RES_100MS				1

#define SET_RLY0(add, state)		writeBit(add, MLINK_RELAY_STATE_REG, 0, state)
#define SET_RLY1(add, state)		writeBit(add, MLINK_RELAY_STATE_REG, 1, state)
#define SET_RLY2(add, state)		writeBit(add, MLINK_RELAY_STATE_REG, 2, state)
#define SET_RLY3(add, state)		writeBit(add, MLINK_RELAY_STATE_REG, 3, state)

#define READ_RLY0(add)				readBit(add, MLINK_RELAY_STATE_REG, 0)
#define READ_RLY1(add)				readBit(add, MLINK_RELAY_STATE_REG, 1)
#define READ_RLY2(add)				readBit(add, MLINK_RELAY_STATE_REG, 2)
#define READ_RLY3(add)				readBit(add, MLINK_RELAY_STATE_REG, 3)

#define RLY0_ON_TIME				MLINK_RLY0_ON_TIME_L
#define RLY1_ON_TIME				MLINK_RLY1_ON_TIME_L
#define RLY2_ON_TIME				MLINK_RLY2_ON_TIME_L
#define RLY3_ON_TIME				MLINK_RLY3_ON_TIME_L

#define RLY0_SetOnTime(add, time)	writeInt(add, MLINK_RLY0_ON_TIME_L, time)
#define RLY1_SetOnTime(add, time)	writeInt(add, MLINK_RLY1_ON_TIME_L, time)
#define RLY2_SetOnTime(add, time)	writeInt(add, MLINK_RLY2_ON_TIME_L, time)
#define RLY3_SetOnTime(add, time)	writeInt(add, MLINK_RLY3_ON_TIME_L, time)

#define RLY_ON(add, index)			write(add, MLINK_RLY_ON, index);
#define RLY_OFF(add, index)			write(add, MLINK_RLY_OFF, index);
#define RLY0_TIMER_RES(add, time)	write(add, MLINK_RLY0_TIMER_RES, time);
#define RLY1_TIMER_RES(add, time)	write(add, MLINK_RLY1_TIMER_RES, time);
#define RLY2_TIMER_RES(add, time)	write(add, MLINK_RLY2_TIMER_RES, time);
#define RLY3_TIMER_RES(add, time)	write(add, MLINK_RLY3_TIMER_RES, time);
/**********************************************************/


/***********************************************************
				MLINK RGBW CONTROLLER (HCMODU0185)
***********************************************************/

// Default I2C address
#define RGBW_I2C_ADD	0x53

// Module specific registers
enum MLINK_RGBW_CONTROLLER_REGISTERS
{
	MLINK_RGBW_R_REG = 					10,	
	MLINK_RGBW_G_REG = 					11,	
	MLINK_RGBW_B_REG = 					12,	
	MLINK_RGBW_W_REG = 					13,	
	MLINK_RGBW_BRIGHT_REG = 			14,
	MLINK_RGBW_LOAD_CYCLE_REG = 		15,
	MLINK_RGBW_PAT_STEP_SPEED_L_REG = 	16,
	MLINK_RGBW_PAT_STEP_SPEED_H_REG = 	17,
	MLINK_RGBW_PAT_STEPS_REG = 			18,
	MLINK_RGBW_PAT_COLOURS_REG	=		19,
	
	MLINK_RGBW_I2C_R_0_REG =			20,
	MLINK_RGBW_I2C_G_0_REG =			21,
	MLINK_RGBW_I2C_B_0_REG =			22,
	
	MLINK_RGBW_I2C_R_1_REG =			23,
	MLINK_RGBW_I2C_G_1_REG =			24,
	MLINK_RGBW_I2C_B_1_REG =			25,
	
	MLINK_RGBW_I2C_R_2_REG =			26,
	MLINK_RGBW_I2C_G_2_REG =			27,
	MLINK_RGBW_I2C_B_2_REG =			28,
	
	MLINK_RGBW_I2C_R_3_REG =			29,
	MLINK_RGBW_I2C_G_3_REG =			30,
	MLINK_RGBW_I2C_B_3_REG =			31,
	
	MLINK_RGBW_I2C_R_4_REG =			32,
	MLINK_RGBW_I2C_G_4_REG =			33,
	MLINK_RGBW_I2C_B_4_REG =			34,

	MLINK_RGBW_I2C_R_5_REG =			35,
	MLINK_RGBW_I2C_G_5_REG =			36,
	MLINK_RGBW_I2C_B_5_REG =			37,
	
	MLINK_RGBW_I2C_R_6_REG =			38,
	MLINK_RGBW_I2C_G_6_REG =			39,
	MLINK_RGBW_I2C_B_6_REG =			40,
	
	MLINK_RGBW_I2C_R_7_REG =			41,
	MLINK_RGBW_I2C_G_7_REG =			42,
	MLINK_RGBW_I2C_B_7_REG =			43,
	
	MLINK_RGBW_SAVE_REG = 				44
};


enum MLINK_RGBW_CYCLES
{
	RGBW_CYCLE_USER = 0,
	RGBW_CYCLE_FAST_RGB_COLOUR_CYCLE = 1, 
	RGBW_CYCLE_MED_RGB_COLOUR_CYCLE = 2, 
	RGBW_CYCLE_SLOW_RGB_COLOUR_CYCLE = 3, 
	RGBW_CYCLE_FAST_RG_CYCLE = 4, 
	RGBW_CYCLE_ALARM_INTER_PULSE = 5, 
	RGBW_CYCLE_ALARM_CONT_PULSE = 6,
	RGBW_CYCLE_RGB_CONT_PULSE = 7,	
	RGBW_CYCLE_FLAME = 8
};


// I2C read and write command macros
#define RGBW_R_LEVEL			MLINK_RGBW_R_REG
#define RGBW_G_LEVEL			MLINK_RGBW_G_REG
#define RGBW_B_LEVEL			MLINK_RGBW_B_REG
#define RGBW_W_LEVEL			MLINK_RGBW_W_REG


#define RGBW_BRIGHTNESS 		MLINK_RGBW_BRIGHT_REG
#define RGBW_LOAD_CYCLE			MLINK_RGBW_LOAD_CYCLE_REG
#define RGBW_CYCLE_STEP_SPEED 	MLINK_RGBW_PAT_STEP_SPEED_L_REG
#define RGBW_CYCLE_STEPS		MLINK_RGBW_PAT_STEPS_REG

#define RGBW_CYCLE_COLOURS 		MLINK_RGBW_PAT_COLOURS_REG
#define RGBW_CYCLE_COLORS 		MLINK_RGBW_PAT_COLOURS_REG

#define RGBW_R_0				MLINK_RGBW_I2C_R_0_REG
#define RGBW_G_0				MLINK_RGBW_I2C_G_0_REG
#define RGBW_B_0				MLINK_RGBW_I2C_B_0_REG
#define RGBW_R_1				MLINK_RGBW_I2C_R_1_REG
#define RGBW_G_1				MLINK_RGBW_I2C_G_1_REG
#define RGBW_B_1				MLINK_RGBW_I2C_B_1_REG
#define RGBW_R_2				MLINK_RGBW_I2C_R_2_REG
#define RGBW_G_2				MLINK_RGBW_I2C_G_2_REG
#define RGBW_B_2				MLINK_RGBW_I2C_B_2_REG
#define RGBW_R_3				MLINK_RGBW_I2C_R_3_REG
#define RGBW_G_3				MLINK_RGBW_I2C_G_3_REG
#define RGBW_B_3				MLINK_RGBW_I2C_B_3_REG
#define RGBW_R_4				MLINK_RGBW_I2C_R_4_REG
#define RGBW_G_4				MLINK_RGBW_I2C_G_4_REG
#define RGBW_B_4				MLINK_RGBW_I2C_B_4_REG
#define RGBW_R_5				MLINK_RGBW_I2C_R_5_REG
#define RGBW_G_5				MLINK_RGBW_I2C_G_5_REG
#define RGBW_B_5				MLINK_RGBW_I2C_B_5_REG
#define RGBW_R_6				MLINK_RGBW_I2C_R_6_REG
#define RGBW_G_6				MLINK_RGBW_I2C_G_6_REG
#define RGBW_B_6				MLINK_RGBW_I2C_B_6_REG
#define RGBW_R_7				MLINK_RGBW_I2C_R_7_REG
#define RGBW_G_7				MLINK_RGBW_I2C_G_7_REG
#define RGBW_B_7				MLINK_RGBW_I2C_B_7_REG

#define RGBW_RGB_0				MLINK_RGBW_I2C_R_0_REG, 3
#define RGBW_RGB_1				MLINK_RGBW_I2C_R_1_REG, 3
#define RGBW_RGB_2				MLINK_RGBW_I2C_R_2_REG, 3
#define RGBW_RGB_3				MLINK_RGBW_I2C_R_3_REG, 3
#define RGBW_RGB_4				MLINK_RGBW_I2C_R_4_REG, 3
#define RGBW_RGB_5				MLINK_RGBW_I2C_R_5_REG, 3
#define RGBW_RGB_6				MLINK_RGBW_I2C_R_6_REG, 3
#define RGBW_RGB_7				MLINK_RGBW_I2C_R_7_REG, 3

#define RGBW_SAVE 				MLINK_RGBW_SAVE_REG, 1

#define RGBW_CYCLE(A)			MLINK_RGBW_I2C_R_0_REG, sizeof(A), (uint8_t *)A

//#define RGBW_RED				&(uint8_t[3]){255,0,0}
#define RGBW_RED				255,0,0
#define RGBW_ORANGE				255,100,0
#define RGBW_YELLOW				255,255,0
#define RGBW_MINT				100,255,100
#define RGBW_GREEN				0,255,0
#define RGBW_LIGHT_TEAL			0,255,100
#define RGBW_TEAL				0,255,255
#define RGBW_COLD_BLUE			0,100,255
#define RGBW_BLUE				0,0,255
#define RGBW_VIOLET				100,0,255
#define RGBW_PURPLE				255,0,255
#define RGBW_PINK				255,100,100
#define RGBW_WHITE				255,255,255

/**********************************************************/

/***********************************************************
			MLINK NTC TEMP SENSOR (HCMODU0186)
***********************************************************/

// Default I2C address
#define NTC_I2C_ADD	0x54

// Module specific registers
enum MLINK_NTC_REGISTERS
{
  MLINK_NTC_TEMPL_REG = 11,
  MLINK_NTC_TEMPH_REG = 12,
};

// I2C read and write command macros
#define NTC_READ_TEMP   	MLINK_NTC_TEMPL_REG
#define NTC_Temp(add)		readInt(add, NTC_READ_TEMP) / (float)10

/**********************************************************/

/***********************************************************
			MLINK 4x4 MATRIX KEYPAD (HCMODU0188)
***********************************************************/

// Default I2C address
#define KEYPAD_4X4_I2C_ADD	0x55

// Module specific registers
enum MLINK_KEYPAD_4X4_REGISTERS
{
  MLINK_KEYPAD_4X4_KEY_REG = 11,
  MLINK_KEYPAD_4X4_KEY_STATE_REG = 12,
  MLINK_KEYPAD_4X4_KEY_DEBOUNCE_REG = 13
};

// I2C read and write command macros
#define KEYPAD_4X4_KEY				MLINK_KEYPAD_4X4_KEY_REG
#define KEYPAD_4X4_KEY_STATE		MLINK_KEYPAD_4X4_KEY_STATE_REG
#define KEYPAD_4X4_DEBOUNCE			MLINK_KEYPAD_4X4_KEY_DEBOUNCE_REG

#define Keypad_4x4_Key_Down(add)	readBit(add, KEYPAD_4X4_KEY_STATE, 0)
/**********************************************************/


/***********************************************************
			MLINK CHAR LCD (HCMODU0190)
***********************************************************/
// Default I2C address
#define CLCD_I2C_ADD	0x56

// Module specific registers
enum MLINK_CLCD_REGISTERS
{
  MLINK_CLCD_PRINT_CHAR_REG = 			11,
  MLINK_CLCD_CURS_COL_REG = 			12,
  MLINK_CLCD_CURS_ROW_REG = 			13,
  MLINK_CLCD_CR1 = 						14,
  MLINK_CLCD_CR2 = 						15,
  MLINK_CLCD_SET_BL_REG = 				16,
  MLINK_CLCD_SET_CONT_REG = 			17,
  MLINK_CLCD_PRINT_CUST_REG = 			18,
  MLINK_CLCD_CUST0_REG = 				19,
  MLINK_CLCD_CUST1_REG = 				20,
  MLINK_CLCD_CUST2_REG = 				21,
  MLINK_CLCD_CUST3_REG = 				22,
  MLINK_CLCD_CUST4_REG = 				23,
  MLINK_CLCD_CUST5_REG = 				24,
  MLINK_CLCD_CUST6_REG = 				25,
  MLINK_CLCD_CUST7_REG = 				26,
};

#define CLCD_CLEAR_BIT					0
#define CLCD_DISP_ON_BIT				1
#define CLCD_CURS_DIR_BIT				0
#define CLCD_DISP_TYPE_BIT				1

#define CURS_LTOR						0
#define CURS_RTOL						1

#define CLCD_TYPE_1602					0
#define CLCD_TYPE_2004					1


#define CLCD_COL						MLINK_CLCD_CURS_COL_REG
#define CLCD_ROW						MLINK_CLCD_CURS_ROW_REG
#define CLCD_CR1						MLINK_CLCD_CR1
#define CLCD_CR2						MLINK_CLCD_CR2
#define CLCD_PRINT						MLINK_CLCD_PRINT_CHAR_REG

#define CLCD_PRINT_CUST					MLINK_CLCD_PRINT_CUST_REG
#define CLCD_CUST0						MLINK_CLCD_CUST0_REG
#define CLCD_CUST1						MLINK_CLCD_CUST1_REG
#define CLCD_CUST2						MLINK_CLCD_CUST2_REG
#define CLCD_CUST3						MLINK_CLCD_CUST3_REG
#define CLCD_CUST4						MLINK_CLCD_CUST4_REG
#define CLCD_CUST5						MLINK_CLCD_CUST5_REG
#define CLCD_CUST6						MLINK_CLCD_CUST6_REG
#define CLCD_CUST7						MLINK_CLCD_CUST7_REG

#define CLCD_BACKLIGHT					MLINK_CLCD_SET_BL_REG
#define CLCD_CONTRAST					MLINK_CLCD_SET_CONT_REG


// Character LCD command macros
#define cLCD_cursor(add, c, r) 			writeInt(add, CLCD_COL, ((uint16_t)r << 8) | (uint8_t)c)
#define cLCD_clear(add)					writeBit(add, MLINK_CLCD_CR1, CLCD_CLEAR_BIT, 1); 
#define cLCD_on(add, s)					writeBit(add, MLINK_CLCD_CR1, CLCD_DISP_ON_BIT, s); 
#define cLCD_cursDir(add, dir)			writeBit(add, MLINK_CLCD_CR2, CLCD_CURS_DIR_BIT, dir); 
#define cLCD_dispType(add, type)		writeBit(add, MLINK_CLCD_CR2, CLCD_DISP_TYPE_BIT, type); 
#define cLCD_backlight(add, level)		write(add, CLCD_BACKLIGHT, level)
#define cLCD_contrast(add, level)		write(add, CLCD_CONTRAST, level)

#define cLCD_print(add, d)				print(add, CLCD_PRINT, d)
#define cLCD_printFloat(add, n, dp)		print(add, CLCD_PRINT, (float)n, dp)
#define cLCD_printCust(add, i)			write(add, CLCD_PRINT_CUST, i)

#define cLCD_setCust0(add, bitmap)   	write(add, CLCD_CUST0, 8, (uint8_t *)bitmap)
#define cLCD_setCust1(add, bitmap) 		write(add, CLCD_CUST1, 8, (uint8_t *)bitmap)
#define cLCD_setCust2(add, bitmap) 		write(add, CLCD_CUST2, 8, (uint8_t *)bitmap)
#define cLCD_setCust3(add, bitmap) 		write(add, CLCD_CUST3, 8, (uint8_t *)bitmap)
#define cLCD_setCust4(add, bitmap) 		write(add, CLCD_CUST4, 8, (uint8_t *)bitmap)
#define cLCD_setCust5(add, bitmap) 		write(add, CLCD_CUST5, 8, (uint8_t *)bitmap)
#define cLCD_setCust6(add, bitmap) 		write(add, CLCD_CUST6, 8, (uint8_t *)bitmap)
#define cLCD_setCust7(add, bitmap) 		write(add, CLCD_CUST7, 8, (uint8_t *)bitmap)

/**********************************************************/


/***********************************************************
	 	MLINK GRAPHICS LCD KEYPAD (HCMODU0190)
***********************************************************/
// Default I2C address
#define GLCD_I2C_ADD	0x57

// Module specific registers
enum MLINK_GLCD_REGISTERS
{
  MLINK_GLCD_CR1 = 						11,
  MLINK_GLCD_SET_BL_REG = 				13,	
  MLINK_GLCD_SCALEXY_REG = 				14,
  MLINK_GLCD_DRAWMODE_REG =				15,	
  MLINK_GLCD_ROTATE_REG =				16,	
	
  MLINK_GLCD_PRINT_CHAR_REG = 			17,
  MLINK_GLCD_CURS_COL_L_REG = 			18,
  MLINK_GLCD_CURS_COL_H_REG = 			19,
  MLINK_GLCD_CURS_ROW_L_REG = 			20,
  MLINK_GLCD_CURS_ROW_H_REG = 			21,

  MLINK_GLCD_SETGETPIXEL_REG = 			22,
  MLINK_GLCD_CLRPIXEL_REG = 			23,

  MLINK_GLCD_LINE_REG = 				24,
  MLINK_GLCD_RECT_REG = 				25,
  MLINK_GLCD_ERASE_REG = 				26,

  MLINK_CCHAR0_ASCII_REG =				27,
  MLINK_CCHAR1_ASCII_REG =				28,
  MLINK_CCHAR2_ASCII_REG =				29,
  MLINK_CCHAR3_ASCII_REG =				30,
  MLINK_CCHAR4_ASCII_REG =				31,
  MLINK_CCHAR5_ASCII_REG =				32,
  MLINK_CCHAR6_ASCII_REG =				33,
  MLINK_CCHAR7_ASCII_REG =				34,
  MLINK_CCHAR8_ASCII_REG =				35,
  MLINK_CCHAR9_ASCII_REG =				36,
  MLINK_CCHAR10_ASCII_REG =				37,
  MLINK_CCHAR11_ASCII_REG =				38,
  MLINK_CCHAR12_ASCII_REG =				39,
  MLINK_CCHAR13_ASCII_REG =				40,
  MLINK_CCHAR14_ASCII_REG =				41,
  MLINK_CCHAR15_ASCII_REG =				42,
  
  MLINK_CCHAR0_BITMAP_REG =				43,
  MLINK_CCHAR1_BITMAP_REG =				44,
  MLINK_CCHAR2_BITMAP_REG =				45,
  MLINK_CCHAR3_BITMAP_REG =				46,
  MLINK_CCHAR4_BITMAP_REG =				47,
  MLINK_CCHAR5_BITMAP_REG =				48,
  MLINK_CCHAR6_BITMAP_REG =				49,
  MLINK_CCHAR7_BITMAP_REG =				50,
  MLINK_CCHAR8_BITMAP_REG =				51,
  MLINK_CCHAR9_BITMAP_REG =				52,
  MLINK_CCHAR10_BITMAP_REG =			53,
  MLINK_CCHAR11_BITMAP_REG =			54,
  MLINK_CCHAR12_BITMAP_REG =			55,
  MLINK_CCHAR13_BITMAP_REG =			56,
  MLINK_CCHAR14_BITMAP_REG =			57,
  MLINK_CCHAR15_BITMAP_REG =			58,
};


#define GLCD_PRINT						MLINK_GLCD_PRINT_CHAR_REG
#define GLCD_COL						MLINK_GLCD_CURS_COL_L_REG
#define GLCD_ROW						MLINK_GLCD_CURS_ROW_L_REG
#define GLCD_COLROW						MLINK_GLCD_CURS_COL_L_REG
#define GLCD_BACKLIGHT					MLINK_GLCD_SET_BL_REG
#define GLCD_LINE						MLINK_GLCD_LINE_REG
#define GLCD_RECT						MLINK_GLCD_RECT_REG
#define GLCD_ERASE						MLINK_GLCD_ERASE_REG
#define GLCD_SETPIXEL					MLINK_GLCD_SETGETPIXEL_REG
#define GLCD_CLRPIXEL					MLINK_GLCD_CLRPIXEL_REG
#define GLCD_GETPIXEL					MLINK_GLCD_SETGETPIXEL_REG
#define GLCD_SCALEXY					MLINK_GLCD_SCALEXY_REG

#define GLCD_CC0_ASCII_CODE				MLINK_CCHAR0_ASCII_REG
#define GLCD_CC1_ASCII_CODE				MLINK_CCHAR1_ASCII_REG
#define GLCD_CC2_ASCII_CODE				MLINK_CCHAR2_ASCII_REG
#define GLCD_CC3_ASCII_CODE				MLINK_CCHAR3_ASCII_REG
#define GLCD_CC4_ASCII_CODE				MLINK_CCHAR4_ASCII_REG
#define GLCD_CC5_ASCII_CODE				MLINK_CCHAR5_ASCII_REG
#define GLCD_CC6_ASCII_CODE				MLINK_CCHAR6_ASCII_REG
#define GLCD_CC7_ASCII_CODE				MLINK_CCHAR7_ASCII_REG
#define GLCD_CC8_ASCII_CODE				MLINK_CCHAR8_ASCII_REG
#define GLCD_CC9_ASCII_CODE				MLINK_CCHAR9_ASCII_REG
#define GLCD_CC10_ASCII_CODE			MLINK_CCHAR10_ASCII_REG
#define GLCD_CC11_ASCII_CODE			MLINK_CCHAR11_ASCII_REG
#define GLCD_CC12_ASCII_CODE			MLINK_CCHAR12_ASCII_REG
#define GLCD_CC13_ASCII_CODE			MLINK_CCHAR13_ASCII_REG
#define GLCD_CC14_ASCII_CODE			MLINK_CCHAR14_ASCII_REG
#define GLCD_CC15_ASCII_CODE			MLINK_CCHAR15_ASCII_REG

#define GLCD_CC0_BITMAP					MLINK_CCHAR0_BITMAP_REG
#define GLCD_CC1_BITMAP					MLINK_CCHAR1_BITMAP_REG
#define GLCD_CC2_BITMAP					MLINK_CCHAR2_BITMAP_REG
#define GLCD_CC3_BITMAP					MLINK_CCHAR3_BITMAP_REG
#define GLCD_CC4_BITMAP					MLINK_CCHAR4_BITMAP_REG
#define GLCD_CC5_BITMAP					MLINK_CCHAR5_BITMAP_REG
#define GLCD_CC6_BITMAP					MLINK_CCHAR6_BITMAP_REG
#define GLCD_CC7_BITMAP					MLINK_CCHAR7_BITMAP_REG
#define GLCD_CC8_BITMAP					MLINK_CCHAR8_BITMAP_REG
#define GLCD_CC9_BITMAP					MLINK_CCHAR9_BITMAP_REG
#define GLCD_CC10_BITMAP				MLINK_CCHAR10_BITMAP_REG
#define GLCD_CC11_BITMAP				MLINK_CCHAR11_BITMAP_REG
#define GLCD_CC12_BITMAP				MLINK_CCHAR12_BITMAP_REG
#define GLCD_CC13_BITMAP				MLINK_CCHAR13_BITMAP_REG
#define GLCD_CC14_BITMAP				MLINK_CCHAR14_BITMAP_REG
#define GLCD_CC15_BITMAP				MLINK_CCHAR15_BITMAP_REG

#define GLCD_CLEAR_BIT					0
#define GLCD_DISP_ON_BIT				1
#define GLCD_BITMAP_BG_MODE_BIT			2

#define GLCD_DRAW_MODE_NORMAL			0
#define GLCD_DRAW_MODE_INVERT			1

#define GLCD_BG_OFF						0
#define GLCD_BG_ON						1

#define GLCD_ROTATE_0					0
#define GLCD_ROTATE_90					1
#define GLCD_ROTATE_180					2
#define GLCD_ROTATE_270					3

#define gLCD_print(add, d)				print(add, GLCD_PRINT, d, true)
#define gLCD_printFloat(add, n, dp)		print(add, GLCD_PRINT, n, dp, true)

#define gLCD_cursorCol(add, c) 			writeInt(add, GLCD_COL, (int16_t)c)
#define gLCD_cursorRow(add, r) 			writeInt(add, GLCD_ROW, (int16_t)r)
//#define gLCD_cursor(add, c, r)			writeLong(add, GLCD_COLROW, ((uint32_t)r << 16) | (uint16_t)c)
#define gLCD_cursor(add, c, r)			write(add, GLCD_COLROW, (uint16_t)c, (uint16_t)r)
#define gLCD_getCol(add)				readInt(add, GLCD_COL)
#define gLCD_getRow(add)				readInt(add, GLCD_ROW)

#define gLCD_clear(add)					writeBit(add, MLINK_GLCD_CR1, GLCD_CLEAR_BIT, 1)
#define gLCD_on(add, s)					writeBit(add, MLINK_GLCD_CR1, GLCD_DISP_ON_BIT, s, true)
#define gLCD_backlight(add, level)		write(add, GLCD_BACKLIGHT, level)

#define gLCD_line(add, x1, y1, x2, y2)  write(add, GLCD_LINE, (uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, true)
#define gLCD_rect(add, x1, y1, x2, y2)  write(add, GLCD_RECT, (uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, true)
#define gLCD_erase(add, x1, y1, x2, y2) write(add, GLCD_ERASE, (uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, true)
#define gLCD_setPixel(add, x1, y1)  	write(add, GLCD_SETPIXEL, (uint16_t)x1, (uint16_t)y1, true)
#define gLCD_clrPixel(add, x1, y1)  	write(add, GLCD_CLRPIXEL, (uint16_t)x1, (uint16_t)y1, true)
#define gLCD_getPixel(add)				readBit(add, GLCD_GETPIXEL, 0)
#define gLCD_scaleXY(add, x, y)			write(add, GLCD_SCALEXY, (x << 4) | (y & 0b1111))
#define gLCD_drawMode(add, mode)		write(add, MLINK_GLCD_DRAWMODE_REG, mode)

#define gLCD_bgMode(add, mode)			writeBit(add, MLINK_GLCD_CR1, GLCD_BITMAP_BG_MODE_BIT, mode) 
#define gLCD_scnRotate(add, d)			write(add, MLINK_GLCD_ROTATE_REG, d)

#define gLCD_setCustCode0(add, a)		write(add, GLCD_CC0_ASCII_CODE, a)
#define gLCD_setCustCode1(add, a)		write(add, GLCD_CC1_ASCII_CODE, a)
#define gLCD_setCustCode2(add, a)		write(add, GLCD_CC2_ASCII_CODE, a)
#define gLCD_setCustCode3(add, a)		write(add, GLCD_CC3_ASCII_CODE, a)
#define gLCD_setCustCode4(add, a)		write(add, GLCD_CC4_ASCII_CODE, a)
#define gLCD_setCustCode5(add, a)		write(add, GLCD_CC5_ASCII_CODE, a)
#define gLCD_setCustCode6(add, a)		write(add, GLCD_CC6_ASCII_CODE, a)
#define gLCD_setCustCode7(add, a)		write(add, GLCD_CC7_ASCII_CODE, a)
#define gLCD_setCustCode8(add, a)		write(add, GLCD_CC8_ASCII_CODE, a)
#define gLCD_setCustCode9(add, a)		write(add, GLCD_CC9_ASCII_CODE, a)
#define gLCD_setCustCode10(add, a)		write(add, GLCD_CC10_ASCII_CODE, a)
#define gLCD_setCustCode11(add, a)		write(add, GLCD_CC11_ASCII_CODE, a)
#define gLCD_setCustCode12(add, a)		write(add, GLCD_CC12_ASCII_CODE, a)
#define gLCD_setCustCode13(add, a)		write(add, GLCD_CC13_ASCII_CODE, a)
#define gLCD_setCustCode14(add, a)		write(add, GLCD_CC14_ASCII_CODE, a)
#define gLCD_setCustCode15(add, a)		write(add, GLCD_CC15_ASCII_CODE, a)

#define gLCD_setCustBitmap0(add, b)   	write(add, GLCD_CC0_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap1(add, b)   	write(add, GLCD_CC1_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap2(add, b)   	write(add, GLCD_CC2_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap3(add, b)   	write(add, GLCD_CC3_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap4(add, b)   	write(add, GLCD_CC4_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap5(add, b)   	write(add, GLCD_CC5_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap6(add, b)   	write(add, GLCD_CC6_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap7(add, b)   	write(add, GLCD_CC7_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap8(add, b)   	write(add, GLCD_CC8_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap9(add, b)   	write(add, GLCD_CC9_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap10(add, b)   	write(add, GLCD_CC10_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap11(add, b)   	write(add, GLCD_CC11_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap12(add, b)   	write(add, GLCD_CC12_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap13(add, b)   	write(add, GLCD_CC13_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap14(add, b)   	write(add, GLCD_CC14_BITMAP, sizeof(b), (uint8_t *)b)
#define gLCD_setCustBitmap15(add, b)	write(add, GLCD_CC15_BITMAP, sizeof(b), (uint8_t *)b)
/**********************************************************/


/***********************************************************
		MLINK TMP36 Temperature Sensor (HCMODU0187)
***********************************************************/
// Default I2C address
#define TMP36_I2C_ADD	0x58

// Module specific registers
enum MLINK_TMP36_REGISTERS
{
  MLINK_TMP36_TEMPL_REG =				11,
  MLINK_TMP36_TEMPH_REG =				12,
};

// I2C read and write command macros
#define TMP36_READ_TEMP   	MLINK_TMP36_TEMPL_REG
#define TMP36_Temp(add)		readInt(add, TMP36_READ_TEMP) / (float)10
/**********************************************************/


/***********************************************************
	 	MLINK 6 Button Pad (HCMODU0193)
***********************************************************/
// Default I2C address
#define BPAD_I2C_ADD	0x59

// Module specific registers
enum MLINK_BPAD_REGISTERS
{
  MLINK_BPAD_BUFF_STATUS_REG =			10,
  MLINK_BPAD_BUFFER_REG =				11,
  MLINK_BPAD_KEYSTATE_REG =				12,
  MLINK_BPAD_DEBOUNCE_REG =				13,
};


#define BPAD_BUFFER_STATUS				MLINK_BPAD_BUFF_STATUS_REG
#define BPAD_BUFFER						MLINK_BPAD_BUFFER_REG
#define BPAD_KEYSTATE					MLINK_BPAD_KEYSTATE_REG
#define BPAD_DEBOUNCE					MLINK_BPAD_DEBOUNCE_REG

#define BPAD_UP_BIT						0
#define BPAD_LEFT_BIT					1
#define BPAD_DOWN_BIT					2
#define BPAD_RIGHT_BIT					3
#define BPAD_SELECT_BIT					4
#define BPAD_BACK_BIT					5

#define BPAD_BUFF_EMPTY_BIT				0
#define BPAD_BUFF_FULL_BIT				1

#define bPad_Empty(add)					readBit(add, BPAD_BUFFER_STATUS, BPAD_BUFF_EMPTY_BIT)
#define bPad_Read(add)					read(add, BPAD_BUFFER)
#define bPad_UpState(add)				readBit(add, BPAD_KEYSTATE, BPAD_UP_BIT)
#define bPad_LeftState(add)				readBit(add, BPAD_KEYSTATE, BPAD_LEFT_BIT)
#define bPad_DownState(add)				readBit(add, BPAD_KEYSTATE, BPAD_DOWN_BIT)
#define bPad_RightState(add)			readBit(add, BPAD_KEYSTATE, BPAD_RIGHT_BIT)
#define bPad_SelectState(add)			readBit(add, BPAD_KEYSTATE, BPAD_SELECT_BIT)
#define bPad_BackState(add)				readBit(add, BPAD_KEYSTATE, BPAD_BACK_BIT)

#define bPad_Debounce(add, d)			write(add, BPAD_DEBOUNCE, d)
/**********************************************************/



/***********************************************************
	 	MLINK Home Sensor (HCMODU0198)
***********************************************************/
// Default I2C address
#define HSENS_I2C_ADD	0x5B

// Module specific registers
enum MLINK_HSENS_REGISTERS
{
  

  MLINK_HSENS_DHTREAD_REG =				10,
  MLINK_HSENS_TEMPL_REG =				11,
  MLINK_HSENS_TEMPH_REG =				12,
  MLINK_HSENS_HUML_REG =				13,
  MLINK_HSENS_HUMH_REG =				14,
  
  MLINK_HSENS_PIR_REG =					15,
  MLINK_HSENS_LDR_REG =					16,
  
  MLINK_HSENS_PIR_TRIGS_L_REG =			17,
  MLINK_HSENS_PIR_TRIGS_H_REG =			18
};


#define HSENS_START_MEAS  				MLINK_HSENS_DHTREAD_REG, 1
#define HSENS_READ_TEMP					MLINK_HSENS_TEMPL_REG
#define HSENS_READ_HUM					MLINK_HSENS_HUML_REG
#define HSENS_READ_PIR					MLINK_HSENS_PIR_REG
#define HSENS_READ_LDR					MLINK_HSENS_LDR_REG
#define HSENS_READ_PIR_TRIGS			MLINK_HSENS_PIR_TRIGS_L_REG

#define HSENS_DHT22_MEAS_ERROR_BIT		3

// I2C read and write command macros
#define HSense_Start_Meas(add)			write(add, HSENS_START_MEAS, 1)
#define HSens_Temp(add)					readInt(add, HSENS_READ_TEMP) / (float)10
#define HSens_Hum(add)					readInt(add, HSENS_READ_HUM) / (float)10
#define HSens_DHT22_Error(add)			readBit(add, MLINK_STATUS_REG, HSENS_DHT22_MEAS_ERROR_BIT)
#define HSens_LDR(add)					read(add, HSENS_READ_LDR)
#define HSens_PIR(add)					read(add, HSENS_READ_PIR)
#define HSens_Trigs(add)				readInt(add, HSENS_READ_PIR_TRIGS)
#define HSens_Clear_Trigs(add)			write(add, HSENS_READ_PIR_TRIGS, 0)

/***********************************************************
			MLINK IR Transceiver (HCMODU0195)
***********************************************************/
// Default I2C address
#define IR_I2C_ADD	0x5C

// Module specific registers
enum MLINK_IR_REGISTERS
{
  MLINK_IR_RX_COUNT_REG =				10,
  MLINK_IR_DATA0_REG =					11,
  MLINK_IR_DATA1_REG =					12,
  MLINK_IR_DATA2_REG =					13,
  MLINK_IR_DATA3_REG =					14,
  
  MLINK_IR_SEND_REG =					15,
  
  MLINK_IR_NEC_ADD_REG =				16,
  MLINK_IR_NEC_COM_REG =				17,
  
  MLINK_IR_COM_MODE_REG = 				18
};

#define IR_VALID_BIT					3

#define IR_COM_LED_I2C					0
#define IR_COM_LED_IR					1

#define IR_Write_Data(add, data)		write(add, MLINK_IR_DATA0_REG, 4, data)
#define IR_Write_NEC(add, iradd, irdat)	 writeInt(add, MLINK_IR_NEC_ADD_REG, ((uint16_t)irdat << 8) | (uint8_t)iradd)
#define IR_Count(add)					read(add, MLINK_IR_RX_COUNT_REG);
#define IR_NEC_Valid(add)				readBit(add, MLINK_STATUS_REG, IR_VALID_BIT)
#define IR_Read(add, data)				read(add, MLINK_IR_DATA0_REG, 4, (uint8_t *)data)
#define IR_Read_NEC_Add(add)			read(add, MLINK_IR_DATA0_REG)
#define IR_Read_NEC_Command(add)		read(add, MLINK_IR_DATA2_REG)
#define IR_Send(add, count)				write(add, MLINK_IR_SEND_REG, count)
#define IR_Com_LED_Mode(add, mode)		write(add, MLINK_IR_COM_MODE_REG, mode)


/***********************************************************
		MLINK L9110 DC MOTOR CONTROLLER (HCMODU0199)
***********************************************************/
// Default I2C address
#define L9110_I2C_ADD	0x5D

// Module specific registers
enum MLINK_L9110_REGISTERS
{
  MLINK_L9110_M1_SPEED_REG =			10,
  MLINK_L9110_M2_SPEED_REG =			11,
  MLINK_L9110_M1_DIR_REG =				12,
  MLINK_L9110_M2_DIR_REG =				13
};

#define L9110_M1_SPEED					MLINK_L9110_M1_SPEED_REG
#define L9110_M2_SPEED					MLINK_L9110_M2_SPEED_REG
#define L9110_M1_DIR					MLINK_L9110_M1_DIR_REG
#define L9110_M2_DIR					MLINK_L9110_M2_DIR_REG

#define L9110_M1_Speed(add, speed)		write(add, L9110_M1_SPEED, speed)
#define L9110_M2_Speed(add, speed)		write(add, L9110_M2_SPEED, speed)

#define L9110_M1_Dir(add, dir)			write(add, L9110_M1_DIR, dir)
#define L9110_M2_Dir(add, dir)			write(add, L9110_M2_DIR, dir)

#define L9110_M1_Stop(add)				write(add, L9110_M1_SPEED, 0)
#define L9110_M2_Stop(add)				write(add, L9110_M2_SPEED, 0)



/***********************************************************
		MLINK WS2812 RGB LED CONTROLLER (HCMODU0197)
***********************************************************/
// Default I2C address
#define WS2812_I2C_ADD	0x5E

// Module specific registers
enum MLINK_WS2812_REGISTERS
{
  MLINK_WS2812_LED_COUNT_REG =			10,
  MLINK_WS2812_LED_INDEX_REG =			11,
  MLINK_WS2812_WRITE_RED_REG =			12,
  MLINK_WS2812_WRITE_GRN_REG =			13,
  MLINK_WS2812_WRITE_BLU_REG =			14,
  MLINK_WS2812_REFRESH_REG =			15,
  MLINK_WS2812_CLEAR_BUFFER_REG =		16,
  MLINK_WS2812_BRIGHTNESS_REG =			17,
  MLINK_WS2812_ON_STATE_REG =			18,
  MLINK_WS2812_RGB_ORDER_REG =			19
};


#define WS2812_COUNT					MLINK_WS2812_LED_COUNT_REG
#define WS2812_INDEX					MLINK_WS2812_LED_INDEX_REG
#define WS2812_R						MLINK_WS2812_WRITE_RED_REG
#define WS2812_G						MLINK_WS2812_WRITE_GRN_REG
#define WS2812_B						MLINK_WS2812_WRITE_BLU_REG
#define WS2812_REFRESH					MLINK_WS2812_REFRESH_REG
#define WS2812_CLEAR					MLINK_WS2812_CLEAR_BUFFER_REG
#define WS2812_BRIGHTNESS				MLINK_WS2812_BRIGHTNESS_REG
#define WS2812_ON_STATE					MLINK_WS2812_ON_STATE_REG
#define WS2812_RGBORDER					MLINK_WS2812_RGB_ORDER_REG

#define WS2812_ORDER_RGB				0
#define WS2812_ORDER_GRB				1


#define WS2812_Max(add, c)				write(add, WS2812_COUNT, c)
#define WS2812_Index(add, i)			write(add, WS2812_INDEX, i)
#define WS2812_Red(add, r)				write(add, WS2812_R, r)
#define WS2812_Green(add, g)			write(add, WS2812_G, g)
#define WS2812_Blue(add, b)				write(add, WS2812_B, b)
#define WS2812_Refresh(add)				write(add, WS2812_REFRESH, 1)
#define WS2812_Clear(add)				writewb(add, WS2812_CLEAR, 1)
#define WS2812_Brightness(add, l)		write(add, WS2812_BRIGHTNESS, l)
#define WS2812_On(add, s)				write(add, WS2812_ON_STATE, s)
#define WS2812_Order(add, o)			write(add, WS2812_RGBORDER, o)

#define WS2812_RGB(add, i, r, g, b)		write(I2C_ADD, WS2812_INDEX, ((uint16_t)r << 8) | (uint8_t)i , ((uint16_t)b << 8) | (uint8_t)g, false)

#define WS2812_WriteBuffer(add, d)		write(add, WS2812_R, sizeof(d), (uint8_t *)d)  

#define WS2812_Get_Red(add)				read(add, WS2812_R)
#define WS2812_Get_Green(add)			read(add, WS2812_G)
#define WS2812_Get_Blue(add)			read(add, WS2812_B)
#define WS2812_Get_Brightness(add)		read(add, WS2812_BRIGHTNESS)
#define WS2812_Get_On_State(add)		read(add, WS2812_ON_STATE)



/***********************************************************
		MLINK LONGREACH RM95 LORA MODULE (HCMODU0250)
***********************************************************/
// Default I2C address
#define LONGREACH_I2C_ADD	0x5F

// Module specific registers
enum MLINK_LORA_REGISTERS
{
  LORA_RX_AVAILABLE_REG =				10,
  LORA_RX_SIZE_REG =					11,
  LORA_RX_READ_REG =					12,
  LORA_RX_ADD_REG =						13,
  LORA_TX_LOAD_REG =					14,
  LORA_TX_SEND_REG =					15,
  LORA_TX_BUSY_REG =					16,
  LORA_MODE_REG =						17,
  LORA_FREQ_REG_L =						18,
  LORA_BW_REG =							19,
  LORA_SF_REG =							20,
  LORA_RSSI_REG_L =						21,
  LORA_RSSI_REG_H =						22,
  LORA_LR_MODE_REG = 					23,
  LORA_RESENDS_REG =					24,
  LORA_RESEND_DELAY_L_REG =				25,
  LORA_RESEND_DELAY_H_REG =				26
};



// RF Bandwidth options
#define LORA_BW_7_8KHz					0b0000
#define LORA_BW_10_4KHz					0b0001
#define LORA_BW_15_6KHz					0b0010
#define LORA_BW_20_8KHz					0b0011
#define LORA_BW_31_25KHz				0b0100
#define LORA_BW_41_7KHz					0b0101
#define LORA_BW_62_5KHz					0b0110
#define LORA_BW_125KHz					0b0111
#define LORA_BW_250KHz					0b1000
#define LORA_BW_500KHz					0b1001

// RF spreading factor options
#define LORA_SF_64						6
#define LORA_SF_128						7
#define LORA_SF_256						8
#define LORA_SF_512						9
#define LORA_SF_1024					10
#define LORA_SF_2048					11
#define LORA_SF_4096					12

#define LR_MODE_OFF						0
#define LR_MODE_ON						1


#define LORA_MODE_SLEEP					0b000
#define LORA_MODE_STDBY					0b001
#define LORA_MODE_TRANSMIT				0b011
#define LORA_MODE_RXCONTINUOUS			0b101
#define LORA_MODE_RXSINGLE				0b110


#define LORA_RX_AVAILABLE				LORA_RX_AVAILABLE_REG
#define LORA_RX_SIZE					LORA_RX_SIZE_REG
#define LORA_RX_READ					LORA_RX_READ_REG
#define LORA_RX_ADD						LORA_RX_ADD_REG
#define LORA_TX_LOAD					LORA_TX_LOAD_REG
#define LORA_TX_SEND					LORA_TX_SEND_REG
#define LORA_TX_BUSY					LORA_TX_BUSY_REG
#define LORA_MODE						LORA_MODE_REG
#define LORA_FREQ_L 					LORA_FREQ_REG_L
#define LORA_FREQ_H 					LORA_FREQ_REG_H
#define LORA_BW							LORA_BW_REG
#define LORA_SF							LORA_SF_REG
#define LORA_RSSI_L						LORA_RSSI_REG_L
#define LORA_RSSI_H						LORA_RSSI_REG_H
#define LORA_LR_MODE					LORA_LR_MODE_REG
#define LORA_RESENDS					LORA_RESENDS_REG
#define LORA_RESEND_DELAY_L				LORA_RESEND_DELAY_L_REG	
#define LORA_RESEND_DELAY_H				LORA_RESEND_DELAY_H_REG	


#define LORA_Rx_Available(add)			readBit(add, LORA_RX_AVAILABLE, 0)
#define LORA_Rx_Size(add)				read(add, LORA_RX_SIZE)
#define LORA_Rx_Read(add, s, b)			read(add, LORA_RX_READ, s, b)
#define LORA_Rx_Address(add)			read(add, LORA_RX_ADD)

#define LORA_Tx_Load(add, s, d)			write(add, LORA_TX_LOAD, (uint8_t)s, (uint8_t *)d)
#define LORA_Tx_Send(add)				write(add, LORA_TX_SEND, 1) 
#define LORA_Tx_LR_Send(add, lrAdd)		write(add, LORA_TX_SEND, lrAdd) 
//#define LORA_Tx_Done(add)				readBit(add, LORA_TX_DONE, 0)
#define LORA_Tx_Busy(add)				readBit(add, LORA_TX_BUSY, 0)

#define LORA_Freq(add, f)				writewb(add, LORA_FREQ_L, f)
#define LORA_Set_BW(add, bw)			writewb(add, LORA_BW, bw)
#define LORA_Set_SF(add, sf)			writewb(add, LORA_SF, sf)
#define LORA_RSSI(add)					readInt(add, LORA_RSSI_L)
#define LORA_LR_Mode(add, m)			writewb(add, LORA_LR_MODE, m)
#define LORA_Mode(add, m)				writewb(add, LORA_MODE, m)
#define LORA_Resends(add, r)			write(add, LORA_RESENDS, r) 
#define LORA_Resend_Delay(add, d)		writeInt(add, LORA_RESEND_DELAY_L_REG, d)


/***********************************************************
	MLINK 12 CHANNEL SERVO CONTROLLER MODULE (HCMODU0263)
***********************************************************/
// Default I2C address
#define SERVO_I2C_ADD	0x60

// Module specific registers
enum MLINK_SERVO_REGISTERS
{
  MLINK_SERVO0_POS_REG =				10,
  MLINK_SERVO1_POS_REG =				11,
  MLINK_SERVO2_POS_REG =				12,
  MLINK_SERVO3_POS_REG =				13,
  MLINK_SERVO4_POS_REG =				14,
  MLINK_SERVO5_POS_REG =				15,
  MLINK_SERVO6_POS_REG =				16,
  MLINK_SERVO7_POS_REG =				17,
  MLINK_SERVO8_POS_REG =				18,
  MLINK_SERVO9_POS_REG =				19,
  MLINK_SERVO10_POS_REG =				20,
  MLINK_SERVO11_POS_REG =				21,
  
  MLINK_SERVO0_LIM_REG_L = 				22,
  MLINK_SERVO1_LIM_REG_L = 				23,
  MLINK_SERVO2_LIM_REG_L = 				24,
  MLINK_SERVO3_LIM_REG_L = 				25,
  MLINK_SERVO4_LIM_REG_L = 				26,
  MLINK_SERVO5_LIM_REG_L = 				27,
  MLINK_SERVO6_LIM_REG_L = 				28,
  MLINK_SERVO7_LIM_REG_L = 				29,
  MLINK_SERVO8_LIM_REG_L = 				30,
  MLINK_SERVO9_LIM_REG_L = 				31,
  MLINK_SERVO10_LIM_REG_L = 			32,
  MLINK_SERVO11_LIM_REG_L = 			33,
  
  MLINK_SERVO0_LIM_REG_H = 				34,
  MLINK_SERVO1_LIM_REG_H = 				35,
  MLINK_SERVO2_LIM_REG_H = 				36,
  MLINK_SERVO3_LIM_REG_H = 				37,
  MLINK_SERVO4_LIM_REG_H = 				38,
  MLINK_SERVO5_LIM_REG_H = 				39,
  MLINK_SERVO6_LIM_REG_H = 				40,
  MLINK_SERVO7_LIM_REG_H = 				41,
  MLINK_SERVO8_LIM_REG_H = 				42,
  MLINK_SERVO9_LIM_REG_H = 				43,
  MLINK_SERVO10_LIM_REG_H = 			44,
  MLINK_SERVO11_LIM_REG_H = 			45,
  
  MLINK_SERVO_ON_REG =					46,
  MLINK_SERVO_OFF_REG =					47,
	
  MLINK_SERVO_SAVE_REG =				48,
};


#define SERVO_SAVE_STATE				0
#define SERVO_SAVE_DEFAULTS				1

#define MLINK_SERVO0_POS				MLINK_SERVO0_POS_REG
#define MLINK_SERVO1_POS				MLINK_SERVO1_POS_REG
#define MLINK_SERVO2_POS				MLINK_SERVO2_POS_REG
#define MLINK_SERVO3_POS				MLINK_SERVO3_POS_REG
#define MLINK_SERVO4_POS				MLINK_SERVO4_POS_REG
#define MLINK_SERVO5_POS				MLINK_SERVO5_POS_REG
#define MLINK_SERVO6_POS				MLINK_SERVO6_POS_REG
#define MLINK_SERVO7_POS				MLINK_SERVO7_POS_REG
#define MLINK_SERVO8_POS				MLINK_SERVO8_POS_REG
#define MLINK_SERVO9_POS				MLINK_SERVO9_POS_REG
#define MLINK_SERVO10_POS				MLINK_SERVO10_POS_REG
#define MLINK_SERVO11_POS				MLINK_SERVO11_POS_REG

#define MLINK_SERVO0_LIM_L				MLINK_SERVO0_LIM_REG_L
#define MLINK_SERVO1_LIM_L				MLINK_SERVO1_LIM_REG_L
#define MLINK_SERVO2_LIM_L				MLINK_SERVO2_LIM_REG_L
#define MLINK_SERVO3_LIM_L				MLINK_SERVO3_LIM_REG_L
#define MLINK_SERVO4_LIM_L				MLINK_SERVO4_LIM_REG_L
#define MLINK_SERVO5_LIM_L				MLINK_SERVO5_LIM_REG_L
#define MLINK_SERVO6_LIM_L				MLINK_SERVO6_LIM_REG_L
#define MLINK_SERVO7_LIM_L				MLINK_SERVO7_LIM_REG_L
#define MLINK_SERVO8_LIM_L				MLINK_SERVO8_LIM_REG_L
#define MLINK_SERVO9_LIM_L				MLINK_SERVO9_LIM_REG_L
#define MLINK_SERVO10_LIM_L				MLINK_SERVO10_LIM_REG_L
#define MLINK_SERVO11_LIM_L				MLINK_SERVO11_LIM_REG_L

#define MLINK_SERVO0_LIM_H				MLINK_SERVO0_LIM_REG_H
#define MLINK_SERVO1_LIM_H				MLINK_SERVO1_LIM_REG_H
#define MLINK_SERVO2_LIM_H				MLINK_SERVO2_LIM_REG_H
#define MLINK_SERVO3_LIM_H				MLINK_SERVO3_LIM_REG_H
#define MLINK_SERVO4_LIM_H				MLINK_SERVO4_LIM_REG_H
#define MLINK_SERVO5_LIM_H				MLINK_SERVO5_LIM_REG_H
#define MLINK_SERVO6_LIM_H				MLINK_SERVO6_LIM_REG_H
#define MLINK_SERVO7_LIM_H				MLINK_SERVO7_LIM_REG_H
#define MLINK_SERVO8_LIM_H				MLINK_SERVO8_LIM_REG_H
#define MLINK_SERVO9_LIM_H				MLINK_SERVO9_LIM_REG_H
#define MLINK_SERVO10_LIM_H				MLINK_SERVO10_LIM_REG_H
#define MLINK_SERVO11_LIM_H				MLINK_SERVO11_LIM_REG_H

#define MLINK_SERVO_ON					MLINK_SERVO_ON_REG
#define MLINK_SERVO_OFF					MLINK_SERVO_OFF_REG

#define MLINK_SERVO_SAVE				MLINK_SERVO_SAVE_REG


#define servo_On(a, s)					write(a, MLINK_SERVO_ON, s); 
#define servo_Off(a, s)					write(a, MLINK_SERVO_OFF, s);

#define servo0_On(a)					write(a, MLINK_SERVO_ON, 0); 
#define servo1_On(a)					write(a, MLINK_SERVO_ON, 1); 
#define servo2_On(a)					write(a, MLINK_SERVO_ON, 2); 
#define servo3_On(a)					write(a, MLINK_SERVO_ON, 3); 
#define servo4_On(a)					write(a, MLINK_SERVO_ON, 4); 
#define servo5_On(a)					write(a, MLINK_SERVO_ON, 5); 
#define servo6_On(a)					write(a, MLINK_SERVO_ON, 6); 
#define servo7_On(a)					write(a, MLINK_SERVO_ON, 7); 
#define servo8_On(a)					write(a, MLINK_SERVO_ON, 8); 
#define servo9_On(a)					write(a, MLINK_SERVO_ON, 9); 
#define servo10_On(a)					write(a, MLINK_SERVO_ON, 10); 
#define servo11_On(a)					write(a, MLINK_SERVO_ON, 11);

#define servo0_Off(a)					write(a, MLINK_SERVO_OFF, 0);
#define servo1_Off(a)					write(a, MLINK_SERVO_OFF, 1);
#define servo2_Off(a)					write(a, MLINK_SERVO_OFF, 2);
#define servo3_Off(a)					write(a, MLINK_SERVO_OFF, 3);
#define servo4_Off(a)					write(a, MLINK_SERVO_OFF, 4);
#define servo5_Off(a)					write(a, MLINK_SERVO_OFF, 5);
#define servo6_Off(a)					write(a, MLINK_SERVO_OFF, 6);
#define servo7_Off(a)					write(a, MLINK_SERVO_OFF, 7);
#define servo8_Off(a)					write(a, MLINK_SERVO_OFF, 8);
#define servo9_Off(a)					write(a, MLINK_SERVO_OFF, 9);
#define servo10_Off(a)					write(a, MLINK_SERVO_OFF, 10);
#define servo11_Off(a)					write(a, MLINK_SERVO_OFF, 11);

#define servo0_Pos(a, p)				write(a, MLINK_SERVO0_POS, p)
#define servo1_Pos(a, p)				write(a, MLINK_SERVO1_POS, p)
#define servo2_Pos(a, p)				write(a, MLINK_SERVO2_POS, p)
#define servo3_Pos(a, p)				write(a, MLINK_SERVO3_POS, p)
#define servo4_Pos(a, p)				write(a, MLINK_SERVO4_POS, p)
#define servo5_Pos(a, p)				write(a, MLINK_SERVO5_POS, p)
#define servo6_Pos(a, p)				write(a, MLINK_SERVO6_POS, p)
#define servo7_Pos(a, p)				write(a, MLINK_SERVO7_POS, p)
#define servo8_Pos(a, p)				write(a, MLINK_SERVO8_POS, p)
#define servo9_Pos(a, p)				write(a, MLINK_SERVO9_POS, p)
#define servo10_Pos(a, p)				write(a, MLINK_SERVO10_POS, p)
#define servo11_Pos(a, p)				write(a, MLINK_SERVO11_POS, p)

#define servo0_LimLow(a, p)				write(a, MLINK_SERVO0_LIM_L, p)
#define servo1_LimLow(a, p)				write(a, MLINK_SERVO1_LIM_L, p)
#define servo2_LimLow(a, p)				write(a, MLINK_SERVO2_LIM_L, p)
#define servo3_LimLow(a, p)				write(a, MLINK_SERVO3_LIM_L, p)
#define servo4_LimLow(a, p)				write(a, MLINK_SERVO4_LIM_L, p)
#define servo5_LimLow(a, p)				write(a, MLINK_SERVO5_LIM_L, p)
#define servo6_LimLow(a, p)				write(a, MLINK_SERVO6_LIM_L, p)
#define servo7_LimLow(a, p)				write(a, MLINK_SERVO7_LIM_L, p)
#define servo8_LimLow(a, p)				write(a, MLINK_SERVO8_LIM_L, p)
#define servo9_LimLow(a, p)				write(a, MLINK_SERVO9_LIM_L, p)
#define servo10_LimLow(a, p)			write(a, MLINK_SERVO10_LIM_L, p)
#define servo11_LimLow(a, p)			write(a, MLINK_SERVO11_LIM_L, p)

#define servo0_LimHigh(a, p)			write(a, MLINK_SERVO0_LIM_H, p)
#define servo1_LimHigh(a, p)			write(a, MLINK_SERVO1_LIM_H, p)
#define servo2_LimHigh(a, p)			write(a, MLINK_SERVO2_LIM_H, p)
#define servo3_LimHigh(a, p)			write(a, MLINK_SERVO3_LIM_H, p)
#define servo4_LimHigh(a, p)			write(a, MLINK_SERVO4_LIM_H, p)
#define servo5_LimHigh(a, p)			write(a, MLINK_SERVO5_LIM_H, p)
#define servo6_LimHigh(a, p)			write(a, MLINK_SERVO6_LIM_H, p)
#define servo7_LimHigh(a, p)			write(a, MLINK_SERVO7_LIM_H, p)
#define servo8_LimHigh(a, p)			write(a, MLINK_SERVO8_LIM_H, p)
#define servo9_LimHigh(a, p)			write(a, MLINK_SERVO9_LIM_H, p)
#define servo10_LimHigh(a, p)			write(a, MLINK_SERVO10_LIM_H, p)
#define servo11_LimHigh(a, p)			write(a, MLINK_SERVO11_LIM_H, p)

#define servo0_GetPos(a)				read(a, MLINK_SERVO0_POS)
#define servo1_GetPos(a)				read(a, MLINK_SERVO1_POS)
#define servo2_GetPos(a)				read(a, MLINK_SERVO2_POS)
#define servo3_GetPos(a)				read(a, MLINK_SERVO3_POS)
#define servo4_GetPos(a)				read(a, MLINK_SERVO4_POS)
#define servo5_GetPos(a)				read(a, MLINK_SERVO5_POS)
#define servo6_GetPos(a)				read(a, MLINK_SERVO6_POS)
#define servo7_GetPos(a)				read(a, MLINK_SERVO7_POS)
#define servo8_GetPos(a)				read(a, MLINK_SERVO8_POS)
#define servo9_GetPos(a)				read(a, MLINK_SERVO9_POS)
#define servo10_GetPos(a)				read(a, MLINK_SERVO10_POS)
#define servo11_GetPos(a)				read(a, MLINK_SERVO11_POS)

#define servo0_getLimLow(a)				read(a, MLINK_SERVO0_LIM_L)
#define servo1_getLimLow(a)				read(a, MLINK_SERVO1_LIM_L)
#define servo2_getLimLow(a)				read(a, MLINK_SERVO2_LIM_L)
#define servo3_getLimLow(a)				read(a, MLINK_SERVO3_LIM_L)
#define servo4_getLimLow(a)				read(a, MLINK_SERVO4_LIM_L)
#define servo5_getLimLow(a)				read(a, MLINK_SERVO5_LIM_L)
#define servo6_getLimLow(a)				read(a, MLINK_SERVO6_LIM_L)
#define servo7_getLimLow(a)				read(a, MLINK_SERVO7_LIM_L)
#define servo8_getLimLow(a)				read(a, MLINK_SERVO8_LIM_L)
#define servo9_getLimLow(a)				read(a, MLINK_SERVO9_LIM_L)
#define servo10_getLimLow(a)			read(a, MLINK_SERVO10_LIM_L)
#define servo11_getLimLow(a)			read(a, MLINK_SERVO11_LIM_L)

#define servo0_getLimHigh(a)			read(a, MLINK_SERVO0_LIM_H)
#define servo1_getLimHigh(a)			read(a, MLINK_SERVO1_LIM_H)
#define servo2_getLimHigh(a)			read(a, MLINK_SERVO2_LIM_H)
#define servo3_getLimHigh(a)			read(a, MLINK_SERVO3_LIM_H)
#define servo4_getLimHigh(a)			read(a, MLINK_SERVO4_LIM_H)
#define servo5_getLimHigh(a)			read(a, MLINK_SERVO5_LIM_H)
#define servo6_getLimHigh(a)			read(a, MLINK_SERVO6_LIM_H)
#define servo7_getLimHigh(a)			read(a, MLINK_SERVO7_LIM_H)
#define servo8_getLimHigh(a)			read(a, MLINK_SERVO8_LIM_H)
#define servo9_getLimHigh(a)			read(a, MLINK_SERVO9_LIM_H)
#define servo10_getLimHigh(a)			read(a, MLINK_SERVO10_LIM_H)
#define servo11_getLimHigh(a)			read(a, MLINK_SERVO11_LIM_H)

#define servo_Save_State(a)				write(a, MLINK_SERVO_SAVE, SERVO_SAVE_STATE)
#define servo_Save_Defaults(a)			write(a, MLINK_SERVO_SAVE, SERVO_SAVE_DEFAULTS)


/***********************************************************
		MLINK ENVIRONMENTAL SENSOR (HCMODU0265)
***********************************************************/
// Default I2C address
#define ENV_I2C_ADD	0x61

// Module specific registers
enum MLINK_ENV_REGISTERS
{
  MLINK_ENV_TRIG_REG =					10,
  MLINK_ENV_TMP0_REG =					11,
  MLINK_ENV_TMP1_REG =					12,
  MLINK_ENV_TMP2_REG =					13,
  MLINK_ENV_TMP3_REG =					14,
  
  MLINK_ENV_HUM0_REG =					15,
  MLINK_ENV_HUM1_REG =					16,
  MLINK_ENV_HUM2_REG =					17,
  MLINK_ENV_HUM3_REG =					18,
  
  MLINK_ENV_PRS0_REG =					19,
  MLINK_ENV_PRS1_REG =					20,
  MLINK_ENV_PRS2_REG =					21,
  MLINK_ENV_PRS3_REG = 					22,
  
  MLINK_ENV_AMB0_REG = 					23,
  MLINK_ENV_AMB1_REG = 					24,
  MLINK_ENV_AMB2_REG = 					25,
  MLINK_ENV_AMB3_REG = 					26,
  
  MLINK_ENV_WHT0_REG = 					27,
  MLINK_ENV_WHT1_REG = 					28,
  MLINK_ENV_WHT2_REG = 					29,
  MLINK_ENV_WHT3_REG = 					30,
};


#define envSens_Trigger(add)			write(add, MLINK_ENV_TRIG_REG, 0x01)
#define envSens_Temp(add)				readFloat(add, MLINK_ENV_TMP0_REG)
#define envSens_Hum(add)				readFloat(add, MLINK_ENV_HUM0_REG)
#define envSens_Pres(add)				readFloat(add, MLINK_ENV_PRS0_REG)
#define envSens_Amb(add)				readFloat(add, MLINK_ENV_AMB0_REG)
#define envSens_Wht(add)				readFloat(add, MLINK_ENV_WHT0_REG)

/**********************************************************/



class mLink
{
	public:
		mLink(void);
		void init(void);
		void wake(uint8_t add);
		void sleep(uint8_t add);
		boolean busy(uint8_t add);
		
		void writeBit(uint8_t add, uint8_t reg, uint8_t bit, boolean state, boolean wait = false);
		void write(uint8_t add, uint8_t reg, uint8_t data);
		void writewb(uint8_t add, uint8_t reg, uint8_t data);
		//void writeIntBit(uint8_t add, uint8_t reg, uint8_t bit, boolean state, boolean wait = false);
		void writeInt(uint8_t add, uint8_t reg, uint16_t data, boolean wait = false);	
		//void writeLong(uint8_t add, uint8_t reg, uint32_t data);
		void write(uint8_t add, uint8_t reg, uint16_t a, uint16_t b, boolean wait = false);
		void write(uint8_t add, uint8_t reg, uint16_t a, uint16_t b, uint16_t c, uint16_t d, boolean wait = false);
		void write(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data);	

		boolean readBit(uint8_t add, uint8_t reg, uint8_t bit);
		uint8_t read(uint8_t add, uint8_t reg);
		int16_t readInt(uint8_t add, uint8_t reg);
		uint16_t readuInt(uint8_t add, uint8_t reg);
		float readFloat(uint8_t add, uint8_t reg);
		void read(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data);
		
		void print(uint8_t add, uint8_t reg, char c, boolean wait = false);
		void print(uint8_t add, uint8_t reg, char *str, boolean wait = false);
//		void print(uint8_t add, uint8_t reg, uint16_t val, boolean wait = false);
//		void print(uint8_t add, uint8_t reg, int16_t val, boolean wait = false);
		void print(uint8_t add, uint8_t reg, int val, boolean wait = false);
		void print(uint8_t add, uint8_t reg, unsigned int val, boolean wait = false);
		void print(uint8_t add, uint8_t reg, float val, uint8_t dp = 0, boolean wait = false);


	private:
		void _I2CWriteReg(uint8_t add, uint8_t reg, uint8_t data);
		void _I2CWriteReg(uint8_t add, uint8_t reg, uint8_t bytes, uint8_t *data);
		uint8_t _I2CReadReg(uint8_t add, uint8_t reg);
		void _I2CReadReg(uint8_t add, uint8_t reg, uint16_t bytes, uint8_t *data);
		void _cout(uint8_t add, uint8_t reg, char *str, boolean wait);
		void _floatToCharArray(float n, char* buffer, uint8_t precision);
};

#endif