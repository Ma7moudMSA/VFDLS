/*
 * Operations.c
 *
 *  Created on: Dec 21, 2024
 */

#include <Operations.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "std_types.h"
#include "LM35.h"

//extern char sentenceArray[MAX_SENTENCES][MAX_SENTENCE_LENGTH + 1];

char* my_strcpy(char *dest, const char *src)
{
    char *original_dest = dest; // Save the original pointer to return later
    while ((*dest++ = *src++) != '\0')
        ; // Copy each character, including the null terminator
    return original_dest;
}

void HandleDTC()
{
    //unsigned char message_accident[MAX_SENTENCES][MAX_SENTENCE_LENGTH + 1];
    // readBufferFromEEPROM(0, 0);
    unsigned char message[50];
    //READ_DTC(message);
    EEPROM_Read(0, message, 14); // Read 14 bytes starting at address 0
    int i;
    for (i = 0; i < 50; i++)
    {
        //printf("Sentence %d: %s\n", i + 1, sentenceArray[i]);
        UART0_SendString(message[i]);
    }

    //readDTC(message_accident, 0x0, 0x0);

}

void Clock_Enable()
{
    // Enable EEPROM module clock
    SYSCTL_RCGCEEPROM_REG |= 1;
    while ((SYSCTL_RCGCEEPROM_REG & 1) == 0)
        ;

    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while (!(SYSCTL_PRGPIO_REG & 0x20))
        ;

    /* Enable clock for PORTB and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x02;
    while (!(SYSCTL_PRGPIO_REG & 0x02))
        ;

    /* Enable clock for PORTC and wait for clock to start */
    SET_BIT(SYSCTL_RCGCGPIO_REG, 2);
    while (!(GET_BIT(SYSCTL_PRGPIO_REG, 2)))
        ;

    /* Enable clock for PORTE and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x10;
    while (!(SYSCTL_PRGPIO_REG & 0x10))
        ;

}

void HandleEndProgram()
{
    const int size = 16; // Adjust the size as needed
    char blockArray[size];
    int i;
    for (i = 0; i < size; ++i)
    {
        blockArray[i] = 219;
    }
    UART0_DisableInterrupt();
    while (1)
    {

        //clear lcd
        LCD_clearScreen();
        LCD_moveCursor(1, 0);
        LCD_displayString(blockArray);
        LCD_moveCursor(0, 0);
        LCD_displayString(blockArray);
        LCD_displayStringRowColumn(0, 3, "Thank You!");
        LCD_displayStringRowColumn(1, 5, "Team 13");

        //Delay_MS(3000);
        LCD_Delay_Three_seconds();

        LCD_clearScreen();
        LCD_moveCursor(1, 0);
        LCD_displayString(blockArray);
        LCD_moveCursor(0, 0);
        LCD_displayString(blockArray);
        LCD_displayStringRowColumn(0, 1, "Start program");
        LCD_displayStringRowColumn(1, 5, "AGAIN!!");
        LCD_Delay_Three_seconds();

        /* LCD_moveCursor(0, 5);
         LCD_displayCharacter(' ');
         LCD_displayCharacter(' ');
         LCD_displayCharacter(' ');
         LCD_moveCursor(0, 14);
         LCD_displayCharacter(' ');
         LCD_displayCharacter(' ');*/
        // GPIO_PORTF_DATA_REG &= ~(1 << 3);
    }
}

void HandleEEPROM()
{

    unsigned char message_accident[5];
    readDTC(message_accident, 0x0, 0x0);
    UART0_SendString(message_accident);

    unsigned char message_temperatue[5];
    readDTC(message_temperatue, 0x0, 0x7);
    UART0_SendString(message_temperatue);
}

void HandleTemperature(int temperature, const char temp[])
{
    temperature = LM35_getTemperature();
    LCD_moveCursor(0, 5);
    LCD_intgerToString(temperature);
    LCD_displayCharacter(' ');
    if (temperature > 90)
    {
        writeDTC(temp, 0x0, 0x7);
    }
    else
    {
        deleteDTC(0x0, 0x7);
    }
}
int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}
char isPassCorrect = FALSE;
void HandlePassword()
{
    UART0_DisableInterrupt();

    while (!isPassCorrect)
    {
        LCD_clearScreen();
        LCD_displayStringRowColumn(1, 0, "ENTER YOUR PASS");

        unsigned char message[6]; // Increased size for null terminator
        int charCount = 0;

        while (charCount < 5)
        {
            unsigned char receivedChar = UART0_ReceiveByte(); // Receive one char
            if (receivedChar != '\0')
            { // Check if a character was received
                message[charCount] = receivedChar;
                LCD_moveCursor(0, charCount);
                charCount++;
                LCD_displayCharacter(receivedChar); // Echo the received char on LCD
            }
        }

        message[5] = '\0'; // Null-terminate the string (essential!)
        //UART0_SendString(message);
        int temp = my_strcmp(message, "micro");
        if (temp == 0)
            break;
        LCD_displayStringRowColumn(2, 0, "Sent: ");
        LCD_displayString(message); // Display what was sent

        //Optional: Clear the LCD for the next input
        LCD_displayStringRowColumn(1, 0, "                    "); //Clear line 1
        LCD_displayStringRowColumn(2, 0, "                    "); //Clear line 2
    }
    isPassCorrect = TRUE;
    UART0_EnableInterrupt();

}

/**************************************************************************/
/************                              ultrasonic              ********/
/************                                                      ********/
/**************************************************************************/
/**************************************************************************/
// GPIO PORTF External Interrupt - ISR
//ultrasonic sensor echo pin
/* Global Variables  */
//volatile uint32 t1 = 0;
volatile uint32 t2 = 0;
volatile uint8 GPIOPORTF_Counter = 0;
volatile char operation = 0;
static const double FREQUENCY = 16000000.0;
static const int TEN_MICROSECONDS = 10;
void GPIOPortF_Handler(void)
{
    GPIOPORTF_Counter++;
    if (GPIOPORTF_Counter == 1)
    {
        GPIO_PORTF_ICR_REG |= (1 << 4); // Clear Trigger flag for PF4 (Interrupt Flag)
        GPIO_PORTF_IEV_REG &= ~(1 << 4);      //PF4 will detect a falling edge
        SYSTICK_CTRL_REG |= 0x01;
    }

    else if (GPIOPORTF_Counter == 2)
    {
        GPIO_PORTF_ICR_REG |= (1 << 4); // Clear Trigger flag for PF4 (Interrupt Flag)
        GPIO_PORTF_IEV_REG |= (1 << 4); /* PF4 will detect a Rising edge */
        t2 = SYSTICK_CURRENT_REG;
    }
    GPIO_PORTF_ICR_REG |= (1 << 4); // Clear Trigger flag for PF4 (Interrupt Flag)
}

void HandleUltraSonic(int *distance, const char *accident)
{
    int Local_EchoTicks_timer = 0;
    float Local_echos_inseconds = 0;

    Local_EchoTicks_timer = 0xFFFFFF - t2; // Calculate time in ticks
    Local_echos_inseconds = (float) (Local_EchoTicks_timer / FREQUENCY); // Convert ticks to seconds
    *distance = (int) ((Local_echos_inseconds * 34000) / 2); // Distance in cm (divide by 2 for round trip)

    LCD_moveCursor(0, 14);
    LCD_intgerToString(*distance);
    LCD_displayCharacter(' ');
    if (*distance <= WARNING_DISTANCE) // If distance is bigger than X cm, turn on the LED
    {
        GPIO_PORTF_DATA_REG |= (1 << 3);
        //writeDTC(accident, 0x0, 0x0);
        WriteDTC_2(accident);
    }
    else
    {
        GPIO_PORTF_DATA_REG &= ~(1 << 3);
        LCD_moveCursor(0, 14);

    }

    GPIO_PORTF_DATA_REG |= (1 << 2);
    GPIOPORTF_Counter = 0;
    SYSTICK_CTRL_REG &= ~(1 << 0);
    SYSTICK_CURRENT_REG = 0; // Clear current value
}
