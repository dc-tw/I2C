/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CFG_I2C_H
#define __HW_CFG_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
#define I2C_ON                           I2C1
#define I2C_CLK                       RCC_APB1Periph_I2C1

#define I2C_SCL_PIN                   GPIO_Pin_6                  /* PB.06 */
#define I2C_SCL_GPIO_PORT             GPIOB                       /* GPIOB */
#define I2C_SCL_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define I2C_SCL_SOURCE                GPIO_PinSource6
#define I2C_SCL_AF                    GPIO_AF_1

#define I2C_SDA_PIN                   GPIO_Pin_7                  /* PB.07 */
#define I2C_SDA_GPIO_PORT             GPIOB                       /* GPIOB */
#define I2C_SDA_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define I2C_SDA_SOURCE                GPIO_PinSource7
#define I2C_SDA_AF                    GPIO_AF_1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void i2c1_lowlevel_cfg(void);
void i2c_Init_cfg(void);
void i2c_DeInit_cfg(void);
uint32_t i2c_TIMEOUT_UserCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* __HW_CFG_I2C_H */


/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
