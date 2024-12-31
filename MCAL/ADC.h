/*
 * ADC.h
 */

#ifndef ADC_H_
#define ADC_H_
/*
 * include files
 */
#include "std_types.h"

/*
 * macros
 */
#define ADC_MAXIMUM_VALUE    4095
#define ADC_REF_VOLT_VALUE   3.3

/*
 * implementation
 */
void ADC_Init(unsigned char channel);
unsigned short  ADC_ReadChannel(void);
#endif /* ADC_H_ */
