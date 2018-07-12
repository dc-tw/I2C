/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define TP_I2C                           I2C1
#define TP_I2C_CLK                       RCC_APB1Periph_I2C1

#define TP_I2C_SCL_PIN                   GPIO_Pin_6                  /* PB.06 */
#define TP_I2C_SCL_GPIO_PORT             GPIOB                       /* GPIOB */
#define TP_I2C_SCL_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define TP_I2C_SCL_SOURCE                GPIO_PinSource6
#define TP_I2C_SCL_AF                    GPIO_AF_1

#define TP_I2C_SDA_PIN                   GPIO_Pin_7                  /* PB.07 */
#define TP_I2C_SDA_GPIO_PORT             GPIOB                       /* GPIOB */
#define TP_I2C_SDA_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define TP_I2C_SDA_SOURCE                GPIO_PinSource7
#define TP_I2C_SDA_AF                    GPIO_AF_1

#define TP_I2C_TIMING           0x00C0D5FF//0x20503F5C//0x00501953  //0x00C0D5FF//0x10805E89    //0x00201953
#define TP_SLAVE_WRITE_ADDRESS         0xA0
#define TP_SLAVE_READ_ADDRESS          0xA1
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HW_TP_Init(void);
void HW_TP_DeInit(void);
__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead);
uint32_t sEE_TIMEOUT_UserCallback(void);


/************************ (C) COPYRIGHT HoyenTech*****END OF FILE****/
