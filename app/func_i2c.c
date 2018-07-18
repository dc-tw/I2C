#include "func_i2c.h"
#include "hw_cfg_i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t flag = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void HW_TP_Init(void);
void HW_TP_DeInit(void);
__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead);
__IO int TP_WriteBuffer(uint8_t* pBuffer, int input_number);

uint32_t sEE_TIMEOUT_UserCallback(void);


/**
  * @brief  Configure the I2C Clock source and Power clock
  * @param  None
  * @retval None
  */
void HW_TP_Init(void)
{ 
  i2c1_lowlevel_cfg();
  i2c_Init_cfg();
}

void HW_TP_DeInit(void)
{
  i2c_DeInit_cfg();
}




__IO int TP_ReadBuffer(uint8_t* pBuffer, uint16_t NumByteToRead)
{
  uint32_t I2C_TimeOut = 0x2000;
   /* Test on BUSY Flag */
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_BUSY) != RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return i2c_TIMEOUT_UserCallback();
  }
 
  /* Configure slave address, nbytes, reload, end mode and start or stop generation */
  I2C_TransferHandling(I2C_ON, TP_SLAVE_WRITE_ADDRESS, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

  /* Wait until TXIS flag is set */
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_TXIS) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_SendData(I2C_ON, 0x08);
  
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_TC) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_TransferHandling(I2C_ON, 0xA1, NumByteToRead, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  


  /* Wait until all data are received */
  while (NumByteToRead)
  {   
    /* Wait until RXNE flag is set */
    I2C_TimeOut = 0x3000;
    while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_RXNE) == RESET)    
    {
      if((I2C_TimeOut--) == 0) return -1;//i2c_TIMEOUT_UserCallback();
    }
    

    
    /* Read data from RXDR */
    *pBuffer = I2C_ReceiveData(I2C_ON);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
    
    /* Decrement the read bytes counter */
    NumByteToRead--;

  } 
  
  /* Wait until STOPF flag is set */
  I2C_TimeOut = 0x3000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_STOPF) == RESET)   
  {
    if((I2C_TimeOut--) == 0)
      return -1; //i2c_TIMEOUT_UserCallback();
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(I2C_ON, I2C_ICR_STOPCF);

  /* If all operations OK */
  return 0;
}

__IO int TP_WriteBuffer(uint8_t* pBuffer, int input_number)
{
    uint32_t I2C_TimeOut = 0x2000;
   /* Test on BUSY Flag */
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_BUSY) != RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return i2c_TIMEOUT_UserCallback();
  }
 
  /* Configure slave address, nbytes, reload, end mode and start or stop generation */
  I2C_TransferHandling(I2C_ON, TP_SLAVE_WRITE_ADDRESS, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

  /* Wait until TXIS flag is set */
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_TXIS) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_SendData(I2C_ON, 0xC4);
  
  I2C_TimeOut = 0x3000;//0xf000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_TC) == RESET)
  {
    if((I2C_TimeOut--) == 0) 
      return 0;
  }

  I2C_TransferHandling(I2C_ON, 0xA1, input_number, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
  

  uint8_t i = 0;
  /* Wait until all data are received */
  for (i=0 ; i < input_number; i++)
  {   
    /* Wait until RXNE flag is set */
    I2C_TimeOut = 0x3000;
    while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_TXIS) == RESET)    
    {
      if((I2C_TimeOut--) == 0) return -1;//i2c_TIMEOUT_UserCallback();
    }

    /* Read data from RXDR */
    I2C_SendData(I2C_ON, pBuffer[i]);

  } 
  
  /* Wait until STOPF flag is set */
  I2C_TimeOut = 0x3000;
  while(I2C_GetFlagStatus(I2C_ON, I2C_ISR_STOPF) == RESET)   
  {
    if((I2C_TimeOut--) == 0)
      return 0; //i2c_TIMEOUT_UserCallback();
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(I2C_ON, I2C_ICR_STOPCF);

  /* If all operations OK */
  return 0;
}



uint8_t keyin_binary(uint8_t key1_8,uint8_t key9_16)
{
  uint8_t keyin = 1;
  switch(key1_8)
    {
    case 0x01:
      keyin = 1;
    break;
    case 0x02:
      keyin = 2;
    break;
    case 0x04:
      keyin = 3;
    break;
    case 0x08:
      keyin = 4;
    break;    
    case 0x10:
      keyin = 5;
    break;
    case 0x20:
      keyin = 6;
    break;
    case 0x40:
      keyin = 7;
    break;
    case 0x80:
      keyin = 8;
    break;
    default:
    break;
    }

  switch(key9_16)
    {
    case 0x01:
      keyin = 9;
    break;
    case 0x02:
      keyin = 10;
    break;
    case 0x04:
      keyin = 11;
    break;
    case 0x08:
      keyin = 12;
    break;    
    case 0x10:
      keyin = 13;
    break;
    case 0x20:
      keyin = 14;
    break;
    case 0x40:
      keyin = 15;
    break;
    case 0x80:
      keyin = 16;
    break;
    default:
    break;
    }
  return keyin;
}



/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
