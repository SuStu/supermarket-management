#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//11111111 miniSTM32开发板
//LED驱动代码	   
//正点原子@11111111
//技术论坛:11111111111.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 11111111111111111111111111 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
//void LED_Init(void)
//{
// 
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//	GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
//	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
//	GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
//}




 
#include <stdint.h>
#include "stm32f10x.h"
#include "led.h"
/* LED GPIO结构体 */
typedef struct
{
    GPIO_TypeDef *gpio;
    uint16_t pin;
} Led_GPIO_t;

/* 注意：这里应该定义LED的GPIO，而不是按键的GPIO
   根据之前的代码，LED可能是PA8和PD2
   我根据常见的STM32开发板配置修改如下 */
static Led_GPIO_t g_gpioList[] =
{
    {GPIOA, GPIO_Pin_8},   // LED1 - PA8
    {GPIOD, GPIO_Pin_2}    // LED2 - PD2
};

#define LED_NUM_MAX (sizeof(g_gpioList) / sizeof(g_gpioList[0]))

/* 如果需要使用之前的GPIO配置，请修改上面的数组为：
static Led_GPIO_t g_gpioList[] =
{
    {GPIOA, GPIO_Pin_0},    // LED1 - PA0
    {GPIOA, GPIO_Pin_15},   // LED2 - PA15
    {GPIOC, GPIO_Pin_5}     // LED3 - PC5
};
*/

/**
***********************************************************
* @brief 使能GPIO时钟（标准库版本）
* @param gpio: GPIO端口
***********************************************************
*/
static void GPIO_ClockEnable(GPIO_TypeDef* gpio)
{
    if (gpio == GPIOA) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    } else if (gpio == GPIOB) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    } else if (gpio == GPIOC) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    } else if (gpio == GPIOD) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    } else if (gpio == GPIOE) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
}

/**
***********************************************************
* @brief LED硬件初始化（标准库版本）
***********************************************************
*/
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    for (uint8_t i = 0; i < LED_NUM_MAX; i++)
    {
        /* 使能GPIO时钟 */
        GPIO_ClockEnable(g_gpioList[i].gpio);
        
        /* 配置GPIO为推挽输出模式 */
        GPIO_InitStructure.GPIO_Pin = g_gpioList[i].pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 低速输出
        GPIO_Init(g_gpioList[i].gpio, &GPIO_InitStructure);
        
        
        GPIO_SetBits(g_gpioList[i].gpio, g_gpioList[i].pin);
    }
    
    /* 特别注意：如果使用了PA15作为LED，需要禁用JTAG功能 */
    for (uint8_t i = 0; i < LED_NUM_MAX; i++)
    {
        if (g_gpioList[i].gpio == GPIOA && g_gpioList[i].pin == GPIO_Pin_15)
        {
            /* PA15默认用于JTAG，需要重映射为普通IO */
           GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
            break;
        }
    }
}

/**
***********************************************************
* @brief 点亮LED
* @param ledNo: LED编号，0~LED_NUM_MAX-1
***********************************************************
*/
void TurnOnLed(uint8_t ledNo)
{
    if (ledNo >= LED_NUM_MAX)
    {
        return;
    }
    
    /* 点亮LED：根据硬件连接，可能是高电平或低电平点亮
       这里假设高电平点亮（推挽输出模式） */
    GPIO_ResetBits(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
}

/**
***********************************************************
* @brief 熄灭LED
* @param ledNo: LED编号，0~LED_NUM_MAX-1
***********************************************************
*/
void TurnOffLed(uint8_t ledNo)
{
    if (ledNo >= LED_NUM_MAX)
    {
        return;
    }
    
    /* 熄灭LED：根据硬件连接，可能是低电平熄灭 */
    GPIO_SetBits(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
}

/**
***********************************************************
* @brief LED状态取反
* @param ledNo: LED编号，0~LED_NUM_MAX-1
***********************************************************
*/
void ToggleLed(uint8_t ledNo)
{
    if (ledNo >= LED_NUM_MAX)
    {
        return;
    }
    
    /* 读取当前状态并取反 */
    if (GPIO_ReadOutputDataBit(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin))
    {
        GPIO_ResetBits(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
    }
    else
    {
        GPIO_SetBits(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
    }
}
