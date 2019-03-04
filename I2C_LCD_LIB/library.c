/*
 * I2C_LCD_LIB.c
 *
 * Created: 04.03.2019 20:28:38
 * Author : Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C_LIB.h"

char savedSlaveAddress = 0;

/************************************************************************/
/* Initializes the LCD for 4-Bit mode                                   */
/************************************************************************/
void initLCD(char slaveAddress)
{
	initI2C(10,'u');
	_delay_ms(500);
	
	sendStartCondition();
	
	if(sendByte(slaveAddress))
	{
		savedSlaveAddress = slaveAddress;
		
		//Init LCD
		_delay_ms(15);
		sendByte(0b00110100);
		sendByte(0b00110000);
		_delay_ms(41);
		sendByte(0b00110100);
		sendByte(0b00110000);
		_delay_us(100);
		sendByte(0b00110100);
		sendByte(0b00110000);
		_delay_ms(41);
		sendByte(0b00100100);
		sendByte(0b00100000);
		
		//Config
		_delay_us(40);
		sendByte(0b00100100);
		sendByte(0b00100000);
		sendByte(0b10000100);
		sendByte(0b10000000);
		
		//Display off
		_delay_us(40);
		sendByte(0b00000100);
		sendByte(0b00000000);
		sendByte(0b10000100);
		sendByte(0b10000000);
		
		//Display clear cursor home
		_delay_us(40);
		sendByte(0b00000100);
		sendByte(0b00000000);
		sendByte(0b00010100);
		sendByte(0b00010000);
		
		//Set cursor direction
		_delay_us(40);
		sendByte(0b00000100);
		sendByte(0b00000000);
		sendByte(0b01100100);
		sendByte(0b01100000);
		
		//Turn on display
		_delay_us(40);
		sendByte(0b00001100);
		sendByte(0b00001000);
		sendByte(0b11101100);
		sendByte(0b11101000);
	}
	sendStopCondition();
}

/************************************************************************/
/* Sends a command as two nibbles to the LCD                            */
/************************************************************************/
void sendCommand(char command)
{
	sendStartCondition();
	sendByte(savedSlaveAddress);
	
	_delay_us(40);
	sendByte((0xF0 &command) | (0b00001100));
	sendByte((0xF0 &command) | (0b00001000));
	sendByte(((0x0F &command)<<4) | (0b00001100));
	sendByte(((0x0F &command)<<4) | (0b00001000));
	
	sendStopCondition();
}

/************************************************************************/
/* Sends a byte of data as two nibbles to the LCD                       */
/************************************************************************/
void sendData(char command)
{
	sendStartCondition();
	sendByte(savedSlaveAddress);
	
	_delay_us(40);
	sendByte((0xF0 &command) | (0b00001101));
	sendByte((0xF0 &command) | (0b00001001));
	sendByte(((0x0F &command)<<4) | (0b00001101));
	sendByte(((0x0F &command)<<4) | (0b00001001));
	
	sendStopCondition();
}

/************************************************************************/
/* Set the cursor at the specified location                             */
/* row: 0 for first line												*/
/*		1 for second line												*/
/* col: 0 for first char												*/
/*		15 for last char												*/
/************************************************************************/
void setCursor(char row, char col)
{
	sendCommand((0x80+col)+(0x40*row));
}

/************************************************************************/
/* Writes a given char on the LCD                                       */
/* The location can be specified with the setCursor() funtion			*/
/************************************************************************/
void writeChar(char character)
{
	sendData(character);
}

/************************************************************************/
/* Writes a given char* (String) on the LCD                             */
/* The start location can be specified with the setCursor() funtion 	*/
/************************************************************************/
void writeString(char* character)
{
	unsigned char i = 0;
	while(character[i] != '\0')
	{
		writeChar(character[i]);
		i++;
	}
}

/************************************************************************/
/* Clears the screen                                                    */
/************************************************************************/
void clearScreen()
{
	sendCommand(0x01);
	_delay_ms(2);
}