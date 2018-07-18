/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


#define TP_I2C_TIMING           0x00C0D5FF//0x20503F5C//0x00501953  //0x00C0D5FF//0x10805E89    //0x00201953
#define TP_SLAVE_WRITE_ADDRESS         0xA0
#define TP_SLAVE_READ_ADDRESS          0xA1
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HW_TP_Init(void);
void HW_TP_DeInit(void);
__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead);
uint8_t keyin_binary(uint8_t key1_8,uint8_t key9_16);
__IO int TP_WriteBuffer(uint8_t* pBuffer, int input_number);


/************************ (C) COPYRIGHT HoyenTech*****END OF FILE****/
