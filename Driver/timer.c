/*
 * @version: V1.0
 * @Author: vincentzhang
 * @Date: 2020-08-28 12:49:36
 * @LastEditors: vincentzhang
 * @LastEditTime: 2020-10-16 13:00:36
 */
#include "timer.h"

uint32_t Millis;

/**
 * @name: millis
 * @description: none
 * @param {type} none
 * @return {uint32_t} m
 */
uint32_t millis(void)
{
    uint32_t m;

    TIM_ITConfig(TIM14, TIM_IT_Update, DISABLE); //TIM IT enable
    m = Millis;
    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE); //TIM IT disable

    return m;
}

/**
 * @name: TIM14_Init
 * @description: none
 * @param {uint16_t, uint16_t} arr, psc
 * @return {type} none
 */
void TIM14_Init(uint16_t arr, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr - 1;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;					//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);			//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE); //使能指定的TIM14中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;   //TIM14中断
	NVIC_InitStructure.NVIC_IRQChannelPriority = TIM14_PRIORITY; //优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	   //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);					   //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM14, ENABLE); //使能TIMx外设
}

/**
 * @name: TIM14_IRQHandler
 * @description: none
 * @param {type} none
 * @return {type} none
 */
void TIM14_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
	{
		TIM_ClearITPendingBit(TIM14, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
		Millis++;
	}
}
