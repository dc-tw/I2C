#include "func_i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void HW_TP_Init(void);
void HW_TP_DeInit(void);
__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead);
uint32_t sEE_TIMEOUT_UserCallback(void);


/**
  * @brief  Configure the I2C Clock source and Power clock
  * @param  None
  * @retval None
  */
void HW_TP_Init(void)
{ 
  I2C_InitTypeDef  I2C_InitStructure;

  /*-----------------------------------------*/   
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure the I2C clock source. The clock is derived from the HSI */
  RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);

  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(TP_I2C_SCL_GPIO_CLK | TP_I2C_SDA_GPIO_CLK, ENABLE);

  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(TP_I2C_CLK, ENABLE);

  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(TP_I2C_SCL_GPIO_PORT, TP_I2C_SCL_SOURCE, TP_I2C_SCL_AF);

  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(TP_I2C_SDA_GPIO_PORT, TP_I2C_SDA_SOURCE, TP_I2C_SDA_AF);

  /* GPIO configuration */
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*--------------------------------------*/

  /* I2C configuration */
  /* sEE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = 0x20302E37;//TP_I2C_TIMING;
  
  /* Apply sEE_I2C configuration after enabling it */
  I2C_Init(TP_I2C, &I2C_InitStructure);
   
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(TP_I2C, ENABLE);    
}

void HW_TP_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(TP_I2C, DISABLE);

  /* sEE_I2C DeInit */
  I2C_DeInit(TP_I2C);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(TP_I2C_CLK, DISABLE);

  /* GPIO configuration */
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TP_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SDA_PIN;
  GPIO_Init(TP_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
}




__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead)
{
  uint32_t I2C_TimeOut = 0x2000;
   /* Test on BUSY Flag */
  while(I2C_GetFlagStatus(TP_I2C, I2C_ISR_BUSY) != RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return sEE_TIMEOUT_UserCallback();
  }
 
  /* Configure slave address, nbytes, reload, end mode and start or stop generation */
  I2C_TransferHandling(TP_I2C, TP_SLAVE_WRITE_ADDRESS, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

  /* Wait until TXIS flag is set */
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(TP_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_SendData(TP_I2C, 0x08);
  
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(TP_I2C, I2C_ISR_TC) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_TransferHandling(TP_I2C, 0xA1, NumByteToRead, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  


  /* Wait until all data are received */
  while (NumByteToRead)
  {   
    /* Wait until RXNE flag is set */
    I2C_TimeOut = 0x3000;
    while(I2C_GetFlagStatus(TP_I2C, I2C_ISR_RXNE) == RESET)    
    {
      if((I2C_TimeOut--) == 0) return -1;//sEE_TIMEOUT_UserCallback();
    }
    

    
    /* Read data from RXDR */
    *pBuffer = I2C_ReceiveData(TP_I2C);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
    
    /* Decrement the read bytes counter */
    NumByteToRead--;

  } 
  
  /* Wait until STOPF flag is set */
  I2C_TimeOut = 0x3000;
  while(I2C_GetFlagStatus(TP_I2C, I2C_ISR_STOPF) == RESET)   
  {
    if((I2C_TimeOut--) == 0)
      return -1; //sEE_TIMEOUT_UserCallback();
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(TP_I2C, I2C_ICR_STOPCF);

  /* If all operations OK */
  return 0;
}

uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Use application may try to recover the communication by resetting I2C
    peripheral (calling the function I2C_SoftwareResetCmd()) then re-start
    the transmission/reception from a previously stored recover point.
    For simplicity reasons, this example only shows a basic way for errors 
    managements which consists of stopping all the process and requiring system
    reset. */
 GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(TP_I2C, DISABLE);
 
  /* sEE_I2C DeInit */
  I2C_DeInit(TP_I2C);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(TP_I2C_CLK, DISABLE);
    
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TP_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SDA_PIN;
  GPIO_Init(TP_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

  I2C_InitTypeDef  I2C_InitStructure;
  
 /* Configure the I2C clock source. The clock is derived from the HSI */
  RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);
    
  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(TP_I2C_SCL_GPIO_CLK | TP_I2C_SDA_GPIO_CLK, ENABLE);
  
  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(TP_I2C_CLK, ENABLE);
  
  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(TP_I2C_SCL_GPIO_PORT, TP_I2C_SCL_SOURCE, TP_I2C_SCL_AF);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(TP_I2C_SDA_GPIO_PORT, TP_I2C_SDA_SOURCE, TP_I2C_SDA_AF);
  
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TP_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = TP_I2C_SDA_PIN;
  GPIO_Init(TP_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  /* I2C configuration */
  /* sEE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = 0x20302E37;//sEE_I2C_TIMING;
  
  /* Apply sEE_I2C configuration after enabling it */
  I2C_Init(TP_I2C, &I2C_InitStructure);
   
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(TP_I2C, ENABLE);    
  /* Block communication and all processes */
  while (1)
  {   
  }  
}


/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
