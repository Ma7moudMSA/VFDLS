/*
 * main.h
 *
 *  Created on: Dec 21, 2024
 *      Author: HODA2
 */

#ifndef APP_APP_H_
#define APP_APP_H_


#include <LEDs.h>
#include "LM35.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "std_types.h"
#include "EEPROM.h"
#include "ultrasonic.h"
#include "UART.h"
#include "pushbuttons.h"
#include "Lcd.h"
#include "ADC.h"
#include "Systick.h"
#include "GPTimers.h"


/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

//#define TRUE    1
//#define FALSE   0
#define CHANNEL_ZERO   0

void InIt(void);
void HandleEndProgram();





static const char RUNNING = '1';
static const char END_PROGRAM = '3';
static const char PRINT_MESSAGE = '2';






#endif /* APP_APP_H_ */
