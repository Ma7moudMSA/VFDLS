/*
 * pushbuttons.c
 *
 */
#include "tm4c123gh6pm_registers.h"
#include "pushbuttons.h"


void PB1_Init(void)
{

    GPIO_PORTE_AMSEL_REG &= ~(1<<ROpen_pin);      /* Disable Analog on PE */

    GPIO_PORTE_PCTL_REG  &= 0xfffff0ff;

    GPIO_PORTE_DIR_REG   &= ~(1<<ROpen_pin);      /* Configure PE as input pin */
    GPIO_PORTE_AFSEL_REG &= ~(1<<ROpen_pin);      /* Disable alternative function on PE */
    GPIO_PORTE_PUR_REG   |= (1<<ROpen_pin);       /* Enable pull-up on PE */
    GPIO_PORTE_DEN_REG   |= (1<<ROpen_pin);       /* Enable Digital I/O on PE */

    GPIO_PORTE_IS_REG    &= ~(1<<ROpen_pin);      /* PE4 detect edges */
    GPIO_PORTE_IBE_REG   |= (1<<ROpen_pin);      /* PE4 will detect any edge */
    GPIO_PORTE_ICR_REG   |= (1<<ROpen_pin);       /* Clear Trigger flag for PE4 (Interrupt Flag) */
    GPIO_PORTE_IM_REG    |= (1<<ROpen_pin);       /* Enable Interrupt on PE4 pin */

        NVIC_PRI1_REG = (NVIC_PRI1_REG & GPIO_PORTE_PRIORITY_MASK) | (GPIO_PORTE_INTERRUPT_PRIORITY << GPIO_PORTE_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= 0x10;   /* Enable NVIC Interrupt for GPIO PORTE by setting bit number 4 in EN0 Register */
}


void PB2_Init(void)
{

    GPIO_PORTE_AMSEL_REG &= ~(1<<R_pin);      /* Disable Analog on PE */
    GPIO_PORTE_PCTL_REG  &= ~(0xF<<R_pin);

    GPIO_PORTE_DIR_REG   &= ~(1<<R_pin);      /* Configure PE as input pin */
    GPIO_PORTE_AFSEL_REG &= ~(1<<R_pin);      /* Disable alternative function on PE */
    GPIO_PORTE_PUR_REG   |= (1<<R_pin);       /* Enable pull-up on PE */
    GPIO_PORTE_DEN_REG   |= (1<<R_pin);       /* Enable Digital I/O on PE */

    GPIO_PORTE_IS_REG    &= ~(1<<R_pin);      /* PE4 detect edges */
    GPIO_PORTE_IBE_REG   |= (1<<R_pin);      /* PE4 will detect any edge */
    GPIO_PORTE_ICR_REG   |= (1<<R_pin);       /* Clear Trigger flag for PE4 (Interrupt Flag) */
    GPIO_PORTE_IM_REG    |= (1<<R_pin);       /* Enable Interrupt on PE4 pin */


    NVIC_PRI1_REG = (NVIC_PRI1_REG & GPIO_PORTE_PRIORITY_MASK) | (GPIO_PORTE_INTERRUPT_PRIORITY << GPIO_PORTE_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= 0x10;   /* Enable NVIC Interrupt for GPIO PORTE by setting bit number 4 in EN0 Register */
}


void PB3_Init(void)
{

    GPIO_PORTE_AMSEL_REG &= ~(1<<L_pin);      /* Disable Analog on PE */
    GPIO_PORTE_PCTL_REG  &= ~(0xF<<L_pin);

    GPIO_PORTE_DIR_REG   &= ~(1<<L_pin);      /* Configure PE as input pin */
    GPIO_PORTE_AFSEL_REG &= ~(1<<L_pin);      /* Disable alternative function on PE */
    GPIO_PORTE_PUR_REG   |= (1<<L_pin);       /* Enable pull-up on PE */
    GPIO_PORTE_DEN_REG   |= (1<<L_pin);       /* Enable Digital I/O on PE */
    GPIO_PORTE_IS_REG    &= ~(1<<L_pin);      /* PE4 detect edges */
    GPIO_PORTE_IBE_REG   |= (1<<L_pin);      /* PE4 will detect any edge */
    GPIO_PORTE_ICR_REG   |= (1<<L_pin);       /* Clear Trigger flag for PE4 (Interrupt Flag) */
    GPIO_PORTE_IM_REG    |= (1<<L_pin);       /* Enable Interrupt on PE4 pin */

    NVIC_PRI1_REG = (NVIC_PRI1_REG & GPIO_PORTE_PRIORITY_MASK) | (GPIO_PORTE_INTERRUPT_PRIORITY << GPIO_PORTE_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= 0x10;   /* Enable NVIC Interrupt for GPIO PORTE by setting bit number 4 in EN0 Register */
}


void PB4_Init(void)
{

    GPIO_PORTE_AMSEL_REG &= ~(1<<LClose_pin);      /* Disable Analog on PE */
    GPIO_PORTE_PCTL_REG  &= ~(0xF<<LClose_pin);
    GPIO_PORTE_DIR_REG   &= ~(1<<LClose_pin);      /* Configure PE as input pin */
    GPIO_PORTE_AFSEL_REG &= ~(1<<LClose_pin);      /* Disable alternative function on PE */
    GPIO_PORTE_PUR_REG   |= (1<<LClose_pin);       /* Enable pull-up on PE */
    GPIO_PORTE_DEN_REG   |= (1<<LClose_pin);       /* Enable Digital I/O on PE */
    GPIO_PORTE_IS_REG    &= ~(1<<LClose_pin);      /* PE4 detect edges */
    GPIO_PORTE_IBE_REG   |= (1<<LClose_pin);      /* PE4 will detect any edge */
    GPIO_PORTE_ICR_REG   |= (1<<LClose_pin);       /* Clear Trigger flag for PE4 (Interrupt Flag) */
    GPIO_PORTE_IM_REG    |= (1<<LClose_pin);       /* Enable Interrupt on PE4 pin */


    NVIC_PRI1_REG = (NVIC_PRI1_REG & GPIO_PORTE_PRIORITY_MASK) | (GPIO_PORTE_INTERRUPT_PRIORITY << GPIO_PORTE_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= 0x10;   /* Enable NVIC Interrupt for GPIO PORTE by setting bit number 4 in EN0 Register */
}

