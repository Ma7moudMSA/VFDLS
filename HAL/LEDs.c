/*
 * LEDS.c
 */

#include <LEDs.h>

/*
 * PF1
 *
 * */
void LED_Red_Init(void)
{

    GPIO_PORTF_DIR_REG |= (1 << RED_LED); /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1 << RED_LED); /* Disable alternative function on PF1 */
    GPIO_PORTF_AMSEL_REG &= ~(1 << RED_LED); /* Disable Analog on PF1 */
    GPIO_PORTF_DEN_REG |= (1 << RED_LED); /* Enable Digital I/O on PF1 */
    GPIO_PORTF_PCTL_REG &= GPIO_RED_LED_MASK; /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTF_DATA_REG &= ~(1 << RED_LED); /* Clear bit 1 in Data register to turn off the led */
}

/*
 * PF2
 * */
void LED_Blue_Init(void)
{

    GPIO_PORTF_DIR_REG |= (1 << BLUE_LED); /* Configure PF2 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1 << BLUE_LED); /* Disable alternative function on PF2 */
    GPIO_PORTF_AMSEL_REG &= ~(1 << BLUE_LED); /* Disable Analog on PF2 */
    GPIO_PORTF_DEN_REG |= (1 << BLUE_LED); /* Enable Digital I/O on PF2 */
    GPIO_PORTF_PCTL_REG &= GPIO_BLUE_LED_MASK; /* Clear PMCx bits for PF2 to use it as GPIO pin */
    GPIO_PORTF_DATA_REG &= ~(1 << BLUE_LED); /* Clear bit 2 in Data register to turn off the led */
}

/*PF3*/
void LED_Green_Init(void)
{

    GPIO_PORTF_DIR_REG |= (1 << GREEN_LED); /* Configure PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1 << GREEN_LED); /* Disable alternative function on PF3 */
    GPIO_PORTF_AMSEL_REG &= ~(1 << GREEN_LED); /* Disable Analog on PF3 */
    GPIO_PORTF_DEN_REG |= (1 << GREEN_LED); /* Enable Digital I/O on PF3 */
    GPIO_PORTF_PCTL_REG &= GPIO_GREEN_LED_MASK; /* Clear PMCx bits for PF3 to use it as GPIO pin */
    GPIO_PORTF_DATA_REG &= ~(1 << GREEN_LED); /* Clear bit 3 in Data register to turn off the led */

}

void PortB_Pin0_Init(void)
{

    GPIO_PORTB_DIR_REG |= (1 << 0); /* Configure PB0 as an output pin */
    GPIO_PORTB_AFSEL_REG &= ~(1 << 0); /* Disable alternative function on PB0 */
    GPIO_PORTB_AMSEL_REG &= ~(1 << 0); /* Disable Analog on PB0 */
    GPIO_PORTB_DEN_REG |= (1 << 0); /* Enable Digital I/O on PB0 */
    GPIO_PORTB_PCTL_REG &= ~(0x0000000F); /* Clear PMCx bits for PB0 to use it as a GPIO pin */
    GPIO_PORTB_DATA_REG &= ~(1 << 0); /* Clear bit 0 in Data register */

}

void PortB_Pin1_Init(void)
{
    GPIO_PORTB_DIR_REG |= (1 << 1); /* Configure PB1 as an output pin */
    GPIO_PORTB_AFSEL_REG &= ~(1 << 1); /* Disable alternative function on PB1 */
    GPIO_PORTB_AMSEL_REG &= ~(1 << 1); /* Disable Analog on PB1 */
    GPIO_PORTB_DEN_REG |= (1 << 1); /* Enable Digital I/O on PB1 */
    GPIO_PORTB_PCTL_REG &= ~(0x000000F0); /* Clear PMCx bits for PB1 to use it as a GPIO pin */
    GPIO_PORTB_DATA_REG &= ~(1 << 1); /* Clear bit 1 in Data register */

}

void PortB_Pin2_Init(void)
{
    GPIO_PORTB_DIR_REG |= (1 << 2);     /* Configure PB2 as an output pin */
    GPIO_PORTB_AFSEL_REG &= ~(1 << 2);     /* Disable alternative function on PB2 */
    GPIO_PORTB_AMSEL_REG &= ~(1 << 2);    /* Disable Analog on PB2 */
    GPIO_PORTB_DEN_REG |= (1 << 2);    /* Enable Digital I/O on PB2 */
    GPIO_PORTB_PCTL_REG &= ~(0x000000F0);    /* Clear PMCx bits for PB2 to use it as a GPIO pin */
    GPIO_PORTB_DATA_REG &= ~(1 << 2);    /* Clear bit 2 in Data register  */

}

void PortB_Pin3_Init(void)
{
    /* Configure PB3 as an output pin */
    GPIO_PORTB_DIR_REG |= (1 << 3);
    /* Disable alternative function on PB3 */
    GPIO_PORTB_AFSEL_REG &= ~(1 << 3);
    /* Disable Analog on PB3 */
    GPIO_PORTB_AMSEL_REG &= ~(1 << 3);
    /* Enable Digital I/O on PB3 */
    GPIO_PORTB_DEN_REG |= (1 << 3);
    /* Clear PMCx bits for PB3 to use it as a GPIO pin */
    GPIO_PORTB_PCTL_REG &= ~(0x000000F0);
    /* Clear bit 3 in Data register */
    GPIO_PORTB_DATA_REG &= ~(1 << 3);
}

