/*
 * Windows.h
 *
 *  Created on: Dec 21, 2024
 */

#ifndef APP_WINDOWS_H_
#define APP_WINDOWS_H_

void GPIOPortE_Handler(void);
void HandleWindow(volatile int flag_window);
void Motor_Init(void);

#define CLOCKWISE_M1        1
#define ANTICLOCKWISE_M1    2
#define CLOCKWISE_M2        4
#define ANTICLOCKWISE_M2    3
#define RIGHT               1
#define LEFT                2
//#define FULL                20
//#define EMPTY               0
#define MAX_STRING_LENGTH   10

void Timer1A_Handler(void);

#endif /* APP_WINDOWS_H_ */
