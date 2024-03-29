﻿/*
 * I2C_LIB.h
 *
 * Created: 14.02.2019 16:19:06
 * Author:  Daniel Schäfer
 * Contact: code@schaeferservices.de
 */

#ifndef I2C_LIB_H_
#define I2C_LIB_H_

typedef enum{FALSE, TRUE} boolean;

/************************************************************************/
/* prototypes of I2C-functions                                          */
/************************************************************************/
void initI2C(double, char);
void sendStartCondition();
void sendStopCondition();
boolean sendByte(char);
char readSlave(char);
char readRegister(char, char);

#endif /* I2C_LIB_H_ */