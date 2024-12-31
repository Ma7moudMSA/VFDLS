/*
 * UART.c
 *
 */

#include "tm4c123gh6pm_registers.h"
#include "UART.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                         Private Functions Definitions                       *
 *******************************************************************************/

static void GPIO_SetupUART0Pins(void)
{
    SYSCTL_RCGCGPIO_REG  |= 0x01;                 /* Enable clock for GPIO PORTA */
    while(GET_BIT(SYSCTL_RCGCGPIO_REG,0) == 0);   /* Wait until GPIO PORTA clock is activated and it is ready for access*/

    GPIO_PORTA_AMSEL_REG &= 0xFC;         /* Disable Analog on PA0 & PA1 */
    GPIO_PORTA_DIR_REG   &= 0xFE;         /* Configure PA0 as input pin */
    GPIO_PORTA_DIR_REG   |= 0x02;         /* Configure PA1 as output pin */
    GPIO_PORTA_AFSEL_REG |= 0x03;         /* Enable alternative function on PA0 & PA1 */
    /* Set PMCx bits for PA0 & PA1 with value 1 to use PA0 as UART0 RX pin and PA1 as UART0 Tx pin */
    GPIO_PORTA_PCTL_REG  = (GPIO_PORTA_PCTL_REG & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_REG   |= 0x03;         /* Enable Digital I/O on PA0 & PA1 */
}

/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

void UART0_DisableInterrupt(void)
{

    UART0_IM_REG &= ~(UART_IM_RXIM | UART_IM_TXIM); // Disable module interrupts


    NVIC_EN0_REG &= ~(1 << 5); // disable UART0 interrupts from NVIC from pin5
}
void UART0_EnableInterrupt(void)
{

    UART0_IM_REG |= UART_IM_RXIM; // Enable interrupts on RX
    UART0_IM_REG |= UART_IM_TXIM; // Enable interrupts on TX


    NVIC_EN0_REG |= (1 << 5); //enable UART0 interrupts from NVIC from pin5
}


void UART0_Handler(void)
{
    // check on the source of the interrupt(RX)
    if (UART0_MIS_REG & UART_MIS_RXMIS)
    {
        operation = UART0_DR_REG; // Read the received byte


        while (UART0_FR_REG & UART_FR_TXFF) ; // Wait until TX FIFO is not empty
        UART0_DR_REG = operation; //change the operation

        // Clear the receive interrupt
        UART0_ICR_REG = UART_ICR_RXIC;
    }
    else
    {
        // clear flag
        UART0_ICR_REG = 0xFFFF;
    }
}

void UART0_Init(void)
{

    GPIO_SetupUART0Pins();

    SYSCTL_RCGCUART_REG |= 0x01;          /* Enable clock for UART0 */
    while(!(SYSCTL_PRUART_REG & 0x01));   /* Wait until UART0 clock is activated and it is ready for access*/

    UART0_CTL_REG = 0;                    /* Disable UART0 at the beginning */

    UART0_CC_REG  = 0;                    /* Use System Clock*/

    /* To Configure UART0 with Baud Rate 9600 */
    UART0_IBRD_REG = 104;
    UART0_FBRD_REG = 11;

    /* UART Line Control Register Settings
     * BRK = 0 Normal Use
     * PEN = 0 Disable Parity
     * EPS = 0 No affect as the parity is disabled
     * STP2 = 0 1-stop bit at end of the frame
     * FEN = 0 FIFOs are disabled
     * WLEN = 0x3 8-bits data frame
     * SPS = 0 no stick parity
     */
    UART0_LCRH_REG = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);

    UART0_IM_REG |= (1 << 4) | (1 << 5);  /* Enable interrupts on RX and TX  */


    NVIC_EN0_REG |= (1<<5); //enable interrupt for UART0

    /* UART Control Register Settings
     * RXE = 1 Enable UART Receive
     * TXE = 1 Enable UART Transmit
     * HSE = 0 The UART is clocked using the system clock divided by 16
     * UARTEN = 1 Enable UART
     */
    UART0_CTL_REG = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
}

void UART0_SendByte(unsigned char data)
{
    while(!(UART0_FR_REG & UART_FR_TXFE_MASK)); /* Wait until the transmit FIFO is empty */
    UART0_DR_REG = data; /* Send the byte */
}

unsigned char UART0_ReceiveByte(void)
{
    while(UART0_FR_REG & UART_FR_RXFE_MASK); /* Wait until the receive FIFO is not empty */
    return UART0_DR_REG; /* Read the byte */
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART0_SendString(unsigned char *pData)
{
    unsigned long uCounter =0;
    /* Transmit the whole string */
    while(pData[uCounter] != '\0')
    {
        UART0_SendByte(pData[uCounter]); /* Send the byte */
        uCounter++; /* increment the counter to the next byte */
    }
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART0_ReceiveString(unsigned char *pData)
{
    unsigned long uCounter =0;

    pData[uCounter] = UART0_ReceiveByte(); /* Receive the first byte */

    /* Receive the whole string until the '#' */
    while(pData[uCounter] != '#')
    {
        uCounter++;
        pData[uCounter] = UART0_ReceiveByte();
    }
    /* After receiving the whole string plus the '#', replace the '#' with '\0' */
    pData[uCounter] = '\0';
}

/*
 * Description :
 * Send the required number of bytes through UART to the other UART device.
 */
void UART0_SendData(unsigned char *pData, unsigned long uSize)
{
    /* Transmit the number of bytes requested on the UART port */
    while(uSize--)
    {

        UART0_SendByte(*pData); /* Send the byte */
        pData++; /* increment pointer to the next byte */
    }
}

/*
 * Description :
 * receive the required number of bytes through UART from the other UART device.
 */
void UART0_ReceiveData(unsigned char *pData, unsigned long uSize)
{
    /* Receive the number of bytes requested on the UART port */
    while(uSize--)
    {
        *pData = UART0_ReceiveByte(); /* receive a byte from the UART */
         pData++; /* increment pointer to receive the next byte in the next location */
    }
}



