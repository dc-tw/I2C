#include "hw_cfg_i2c.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void i2c1_lowlevel_cfg(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure the I2C clock source. The clock is derived from the HSI */
  RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);

  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(I2C_SCL_GPIO_CLK | I2C_SDA_GPIO_CLK, ENABLE);

  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);

  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(I2C_SCL_GPIO_PORT, I2C_SCL_SOURCE, I2C_SCL_AF);

  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(I2C_SDA_GPIO_PORT, I2C_SDA_SOURCE, I2C_SDA_AF);

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
}

void i2c_Init_cfg(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
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
  I2C_Init(I2C_ON, &I2C_InitStructure);
   
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(I2C_ON, ENABLE);    
}

void i2c_DeInit_cfg(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(I2C_ON, DISABLE);

  /* sEE_I2C DeInit */
  I2C_DeInit(I2C_ON);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(I2C_CLK, DISABLE);

  /* GPIO configuration */
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
  GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
}

uint32_t i2c_TIMEOUT_UserCallback(void)
{
  /* Use application may try to recover the communication by resetting I2C
    peripheral (calling the function I2C_SoftwareResetCmd()) then re-start
    the transmission/reception from a previously stored recover point.
    For simplicity reasons, this example only shows a basic way for errors 
    managements which consists of stopping all the process and requiring system
    reset. */
 GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(I2C_ON, DISABLE);
 
  /* sEE_I2C DeInit */
  I2C_DeInit(I2C_ON);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(I2C_CLK, DISABLE);
    
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
  GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

  I2C_InitTypeDef  I2C_InitStructure;
  
 /* Configure the I2C clock source. The clock is derived from the HSI */
  RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);
    
  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(I2C_SCL_GPIO_CLK | I2C_SDA_GPIO_CLK, ENABLE);
  
  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);
  
  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(I2C_SCL_GPIO_PORT, I2C_SCL_SOURCE, I2C_SCL_AF);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(I2C_SDA_GPIO_PORT, I2C_SDA_SOURCE, I2C_SDA_AF);
  
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
  GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
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
  I2C_Init(I2C_ON, &I2C_InitStructure);
   
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(I2C_ON, ENABLE);    
  /* Block communication and all processes */
  while (1)
  {   
  }  
}



/************************ (C) COPYRIGHT HoyenTech *****END OF FILE****/
