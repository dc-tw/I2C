/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CFG_H
#define __HW_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
   #define EVAL_COM1                        USART2
#define EVAL_COM1_CLK                    RCC_APB1Periph_USART2

#define EVAL_COM1_TX_PIN                 GPIO_Pin_2
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource2
#define EVAL_COM1_TX_AF                  GPIO_AF_1

#define EVAL_COM1_RX_PIN                 GPIO_Pin_3
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource3
#define EVAL_COM1_RX_AF                  GPIO_AF_1

#define EVAL_COM1_CTS_PIN                GPIO_Pin_11
#define EVAL_COM1_CTS_GPIO_PORT          GPIOA
#define EVAL_COM1_CTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define EVAL_COM1_CTS_SOURCE             GPIO_PinSource11
#define EVAL_COM1_CTS_AF                 GPIO_AF_1

#define EVAL_COM1_RTS_PIN                GPIO_Pin_12
#define EVAL_COM1_RTS_GPIO_PORT          GPIOA
#define EVAL_COM1_RTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define EVAL_COM1_RTS_SOURCE             GPIO_PinSource12
#define EVAL_COM1_RTS_AF                 GPIO_AF_1
   
#define EVAL_COM1_IRQn                   USART1_IRQn

#define COMn                             1


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ENABLE_GPIOA_67(void);

void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void EXTI4_15_Config(void);
void USART_Config(void);
void TIM_Config(void);
void USART_IN_Config(void);
void NVIC_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __HW_CFG_H */


/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
