/*
 * Operations.h
 *
 *  Created on: Dec 21, 2024
 *      Author: HODA2
 */

#ifndef APP_OPERATIONS_H_
#define APP_OPERATIONS_H_

#include "Lcd.h"
#include "EEPROM.h"
#include "UART.h"
void Clock_Enable();
void HandleEEPROM();
void HandleTemperature(int temperature, const char temp[]);
void HandleEndProgram();
void HandlePassword();
int my_strcmp(const char *str1, const char *str2);
void HandleDTC();
char* my_strcpy(char *dest, const char *src);
void HandleUltraSonic(int *distance, const char *accident);
#define WARNING_DISTANCE 10

#endif /* APP_OPERATIONS_H_ */
