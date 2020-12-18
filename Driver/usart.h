/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:44:29
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:19:57
 */
#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "string.h"
#include "sys.h" 

#define USART_PRINTF				

#define USART_BAUD				115200

#define USART_REC_LEN  			15	 	//定义最大接收字节数 15

#define DATA_LEN  				8	 	//定义数据场字节数 8

typedef __packed struct
{
	__IO uint16_t head;
	__IO uint8_t len;
	__IO uint8_t cmd;
	__IO uint16_t canid;
	__IO uint8_t data[DATA_LEN];
	__IO uint8_t checksum;
} msg_t;

typedef __packed union
{
	uint8_t buffer[USART_REC_LEN];
	msg_t  msg;
} Msg_t;

extern Msg_t UartTxMsg, UartRxMsg;

void Uart_Init(uint32_t baud);
void USART_Send_Byte(uint8_t buf);
void USART_Send_Data(uint8_t *buf, uint8_t len);

#endif


