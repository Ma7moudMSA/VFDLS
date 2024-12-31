/*
 * Lcd.c
 */
#include "common_macros.h"
#include "Lcd.h"
#include <stdio.h>
#include <tm4c123gh6pm_registers.h>

void LCD_Delay_Three_seconds()
{
    Delay_MS(3000);
}

void LCD_Welcome_Screen()
{
    LCD_displayString("Welcome :)");
    LCD_displayStringRowColumn(1, 0, "Ready to receive:");
}

void LCD_Display()
{
    LCD_displayString("TEMP:");
    LCD_displayStringRowColumn(0, 9, "DIST:");
    LCD_displayStringRowColumn(1, 0, "CW:");
}

void my_itoa(int num, char *str, int base)
{
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers for base 10
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    // Process the digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num /= base;
    }

    // Add the negative sign if necessary
    if (isNegative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';
    int j, k;
    for (j = 0, k = i - 1; j < k; ++j, --k)
    {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void LCD_init(void)
{
    // CONFIGURE RS pin as output
    GPIO_PORTA_AMSEL_REG &= ~(1 << 6); /* Disable Analog on PA6 */
    GPIO_PORTA_PCTL_REG &= 0xF0FFFFFF; /* Clear PMCx bits for PA6 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 6); /* Configure PA6 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 6); /* Disable alternative function on PA6 */
    GPIO_PORTA_DEN_REG |= (1 << 6); /* Enable Digital I/O on PA6 */
    GPIO_PORTA_DATA_REG &= ~(1 << 6); /* CLEAR BIT 6 PORTA*/

    /*CONFIGURE E pin as output*/
    GPIO_PORTA_AMSEL_REG &= ~(1 << 7); /* Disable Analog on PA7 */
    GPIO_PORTA_PCTL_REG &= 0x0FFFFFFF; /* Clear PMCx bits for PA7 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 7); /* Configure PA7 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 7); /* Disable alternative function on PA7 */
    GPIO_PORTA_DEN_REG |= (1 << 7); /* Enable Digital I/O on PA7 */
    GPIO_PORTA_DATA_REG &= ~(1 << 7);     // CLEAR BIT 7 PORTA

    Delay_MS(20);



    //Configure PA2---D4
    GPIO_PORTA_AMSEL_REG &= ~(1 << 2); /* Disable Analog on PA2 */
    GPIO_PORTA_PCTL_REG &= 0xFFFFF0FF; /* Clear PMCx bits for PA2 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 2); /* Configure PA2 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 2); /* Disable alternative function on PA2 */
    GPIO_PORTA_DEN_REG |= (1 << 2); /* Enable Digital I/O on PA2 */
    GPIO_PORTA_DATA_REG &= ~(1 << 2);     // CLEAR BIT 2 PORTA

    //Configure PA3---D5
    GPIO_PORTA_AMSEL_REG &= ~(1 << 3); /* Disable Analog on PA3 */
    GPIO_PORTA_PCTL_REG &= 0xFFFF0FFF; /* Clear PMCx bits for PA3 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 3); /* Configure PA3 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 3); /* Disable alternative function on PA3 */
    GPIO_PORTA_DEN_REG |= (1 << 3); /* Enable Digital I/O on PA3 */
    GPIO_PORTA_DATA_REG &= ~(1 << 3);     // CLEAR BIT 3 PORTA

    //Configure PA4---D6
    GPIO_PORTA_AMSEL_REG &= ~(1 << 4); /* Disable Analog on PA4 */
    GPIO_PORTA_PCTL_REG &= 0xFFF0FFFF; /* Clear PMCx bits for PA4 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 4); /* Configure PA4 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 4); /* Disable alternative function on PA4 */
    GPIO_PORTA_DEN_REG |= (1 << 4); /* Enable Digital I/O on PA4 */
    GPIO_PORTA_DATA_REG &= ~(1 << 4);     // CLEAR BIT 4 PORTA

    //Configure PA5---D7
    GPIO_PORTA_AMSEL_REG &= ~(1 << 5); /* Disable Analog on PA5 */
    GPIO_PORTA_PCTL_REG &= 0xFF0FFFFF; /* Clear PMCx bits for PA5 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG |= (1 << 5); /* Configure PA5 as Output pin */
    GPIO_PORTA_AFSEL_REG &= ~(1 << 5); /* Disable alternative function on PA5 */
    GPIO_PORTA_DEN_REG |= (1 << 5); /* Enable Digital I/O on PA5 */
    GPIO_PORTA_DATA_REG &= ~(1 << 5);     // CLEAR BIT 5 PORTA

    /* Send for 4 bit initialization of LCD  */
    LCD_sendCommand(0x33);
    LCD_sendCommand(0x32);

    /* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
    LCD_sendCommand(0x28);

    LCD_sendCommand(0x0C); /* cursor off */
    LCD_sendCommand(0x01); /* clear LCD at the beginning */
}

void static Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while (count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n))
        ;
}

void LCD_sendCommand(char command)
{
    CLEAR_BIT(GPIO_PORTA_DATA_REG, RS_PIN); /* Instruction Mode RS=0 */
    Delay_MS(1); /* delay for processing Tas = 50ns */
    SET_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Enable LCD E=1 */
    Delay_MS(1);

    GPIO_PORTA_DATA_REG = ((GPIO_PORTA_DATA_REG & 0xc3)
            | ((command & 0xF0) >> 2));

    Delay_MS(1); /* delay for processing Tdsw = 100ns */
    CLEAR_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Disable LCD E=0 */
    Delay_MS(1); /* delay for processing Th = 13ns */
    SET_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Enable LCD E=1 */
    Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */

    GPIO_PORTA_DATA_REG = ((GPIO_PORTA_DATA_REG & 0xc3)
            | ((command & 0x0F) << 2));

    Delay_MS(1); /* delay for processing Tdsw = 100ns */
    CLEAR_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Disable LCD E=0 */
    Delay_MS(1);

}


void LCD_displayCharacter(char data)
{
    SET_BIT(GPIO_PORTA_DATA_REG, RS_PIN); /* Data Mode RS=1 */
    Delay_MS(1); /* delay for processing T as = 50ns */
    SET_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Enable LCD E=1 */
    Delay_MS(1);

    GPIO_PORTA_DATA_REG = ((GPIO_PORTA_DATA_REG & 0xc3) | ((data & 0xF0) >> 2));

    Delay_MS(1); /* delay for processing T dsw = 100ns */
    CLEAR_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Disable LCD E=0 */
    Delay_MS(1);
    SET_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Enable LCD E=1 */
    Delay_MS(1);

    GPIO_PORTA_DATA_REG = ((GPIO_PORTA_DATA_REG & 0xc3) | ((data & 0x0F) << 2));

    Delay_MS(1); /* delay for processing Tdsw = 100ns */
    CLEAR_BIT(GPIO_PORTA_DATA_REG, E_PIN); /* Disable LCD E=0 */
    Delay_MS(1);
}

void LCD_displayString(const char *Str)
{
    char i = 0;
    while (Str[i] != '\0')
    {
        LCD_displayCharacter(Str[i]);
        i++;
    }

}


void LCD_moveCursor(char row, char col)
{
    char lcd_memory_address;

    /* Calculate the required address in the LCD DDRAM */
    switch (row)
    {
    case 0:
        lcd_memory_address = col;
        break;
    case 1:
        lcd_memory_address = col + 0x40;
        break;
    case 2:
        lcd_memory_address = col + 0x10;
        break;
    case 3:
        lcd_memory_address = col + 0x50;
        break;
    }
    /* Move the LCD cursor to this specific address */
    LCD_sendCommand(lcd_memory_address | 0x80);
}

void LCD_displayStringRowColumn(char row, char col, const char *Str)
{
    LCD_moveCursor(row, col); /* go to to the required LCD position */
    LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
    char buff[16]; /* String to hold the ascii result */
    my_itoa(data, buff, 10); /* Use my_itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
    LCD_displayString(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
    LCD_sendCommand(0x01); /* Send clear display command */
}

