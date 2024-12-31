/*
 * GPTimers.h
 *
 *  Created on: Dec 20, 2024
 */

#ifndef MCAL_GPTIMERS_H_
#define MCAL_GPTIMERS_H_

#include "tm4c123gh6pm_registers.h"
void Timer1A_Init(void);



/* System Control Registers */
#define SYSCTL_RCGCTIMER_R     (*((volatile unsigned long *)0x400FE604)) // Timer Run Mode Clock Gating Control
#define SYSCTL_PRTIMER_R       (*((volatile unsigned long *)0x400FEA04)) // Timer Peripheral Ready

/* Timer1 Base Address */
#define TIMER1_BASE            0x40031000

/* Timer1 Registers */
#define TIMER1_CFG_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x000))) // GPTM Configuration
#define TIMER1_TAMR_R          (*((volatile unsigned long *)(TIMER1_BASE + 0x004))) // GPTM Timer A Mode
#define TIMER1_CTL_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x00C))) // GPTM Control
#define TIMER1_IMR_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x018))) // GPTM Interrupt Mask
#define TIMER1_RIS_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x01C))) // GPTM Raw Interrupt Status
#define TIMER1_ICR_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x024))) // GPTM Interrupt Clear
#define TIMER1_TAILR_R         (*((volatile unsigned long *)(TIMER1_BASE + 0x028))) // GPTM Timer A Interval Load
#define TIMER1_TAV_R           (*((volatile unsigned long *)(TIMER1_BASE + 0x050))) // GPTM Timer A Value

/* NVIC Registers for Interrupt Handling */
#define NVIC_EN0_R             (*((volatile unsigned long *)0xE000E100)) // NVIC Enable Register 0
#define NVIC_PRI5_R            (*((volatile unsigned long *)0xE000E414)) // NVIC Priority Register for IRQ21 (Timer1A)



/* Bit Masks */
#define SYSCTL_RCGCTIMER_TIMER1 0x02     // Enable Timer1 clock
#define TIMER_CTL_TAEN           0x01    // Timer A Enable
#define TIMER_CFG_32BIT          0x00    // 32-bit timer configuration
#define TIMER_TAMR_PERIODIC      0x02    // Timer A Periodic Mode
#define TIMER_IMR_TATOIM         0x01    // Timer A Timeout Interrupt Mask
#define TIMER_ICR_TATOCINT       0x01    // Clear Timer A timeout interrupt flag
#define NVIC_EN0_TIMER1A         (1 << 21) // NVIC enable bit for Timer1A (IRQ 21)
#define TIMER1_MIS_R (*((volatile unsigned long *)0x40031020))
#define TIMER_MIS_TAMIS 0x00000001  // TimerA Masked Interrupt Status



#endif /* MCAL_GPTIMERS_H_ */
