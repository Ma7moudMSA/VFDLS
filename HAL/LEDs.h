/*
 * LEDS.h
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "tm4c123gh6pm_registers.h"

#define RED_LED    1     /* PF1*/
#define BLUE_LED   2     /* PF2*/
#define GREEN_LED  3     /* PF3*/


#define GPIO_RED_LED_MASK   0XFFFFFF0F
#define GPIO_BLUE_LED_MASK  0XFFFFF0FF
#define GPIO_GREEN_LED_MASK 0XFFFF0FFF

void LED_Red_Init  (void); /*PF1*/
void LED_Blue_Init (void); /*/F2*/
void LED_Green_Init(void); /*PF3*/

void PortB_Pin0_Init(void);
void PortB_Pin1_Init(void);
void PortB_Pin2_Init(void);
void PortB_Pin3_Init(void);

#endif /* LEDS_H_ */
