/*
 * UART.h
 *

 */

#ifndef UART_H_
#define UART_H_


/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/

#define UART_DATA_5BITS          0x0
#define UART_DATA_6BITS          0x1
#define UART_DATA_7BITS          0x2
#define UART_DATA_8BITS          0x3
#define UART_IM_TXIM (1<<5)
#define UART_IM_RXIM (1<<4)
#define UART_LCRH_WLEN_BITS_POS  5
#define UART_CTL_UARTEN_MASK     0x00000001
#define UART_CTL_TXE_MASK        0x00000100
#define UART_CTL_RXE_MASK        0x00000200
#define UART_FR_TXFE_MASK        0x00000080
#define UART_FR_RXFE_MASK        0x00000010


/*
 *
 * pins
 */
#define UART_MIS_RXMIS  (1 << 4)   // Receive Masked Interrupt Status
#define UART_FR_TXFF    (1 << 5)   // Transmit FIFO Full
#define UART_ICR_RXIC   (1 << 4)   // Clear Receive Interrupt



static void GPIO_SetupUART0Pins(void);
void UART0_Init(void);
void UART0_SendByte(unsigned char data);
unsigned char UART0_ReceiveByte(void);
void UART0_SendString(unsigned char *pData);
void UART0_ReceiveString(unsigned char *pData);
void UART0_SendData(unsigned char *pData, unsigned long uSize);
void UART0_ReceiveData(unsigned char *pData, unsigned long uSize);


void UART0_Handler(void);
void UART0_DisableInterrupt(void);
void UART0_EnableInterrupt(void);




extern volatile char operation;



#endif /* UART_H_ */
