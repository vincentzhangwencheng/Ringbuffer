/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:49:37
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-10-10 10:12:49
 */
#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"

#define SECOND(n)       ((uint32_t)(1000UL*(n)))
#define MINUTE(n)       (SECOND(60)*(n))
#define HOUR(n)         (MINUTE(60)*(n))
#define DAY(n)          (HOUR(24)*(n))

#define TIMER_PSC       48
#define TIMER_PERIOD    1000

uint32_t millis(void);
void TIM14_Init(uint16_t arr,uint16_t psc);

#endif
