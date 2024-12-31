/*
 * ADC.c
 *

 */
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "ADC.h"

// ADC initialization function
void ADC_Init(unsigned char channel)
{
    // Enable clock for ADC0 and GPIO ports
    SYSCTL_RCGCADC_REG |= 0x01;          // Enable ADC0 clock

    // Wait for the peripheral to be ready
    while ((SYSCTL_PRADC_REG & 0x01) == 0);

    // Configure GPIO pins for analog mode
    GPIO_PORTE_AFSEL_REG |= (1 << channel);  // Enable alternate function for the selected pin
    GPIO_PORTE_DEN_REG &= ~(1 << channel);   // Disable digital function for the pin
    GPIO_PORTE_AMSEL_REG |= (1 << channel);  // Enable analog function for the pin

    // Configure ADC0
    ADC0_ACTSS_REG &= ~0x08;               // Disable sample sequencer 3 during configuration
    ADC0_EMUX_REG = (ADC0_EMUX_REG & ~0xF000) | 0x0000;  // Software trigger for sequencer 3
    ADC0_SSMUX3_REG = channel;             // Set input channel for sequencer 3
    ADC0_SSCTL3_REG = 0x06;                // Configure sample sequencer 3: single-ended, one sample, end of sequence
    ADC0_ACTSS_REG |= 0x08;                // Enable sample sequencer 3
}

// ADC read function
unsigned short ADC_ReadChannel(void)
{
    ADC0_PSSI_REG = 0x08;                  // Start a conversion on sequencer 3
    while ((ADC0_RIS_REG & 0x08) == 0);    // Wait for conversion to complete
    unsigned short result = ADC0_SSFIFO3_REG & 0xFFF;  // Read 12-bit result from FIFO
    ADC0_ISC_REG = 0x08;                   // Clear completion flag
    return result;
}



