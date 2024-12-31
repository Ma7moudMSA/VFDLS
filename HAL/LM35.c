 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: LM35.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 *
 *
 *******************************************************************************/

#include "LM35.h"
#include "ADC.h"
#include "std_types.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{

	uint8 Temperature = 0;

	uint16 ADC_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	ADC_value = ADC_ReadChannel();

	/* Calculate the temperature from the ADC value*/
	Temperature = (uint8)(((uint32)ADC_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return Temperature;
}

