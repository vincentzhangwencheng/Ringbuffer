/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:38:28
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-12-18 12:23:15
 */
#ifndef __SYS_H
#define __SYS_H

#include "stm32f0xx.h"

#define DEBUG   1

#define BigLittleSwap16(A)          ((((uint16_t)(A) & 0xFF00) >> 8) | (((uint16_t)(A) & 0x0x00FF) << 8))

#define TIM2_PRIORITY               0x00  
#define EXTI0_1_PRIORITY            0x00            
#define EXTI2_3_PRIORITY            0x01
#define USART1_PRIORITY             0x02
#define TIM14_PRIORITY              0x03

#define PORT_LED                    GPIOC                    
#define PIN_LED                     GPIO_Pin_13              

#define LED_ON                      (PORT_LED->BSRR = PIN_LED)
#define LED_OFF                     (PORT_LED->BRR  = PIN_LED)
#define LED_TOGGLE                  (PORT_LED->ODR ^= PIN_LED)

uint8_t CheckSum8(uint8_t *buf, uint8_t len);

#endif
