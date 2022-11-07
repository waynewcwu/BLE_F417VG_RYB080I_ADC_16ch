/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
USART_BLE USARTBLE;
ADC1_t ADC_1;


void BLE_USART(UART_HandleTypeDef *huart)
{
	if(USARTBLE.sendflag ==1)
	{
		//transmit LED status
		HAL_GPIO_WritePin(GPIOD, GreenLED , GPIO_PIN_SET);
		//porting data to usart buffer--------------------------------------------------------------------------
//		sprintf(USARTBLE.buffer,
//				"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
//				ADC_1.Vol[0],ADC_1.Vol[1],ADC_1.Vol[2],ADC_1.Vol[3],ADC_1.Vol[4],
//				ADC_1.Vol[5],ADC_1.Vol[6],ADC_1.Vol[7],ADC_1.Vol[8],ADC_1.Vol[9],
//				ADC_1.Vol[10],ADC_1.Vol[11],ADC_1.Vol[12],ADC_1.Vol[13],ADC_1.Vol[14],
//				ADC_1.Vol[15]);
//
//		memset( ADC_1.Vol, 0, strlen(ADC_1.Vol) ); //clear ADC_1.Vol

		sprintf(USARTBLE.buffer,
						"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
						ADC_1.Temp[0],ADC_1.Temp[1],ADC_1.Temp[2],ADC_1.Temp[3],ADC_1.Temp[4],
						ADC_1.Temp[5],ADC_1.Temp[6],ADC_1.Temp[7],ADC_1.Temp[8],ADC_1.Temp[9],
						ADC_1.Temp[10],ADC_1.Temp[11],ADC_1.Temp[12],ADC_1.Temp[13],ADC_1.Temp[14],
						ADC_1.Temp[15]);

		memset( ADC_1.Temp, 0, strlen(ADC_1.Temp) ); //clear ADC_1.Temp
		//--------------------------------------------------------------------------------------------------------
		USARTBLE.bufferSize = min(Uart_Buffer_Size, strlen(USARTBLE.buffer));


		//USARTBLE.bufferSize = 3;
		USARTBLE.sendTimeout = 60 ;

		/**
		* @param huart   UART handle.
		* @param pData   Pointer to data buffer.
		* @param Size    Amount of data to be received.
		* @param Timeout Timeout duration.(ms)
		*/
		HAL_UART_Transmit(huart, &USARTBLE.buffer, USARTBLE.bufferSize, USARTBLE.sendTimeout );

		memset( USARTBLE.buffer, 0, strlen(USARTBLE.buffer) ); //clear Transmit buffer
		/**
		* @param huart   UART handle.
		* @param pData   Pointer to data buffer.
		* @param Size    Amount of data to be received.
		* @param Timeout Timeout duration.(ms)
		*/
		//HAL_UART_Receive(huart , &USARTBLE.Rbuffer, 14, 10);
		//char C[20];
		//strcpy(C,  USARTBLE.Rbuffer );
		USARTBLE.sendflag = 0;
		//transmit LED status
//		HAL_GPIO_WritePin(GPIOD, GreenLED , GPIO_PIN_SET);
//		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOD, GreenLED , GPIO_PIN_RESET);
		//0x1;
	}
}

void BLECommand(UART_HandleTypeDef *huart,  uint32_t *cmd)
{
	memset(USARTBLE.buffer, 0, strlen(USARTBLE.buffer) ); //clear usart buffer
	sprintf(USARTBLE.buffer,cmd);
	USARTBLE.bufferSize = min(Uart_Buffer_Size, strlen(USARTBLE.buffer));
	USARTBLE.sendTimeout = 50 ;
	/**
	* @param huart   UART handle.
	* @param pData   Pointer to data buffer.
	* @param Size    Amount of data to be received.
	* @param Timeout Timeout duration.(ms)
	*/
	while(HAL_UART_Transmit(huart, &USARTBLE.buffer, USARTBLE.bufferSize, USARTBLE.sendTimeout )!=HAL_OK);
}

void BLE_HW_RSEST(void)
{
	HAL_GPIO_WritePin(GPIOC, RSTPin , GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOC, RSTPin , GPIO_PIN_SET);
}
void RYB080E_Init(void)
{
	//Set Reset pin to high
	HAL_GPIO_WritePin(GPIOC, RSTPin , GPIO_PIN_SET);

//	//set power slave mode
//	HAL_Delay(20);
//	BLECommand(&huart6, PWSlaveMode);
//	BLE_HW_RSEST();
}
