#include "GPTimers.h"

short Seconds_Timer_1=0;
short Seconds_Timer_2=0;
void Timer1A_Init(void)
{

    // Step 1: Enable Timer1 Clock
      SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_TIMER1;   // Enable Timer1 clock
      while ((SYSCTL_RCGCTIMER_R & SYSCTL_RCGCTIMER_TIMER1) == 0); // Wait for Timer1 to be ready

      // Step 2: Disable Timer1A
      TIMER1_CTL_R &= ~TIMER_CTL_TAEN;   // Disable Timer1A during configuration

      // Step 3: Configure Timer1 as a 32-bit Timer
      TIMER1_CFG_R = TIMER_CFG_32BIT;    // Set as 32-bit timer configuration

      // Step 4: Set Timer1A in Periodic Mode
      TIMER1_TAMR_R |= TIMER_TAMR_PERIODIC;  // Configure as periodic timer

      // Step 5: Load the Start Value into the Interval Load Register
      TIMER1_TAILR_R = 16000000 - 1;     // Load the interval value

      // Step 6: Enable Interrupts (Optional)
      TIMER1_ICR_R = TIMER_ICR_TATOCINT; // Clear any pending timeout interrupt
      TIMER1_IMR_R |= TIMER_IMR_TATOIM;   // Enable Timer1A timeout interrupt

      // Step 7: Enable NVIC Interrupt for Timer1A
      NVIC_EN0_R |= NVIC_EN0_TIMER1A;    // Enable IRQ 21 for Timer1A

      // Step 8: Enable Timer1A
      TIMER1_CTL_R |= TIMER_CTL_TAEN;    // Enable Timer1A to start counting

}

