/*
 * Systick.c
 *
 *  Created on: Dec 21, 2024
 */

#include "Systick.h"
#include "tm4c123gh6pm_registers.h"

//initialize the SysTick timer
void SysTick_Init(void)
{
    SYSTICK_CTRL_REG = 0;                // Disable SysTick timer
    SYSTICK_RELOAD_REG = 0xFFFFFF;       // Set reload value
    SYSTICK_CURRENT_REG = 0;             // Clear current value
    SYSTICK_CTRL_REG |= 0x04; // Use system clock (16 MHz) and start the SysTick Timer
}
