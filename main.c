/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hw_cfg.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TPRx1Buffer[50] = {0x55};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  if (SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */ 
    while (1);
  }
  __IO uint32_t I2C_TimeOut = 0x1000;

  HW_TP_Init();
  USART_Config();

  while(1)
  {
    //Delay(100);
    TP_ReadBuffer(TPRx1Buffer, 2);
    
    printf("ok\r\n");
   while(I2C_GetFlagStatus(I2C2, I2C_ISR_BUSY) != RESET)
  {
    if((I2C_TimeOut--) == 0) return sEE_TIMEOUT_UserCallback();
  }
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
