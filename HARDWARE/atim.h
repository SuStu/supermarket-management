/**
 ****************************************************************************************************
 * @file        atim.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       高级定时器 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 M48Z-M3最小系统板STM32F103版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATIM_H
#define __ATIM_H

#include "stm32f10x.h"



// 宏定义（需要根据实际硬件配置，这里沿用原HAL库的宏命名）
// 请根据你的硬件配置修改以下宏定义
#define ATIM_TIMX_CPLM             		TIM8
#define ATIM_TIMX_CPLM_CLK_ENABLE()    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE)

#define ATIM_TIMX_CPLM_CHY_GPIO_PORT  	GPIOC
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN   	GPIO_Pin_6
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE()  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)

#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT  GPIOA
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN   GPIO_Pin_7
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE() RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define ATIM_TIMX_CPLM_CHY           TIM_Channel_1




void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc);

#endif

















