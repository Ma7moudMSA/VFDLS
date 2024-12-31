/*
 * ultrasonic.h
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND        364
#define NUMBER_OF_ITERATIONS_PER_ONE_MICRO_SECOND       3.64
#define GPIO_PORTF_PRIORITY_MASK                       0xFF1FFFFF
#define GPIO_PORTF_PRIORITY_BITS_POS                   21
#define GPIO_PORTF_INTERRUPT_PRIORITY                   1




/* Functions Prototype */
void TriggerPin_init ();
void EchoPin_init(void);

void Delay_US(unsigned long long n); //Delays for micro-Seconds
static void  Delay_MS(unsigned long long n); //Delays for Mili-Seconds

#endif /* ULTRASONIC_H_ */
