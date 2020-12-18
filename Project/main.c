/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-27 14:56:48
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:34:15
 */
/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "queue.h"

/** @addtogroup STM32F0xx_StdPeriph_Templates
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define SIZE sizeof(flash_data_t)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @name: Bsp_Init
 * @description: none
 * @param {type} none
 * @return {type} none
 */
static void Bsp_Init(void)
{
  Uart_Init(USART_BAUD);
	TIM14_Init(TIMER_PERIOD, TIMER_PSC);        //48Mhz/48/1000=1Khz

  #if DEBUG
		printf("DEBUG MODE\r\n");
	#endif

  #if SYS_CLOCK_MCO
    /* Output HSE clock on MCO1 pin(PA8) ****************************************/     
    /* Enable the GPIOA Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* MCO pin configuration: PA8 */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

    RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_1);
  #endif
}

/**
 * @name: UsartQueueDataProcess
 * @description: none
 * @param {*}
 * @return {*}
 */
void UsartQueueDataProcess(void)
{
  uint8_t i;

  if (Rxbuffer.size >= USART_REC_LEN)
  {
    #if DEBUG
    printf("1-Rxbuffer.size=%d\r\n",Rxbuffer.size);
    #endif

    if (RingQueuePop(&Rxbuffer, &UartRxMsg.buffer[0]) == RING_QUEUE_OK && RingQueuePop(&Rxbuffer, &UartRxMsg.buffer[1]) == RING_QUEUE_OK)
    {
      if (UartRxMsg.msg.head == 0xAA55)
      {
        #if DEBUG
        printf("data:%02X %02X ",UartRxMsg.buffer[0], UartRxMsg.buffer[1]);
        #endif

        for (i = 2; i < USART_REC_LEN; i++)
        {
          RingQueuePop(&Rxbuffer, &UartRxMsg.buffer[i]);
          
          #if DEBUG
          printf("%02X ",UartRxMsg.buffer[i]);
          #endif
        }

        #if DEBUG
        printf("\r\n2-Rxbuffer.size=%d\r\n\r\n",Rxbuffer.size);
        #endif
      }
    }
  }
}

/**
 * @name: main
 * @description: none
 * @param {type} none
 * @return {type} none
 */
int main(void)
{
	Bsp_Init();

	while (1)
	{
    UsartQueueDataProcess();
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
