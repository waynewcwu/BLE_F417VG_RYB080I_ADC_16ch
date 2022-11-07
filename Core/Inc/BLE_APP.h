/*
 * ADC_APP.h
 *
 *  Created on: Sep 8, 2020
 *      Author: USER
 */

#ifndef INC_BLE_APP_H_
#define INC_BLE_APP_H_



#endif /* INC_BLE_APP_H_ */

/* Exported types ------------------------------------------------------------*/
#define Uart_Buffer_Size 100
typedef struct
{
	_Bool sendflag;
	//usart transfermit
	unsigned char __attribute__ ((aligned (32))) buffer[Uart_Buffer_Size];
	//char __attribute__ ((aligned (32))) buffer[Uart_Buffer_Size];
	//unsigned char __attribute__ ((aligned (32))) Rbuffer[Uart_Buffer_Size];
	uint32_t sendTimeout;
	uint32_t bufferSize;
	uint8_t SecCount;

} USART_BLE;
/* Private defines -----------------------------------------------------------*/
//Define RYB080E AT Command
#define PWSlaveMode	"AT+PWMODE=2\r\n"
#define GreenLED GPIO_PIN_12
#define RSTPin GPIO_PIN_8

/* Exported macro ------------------------------------------------------------*/
#define min(a, b) ((a) < (b)) ? (a) : (b)
#define max(a, b) ((a) > (b)) ? (a) : (b)

/* Exported functions prototypes ---------------------------------------------*/
void BLE_USART(UART_HandleTypeDef *huart);
void BLECommand(UART_HandleTypeDef *huart,  uint32_t *cmd);
void BLE_HW_RSEST(void);
void RYB080E_Init(void);
