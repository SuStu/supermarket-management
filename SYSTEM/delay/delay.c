#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include "stm32f10x.h"
#include "delay.h"
static uint32_t g_fac_us = 0;  // us延时倍乘数

/**
***********************************************************
* @brief DWT初始化配置
* @param
* @return 
***********************************************************
*/
void Delay_Init(void) 
{
 // 获取系统时钟频率
    SystemCoreClockUpdate();
    
    // 计算us延时系数 (假设72MHz: 72次循环/微秒)
    g_fac_us = SystemCoreClock / 1000000;
    
    // 配置DWT（只在初始化时配置）
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

/**
***********************************************************
* @brief 微秒级延时函数
* @param nUs，最大延时时间( 2^32 / 内核主频 ) * 10^6 us 
* @return 
***********************************************************
*/
void delay_us(uint32_t us)
{
    uint32_t tickStart;
    uint32_t tickDelta;
    
    // 修复：移除关中断代码，避免影响SysTick中断
    tickStart = DWT->CYCCNT;
    tickDelta = us * g_fac_us;
    
    // 等待（DWT计数不受中断影响）
    while ((DWT->CYCCNT - tickStart) < tickDelta);
}

/**
***********************************************************
* @brief 毫秒级延时函数
* @param nMs，延时时间n毫秒
* @return 
***********************************************************
*/
void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
        delay_us(1000);
    }
}


#endif 








































