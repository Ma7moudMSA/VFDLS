/*
 * pushbuttons.h
 */
#ifndef PUSHBUTTONS_H_
#define PUSHBUTTONS_H_


/*
 *
 * Port E
 */
#define ROpen_pin 2
#define R_pin 1
#define L_pin 4
#define LClose_pin 5

#define GPIO_PORTE_PRIORITY_MASK        0xffffff1f
#define GPIO_PORTE_INTERRUPT_PRIORITY   2
#define GPIO_PORTE_PRIORITY_BITS_POS    5


/*
 * implementation
 */
void PB1_Init(void);
void PB2_Init(void);
void PB3_Init(void);
void PB4_Init(void);

#endif /* PUSHBUTTONS_H_ */
