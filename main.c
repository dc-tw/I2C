/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hw_cfg.h"
#include "stdio.h"
#include "func_i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TPRx1Buffer[50] = {0};
uint16_t key = 1;
extern __IO uint8_t flag;
uint8_t WriteBuffer[50] = {0x40};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  if (SysTick_Config(SystemCoreClock / 100000))
  {
    /* Capture error */ 
    while (1);
  }
  __IO uint32_t I2C_TimeOut = 0x1000;

  HW_TP_Init();
  //USART_Config();
  ENABLE_GPIOC_5_8();
  
 

  EXTI4_15_Config();
  TP_WriteBuffer(WriteBuffer,22);
  
  while(1)
  {
    if(flag == 1){
    
    TP_ReadBuffer(TPRx1Buffer, 2);
    key = keyin_binary(TPRx1Buffer[0],TPRx1Buffer[1]);
    //read = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10);
    GPIOC->BRR = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;
    }
    //printf("%d",read);
    GPIOC->BSRR = (key -1) << 5;
    

  }
}






#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
