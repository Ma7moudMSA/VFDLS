/*
 * Windows.c
 *
 *  Created on: Dec 21, 2024
 */

#include <Windows.h>
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "Lcd.h"
#include "GPTimers.h"

/* Global variables */
volatile int flag_window = 0; // Indicates the current window operation
short Windows_Capacity_1 = 0;  // Capacity level of the right window
short Windows_Capacity_2 = 0; // Capacity level of the left window
extern short Seconds_Timer_1; // Timer for right window motor operation
extern short Seconds_Timer_2; // Timer for left window motor operation
char Enable_timer_M1 = 0; // Enable flag for right window motor timer
char Enable_timer_M2 = 0;  // Enable flag for left window motor timer
char Motor_1_on_flag = 0;  // Indicates if the right window motor is active
char Motor_2_on_flag = 0;  // Indicates if the left window motor is active

/*
 * Function to initialize motor control pins (PB2, PB3, PB6, PB7) as output.
 */
void Motor_Init(void)
{
    // Enable clock for GPIO Port B
    SYSCTL_RCGCGPIO_REG |= (1 << 1); // Port B is bit 1 in SYSCTL_RCGCGPIO_R
    while ((SYSCTL_PRGPIO_REG & (1 << 1)) == 0)
        ; // Wait for Port B to be ready

    // Disable analog functionality on PB2, PB3, PB4, PB7
    GPIO_PORTB_AMSEL_REG &= ~((1 << 2) | (1 << 3) | (1 << 6) | (1 << 7));

    // Configure PB2, PB3, PB4, PB7 as GPIO (clear alternate functions)
    GPIO_PORTB_PCTL_REG &= ~((0xF << (2 * 4)) | (0xF << (3 * 6))
            | (0xF << (4 * 4)) | (0xF << (7 * 4)));

    // Set PB2, PB3, PB4, PB7 as output
    GPIO_PORTB_DIR_REG |= ((1 << 2) | (1 << 3) | (1 << 6) | (1 << 7));

    // Enable digital functionality on PB2, PB3, PB4, PB7
    GPIO_PORTB_DEN_REG |= ((1 << 2) | (1 << 3) | (1 << 6) | (1 << 7));

    // Initialize all pins to LOW (optional)
    GPIO_PORTB_DATA_REG &= ~((1 << 2) | (1 << 3) | (1 << 6) | (1 << 7));
}

void GPIOPortE_Handler(void)
{

    /*
     * GPIO interrupt handler for Port E to detect window control button presses.
     */
    if (GET_BIT(GPIO_PORTE_DATA_REG,2) == 0)
    {
        flag_window = CLOCKWISE_M1; // Open right window
    }
    else if (GET_BIT(GPIO_PORTE_DATA_REG,1) == 0)
    {
        flag_window = ANTICLOCKWISE_M1; // Close right window
    }
    else if (GET_BIT(GPIO_PORTE_DATA_REG,4) == 0)
    {
        flag_window = ANTICLOCKWISE_M2; // Close left window
    }
    else if (GET_BIT(GPIO_PORTE_DATA_REG,5) == 0)
    {
        flag_window = CLOCKWISE_M2; // Open left window
    }
    else if (GET_BIT(
            GPIO_PORTE_DATA_REG,
            2) || GET_BIT(GPIO_PORTE_DATA_REG,1) || GET_BIT(GPIO_PORTE_DATA_REG,4) || GET_BIT(GPIO_PORTE_DATA_REG,5))
    {
        flag_window = 0; // Stop all operations
    }

    // Clear interrupt flags for PE1, PE2, PE4, PE5
    GPIO_PORTE_ICR_REG |= 0b00110110;  //clear flag

}
/*
 * Function to turn on a motor by enabling one pin and disabling another.
 * Parameters:
 * pin1 - The pin to set HIGH
 * pin2 - The pin to set LOW
 */
void Motor_ON(int pin1, int pin2)
{
    GPIO_PORTB_DATA_REG |= (1 << pin1);
    GPIO_PORTB_DATA_REG &= ~(1 << pin2);
}
/* Enum to define window capacity levels and enable timer*/
typedef enum
{
    EMPTY = 0, // Window fully closed
    ENABLETIME = 20, // Time required for full operation
    FULL = 40 // Window fully open
} CapacityLevel;
/*
 * Function to display the window capacity on the LCD.
 * Parameters:
 * Windows_Capacity_1 - Current capacity level of the window
 * sign - Character to represent the capacity level (e.g., '=')
 * RightorLeft - Indicates whether to display for the right or left window
 */
void DisplayWindowsCapacity(short Windows_Capacity_1, char sign,
                            short RightorLeft)
{
    int var;
    if (RightorLeft == RIGHT)
    {
        LCD_displayStringRowColumn(1, 3, "R [");
        LCD_displayStringRowColumn(1, 15, "]");
        LCD_moveCursor(1, 6);
        for (var = 0; var < (Windows_Capacity_1 / 4) - 1; ++var)
        {
            LCD_displayCharacter(sign);
        }
    }
    else if (RightorLeft == LEFT)
    {
        LCD_displayStringRowColumn(1, 3, "L [");
        LCD_displayStringRowColumn(1, 15, "]");
        LCD_moveCursor(1, 6);
        for (var = 0; var < (Windows_Capacity_1 / 4) - 1; ++var)
        {
            LCD_displayCharacter(sign);
        }

    }

}
/*
 * Function to handle window operations based on the current flag.
 * Parameters:
 * flag_window - Indicates the current operation to perform
 */
void HandleWindow(volatile int flag_window)
{
    char sign = '=';
    switch (flag_window)
    {
    //open right window
    case CLOCKWISE_M1:
        if (Windows_Capacity_1 <= FULL)
        {
            Motor_ON(2, 3);
            Windows_Capacity_1++;
        }
        else if (Windows_Capacity_1 > FULL)
        {
            Windows_Capacity_1 = FULL;
        }
        DisplayWindowsCapacity(Windows_Capacity_1, sign, RIGHT);
        Enable_timer_M1++;
        if (Enable_timer_M1 == ENABLETIME)
        {
            Motor_1_on_flag = TRUE;
            Seconds_Timer_1 = 0;
            Enable_timer_M1 = 0;
            Windows_Capacity_1 = FULL;

        }
        break;
        //close RIGHT window
    case ANTICLOCKWISE_M1:
        if (Windows_Capacity_1 > EMPTY)
        {
            Windows_Capacity_1--;
            Motor_ON(3, 2);
        }
        else if (Windows_Capacity_1 < EMPTY)
            Windows_Capacity_1 = EMPTY;
        //LCD_displayStringRowColumn(1, 6, "R CLOSING");
        DisplayWindowsCapacity(Windows_Capacity_1, sign, RIGHT);
        Enable_timer_M1++;
        if (Enable_timer_M1 == ENABLETIME)
        {
            Motor_1_on_flag = TRUE;
            Seconds_Timer_1 = 0;
            Enable_timer_M1 = 0;
            Windows_Capacity_1 = EMPTY;

        }
        break;
        //open left window
    case CLOCKWISE_M2:
        if (Windows_Capacity_2 < FULL)
        {
            Motor_ON(6, 7);
            Windows_Capacity_2++;
        }
        else if (Windows_Capacity_2 > FULL)
        {
            Windows_Capacity_2 = FULL;
        }

        DisplayWindowsCapacity(Windows_Capacity_2, sign, LEFT);
        Enable_timer_M2++;
        if (Enable_timer_M2 == ENABLETIME)
        {
            Motor_2_on_flag = 1;
            Seconds_Timer_2 = 0;
            Enable_timer_M2 = 0;
            Windows_Capacity_2 = FULL;
        }
        break;
    case ANTICLOCKWISE_M2: // Close left window
        if (Windows_Capacity_2 > EMPTY)
        {
            Motor_ON(7, 6);
            Windows_Capacity_2--;
        }
        else if (Windows_Capacity_2 < EMPTY)
        {
            Windows_Capacity_2 = EMPTY;
        }
        DisplayWindowsCapacity(Windows_Capacity_2, sign, LEFT);
        Enable_timer_M2++;
        if (Enable_timer_M2 == ENABLETIME)
        {
            Motor_2_on_flag = TRUE;
            Seconds_Timer_2 = 0;
            Enable_timer_M2 = 0;
            Windows_Capacity_2 = EMPTY;

        }
        break;
        //stop all motors
    case 0:

        if (Motor_1_on_flag == 0)
        {
            GPIO_PORTB_DATA_REG &= ~(1 << 2);
            GPIO_PORTB_DATA_REG &= ~(1 << 3);
            Enable_timer_M1 = 0;

        }
        if (Motor_2_on_flag == 0)
        {
            GPIO_PORTB_DATA_REG &= ~(1 << 6);
            GPIO_PORTB_DATA_REG &= ~(1 << 7);
            Enable_timer_M2 = 0;
        }
        LCD_moveCursor(1, 3);
        LCD_displayString("             ");
        break;
    case 5:
        break;
    }
}

/*
 * Timer1A interrupt handler to manage motor operation timing.
 */
void Timer1A_Handler(void)
{
    // Check if the interrupt is from Timer1A
    if (TIMER1_MIS_R & TIMER_MIS_TAMIS)
    {
        TIMER1_ICR_R = TIMER_ICR_TATOCINT; // Clear the interrupt flag
        // GPIO_PORTF_DATA_REG ^= 0x02;         // Toggle PF1 (LED)

        Seconds_Timer_1++;
        Seconds_Timer_2++;
        if (Motor_1_on_flag == 1 && Seconds_Timer_1 > 6)
        {
            Motor_1_on_flag = 0; // Stop right window motor after 6 seconds
        }
        if (Motor_2_on_flag == 1 && Seconds_Timer_2 > 6)
        {
            Motor_2_on_flag = 0; // Stop left window motor after 6 seconds
        }

    }
}
