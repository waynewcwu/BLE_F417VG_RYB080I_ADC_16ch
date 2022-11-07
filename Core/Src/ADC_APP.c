/*
 * ADC_APP.c
 *
 *  Created on: Sep 8, 2020
 *      Author: USER
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
ADC1_t ADC_1;

void ADC1_Conv(ADC_HandleTypeDef *hadc)
{
	//ADC start, LED status = 0
	HAL_GPIO_WritePin(GPIOD, RedLED , GPIO_PIN_RESET);
	unsigned char Count_in, Count_Sum;
	unsigned char Count_Sum_value = 200;//adc value Sum count
    for(Count_Sum=0; Count_Sum < Count_Sum_value; Count_Sum++)//take the adc value sum by count 60
    {
    	for(Count_in=0; Count_in < ADC_Buffer_Ch; Count_in++)//Convert ADC IN by scan channel
    	{
    		/*##-1- Start the conversion process #######################################*/
    		HAL_ADC_Start(hadc);
    		/*##-2- Wait for the end of conversion #####################################*/
    		/*  Before starting a new conversion, you need to check the current state of
    			the peripheral; if it?�s busy you need to wait for the end of current
    			conversion before starting a new one.
    			For simplicity reasons, this example is just waiting till the end of the
    	 	 	conversion, but application may perform other tasks while conversion
    			operation is ongoing. */
    		HAL_ADC_PollForConversion(hadc, 50);
    
    			/* Check if the continous conversion of regular channel is finished */
    		while(!HAL_IS_BIT_SET(HAL_ADC_GetState(hadc), HAL_ADC_STATE_REG_EOC)){};
    		/*##-3- Get the converted value of regular channel  ######################*/
    		ADC_1.BufferValue[Count_in] = HAL_ADC_GetValue(hadc);
            ADC_1.BufferValue_Sum[Count_in] += ADC_1.BufferValue[Count_in];
            ADC_1.BufferValue[Count_in]=0;//clear adc bufferValue
    
    	}
    	HAL_ADC_Stop(hadc);
    }//End adc value sum by count 60
    
    for(Count_in=0; Count_in < ADC_Buffer_Ch; Count_in++)//Calculate the ADC value average Convert to the Temp value
    {
        ADC_1.BufferValue_Avg[Count_in] = ADC_1.BufferValue_Sum[Count_in]/Count_Sum_value ;
        
        //ADC voltage digital valve, max:4095
//        ADC_1.Vol[Count_in]=ADC_1.BufferValue_Avg[Count_in];
        
        //Calculate LM35 Temperature Sensor value
        ADC_1.Temp[Count_in]=ADC_1.BufferValue_Avg[Count_in]*3300/4095;//LM35 output voltage(mv)
        
        ADC_1.BufferValue_Sum[Count_in]=0;//clear Sum ValueV                
        ADC_1.BufferValue_Avg[Count_in]=0;//clear avg Value
                
    }
    //ADC end cycle, LED status =1
    HAL_GPIO_WritePin(GPIOD, RedLED , GPIO_PIN_SET);
}
