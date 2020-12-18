/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:44:29
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:20:30
 */
#include "usart.h"
#include "sys.h"
#include "queue.h"

Msg_t UartTxMsg,UartRxMsg;

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if defined(USART_PRINTF)
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}

//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while ((USART1->ISR & 0X40) == 0); //循环发送,直到发送完毕
	USART1->TDR = (uint8_t)ch;
	return ch;
}
#endif

/*使用microLib的方法*/
/* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)
{ 
    while (!(USART1->SR & USART_FLAG_RXNE));
    return ((int)(USART1->DR & 0x1FF));
}
*/

/**
 * @name: Uart_Init
 * @description: none
 * @param {type} uint32_t baud
 * @return {type} none
 */
void Uart_Init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART1 Pins configuration ************************************************/
	/* Connect pin to Periph */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);

	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART1 IRQ Channel configuration */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = USART1_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	/* Enable 8xUSARTs Receive interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* Enable the 8xUSARTs */
	USART_Cmd(USART1, ENABLE);

	RingQueueInit(&Rxbuffer);
}

/**
 * @name: USART_Send_Byte
 * @description: none
 * @param {type} uint8_t buf
 * @return {type} none
 */
void USART_Send_Byte(uint8_t buf)
{
	USART_SendData(USART1, buf);	//send single byte
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
 * @name: USART_Send_Data
 * @description: none
 * @param {type} uint8_t *buf, uint8_t len
 * @return {type} none
 */
void USART_Send_Data(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;

	//send multiple bytes
	for (i = 0; i < len; i++)
	{
		USART_Send_Byte(buf[i]);	//send single byte
	}
}

/**
 * @name: USART_SendString
 * @description: none
 * @param {type} uint8_t *str
 * @return {type} none
 */
void USART_SendString(uint8_t *str)
{
	while(*str != '\0')
	{
		USART_Send_Byte(*str);
		str++;
	}
}

/**
 * @name: USART1_IRQHandler
 * @description: none
 * @param {type} none
 * @return {type} none
 */
void USART1_IRQHandler(void)
{
	uint8_t Res;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 	//
	{
		Res = USART_ReceiveData(USART1);					//read data

		RingQueuePush(&Rxbuffer, Res);	
	}
}
