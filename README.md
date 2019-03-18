# I²C-LCD1602-Library

## Overview
This I2C-LCD1602-Library is an education project.  
The I2C_LCD_LIB is written for Atmel ATmega328P and developed with Atmel Studio 7.0 IDE.   

**You can use it at your own risk.**

**[Download Library [latest version]](https://github.com/schaeferservices/I2C_LCD_LIB/releases)**  

> **Important**  
> The [I²C-Library](#used-libraries) must be connected/enclosed!

## Properties

- initialize the LCD with slave address
- set cursor to row and column
- write string on LCD
- write single char on LCD
- clear screen

## Usage
### initalize LCD1602
```c
void initLCD(char slaveAddress);
```

### set cursor to row (0 - 1) and column (0 - 15)
```c
void setCursor(char row, char col);
```

### write string on LCD1602 at cursor position
```c
void writeString(char* character);
```

### write char on LCD1602 at cursor position
```c
void writeChar(char character);
```

### clear screen of LCD1602
```c
void clearScreen();
```

## Used Libraries
- [I2C_LIB [v1.0]](https://github.com/schaeferservices/I2C_LIB)

## Used Literature
- [Datasheet LCD1602](https://cdn-shop.adafruit.com/datasheets/TC1602A-01T.pdf)
- [Datasheet NXP PCF8574x](https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf)
- [Datasheet Atmel ATmega328P](https://cdn-shop.adafruit.com/datasheets/ATMEGA328P.pdf)
