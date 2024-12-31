/*
 * ultrasonic.c
 *
 */

#include "tm4c123gh6pm_registers.h"
#include "ultrasonic.h"



#define Trigger_Pin 1

#define Echo_Pin 4

void Delay_US(unsigned long long n)
{
    volatile unsigned long long count = 0;
    unsigned long long scaled_n = ((n * NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND)/1000); // Scale by 364 iterations for 1 millisecond
    while (count++ < (scaled_n));  // Divide by 1000 for microseconds
}


static void  Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}





void TriggerPin_init (void)
{
    GPIO_PORTF_AMSEL_REG &= ~(1 << Trigger_Pin);   // Disable Analog on PF1
    GPIO_PORTF_PCTL_REG &= ~(0xF<<Trigger_Pin);  //0xFFFFFF0F;    Clear PMCx bits for PF1
    GPIO_PORTF_DIR_REG |= (1 << Trigger_Pin);      // Configure PF1 as output
    GPIO_PORTF_AFSEL_REG &= ~(1 << Trigger_Pin);   // Disable alternative function
    GPIO_PORTF_PUR_REG &= ~(1 << Trigger_Pin);     // Disable pull-up
    GPIO_PORTF_DEN_REG |= (1 << Trigger_Pin);      // Enable digital I/O
    GPIO_PORTF_DATA_REG &= ~(1 << Trigger_Pin);    // Set low initially
}


/* Enable PF4 switch and activate external interrupt with falling edge */
void EchoPin_init(void)
{
    GPIO_PORTF_AMSEL_REG &= ~(1<<Echo_Pin);      /* Disable Analog on PF4 */
    GPIO_PORTF_PCTL_REG  &= ~(0xF<<Echo_Pin);  //0xFFF0FFFF;   /* Clear PMCx bits for PF4 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   &= ~(1<<Echo_Pin);      /* Configure PF4 as input pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<Echo_Pin);      /* Disable alternative function on PF4 */
    GPIO_PORTF_DEN_REG   |= (1<<Echo_Pin);       /* Enable Digital I/O on PF4 */

    GPIO_PORTF_IS_REG    &= ~(1<<Echo_Pin);      /* PF4 detect edges */
    GPIO_PORTF_IBE_REG   &= ~(1<<Echo_Pin);      /* PF4 will detect a certain edge */
    GPIO_PORTF_IEV_REG   |= (1<<Echo_Pin);      /* PF4 will detect a Rising edge */
    GPIO_PORTF_ICR_REG   |= (1<<Echo_Pin);       /* Clear Trigger flag for PF4 (Interrupt Flag) */
    GPIO_PORTF_IM_REG    |= (1<<Echo_Pin);       /* Enable Interrupt on PF4 pin */

    /* Set GPIO PORTF priority as 2 by set Bit number 21, 22 and 23 with value 2 */
    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS);
    NVIC_EN0_REG         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */

}

