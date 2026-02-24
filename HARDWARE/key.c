#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//11111111 Mini STM32开发板
//按键输入 驱动代码		   
//正点原子@11111111
//技术论坛:11111111111.com
//修改日期:2014/3/06
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 11111111111111111111111111 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//按键初始化函数 
//PA15和PC5 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// 无按键按下
}
// 典型的KEY_Scan函数正确写法（参考）
//u8 KEY_Scan(u8 mode)
//{
//    static u8 key_up = 1; // 按键松开标志
//    if(mode) key_up = 1;  // 连按模式

//    if(key_up && (KEY0 == 0 || KEY1 == 0 || WKUP_PRES == 1)) // WKUP是高电平触发！
//    {
//        delay_ms(10); // 防抖
//        key_up = 0;
//        if(KEY0 == 0)      return KEY0_PRES;
//        else if(KEY1 == 0) return KEY1_PRES;
//        else if(WKUP_PRES == 1) return WKUP_PRES; // 确认WKUP的触发条件是1（高电平）
//    }
//    else if(KEY0 == 1 && KEY1 == 1 && WKUP_PRES == 0)
//    {
//        key_up = 1;
//    }
//    return 0; // 无按键
//}




//#include <stdint.h>
//#include "stm32f10x.h"
//#include "systick.h"

//#include "key.h"
//#include "delay.h"
///* 按键GPIO结构体 */
//typedef struct
//{
//    GPIO_TypeDef *gpio;
//    uint16_t pin;
//} Key_GPIO_t;

///* 按键GPIO列表配置 */
//static Key_GPIO_t g_gpioList[] = 
//{
//    {GPIOA, GPIO_Pin_0},    // key1
//    {GPIOA, GPIO_Pin_15},   // key2
//    {GPIOC, GPIO_Pin_5}     // key3
//};

//#define KEY_NUM_MAX (sizeof(g_gpioList) / sizeof(g_gpioList[0]))

///* 按键状态枚举 */
////typedef enum
////{
////    KEY_RELEASE = 0,    // 释放松开
////    KEY_CONFIRM,        // 消抖确认
////    KEY_SHORTPRESS,     // 短按
////    KEY_LONGPRESS       // 长按
////} KEY_STATE;

/////* 按键时间定义（毫秒） */
////#define CONFIRM_TIME     10     // 按键消抖时间窗10ms
////#define LONGPRESS_TIME   1000   // 长按时间窗1000ms

/////* 按键信息结构体 */
////typedef struct
////{
////    KEY_STATE keyState;
////    uint32_t prvSysTime;    // 标准库使用32位时间戳
////} Key_Info_t;

////static Key_Info_t g_keyInfo[KEY_NUM_MAX];

///**
//***********************************************************
//* @brief 使能GPIO时钟（标准库版本）
//* @param gpio: GPIO端口
//***********************************************************
//*/
//static void GPIO_ClockEnable(GPIO_TypeDef* gpio)
//{
//    if (gpio == GPIOA) {
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    } else if (gpio == GPIOB) {
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    } else if (gpio == GPIOC) {
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//    } else if (gpio == GPIOD) {
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
//    } else if (gpio == GPIOE) {
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
//    }
//}

///**
//***********************************************************
//* @brief 按键硬件初始化（标准库版本）
//***********************************************************
//*/
//void KEY_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    
//    for (uint8_t i = 0; i < KEY_NUM_MAX; i++)
//    {
//        /* 使能GPIO时钟 */
//        GPIO_ClockEnable(g_gpioList[i].gpio);
//        
//        /* 配置GPIO为上拉输入模式 */
//        GPIO_InitStructure.GPIO_Pin = g_gpioList[i].pin;
//        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入模式
//        GPIO_Init(g_gpioList[i].gpio, &GPIO_InitStructure);
//        
//        /* 初始化按键状态信息 */
////        g_keyInfo[i].keyState = KEY_RELEASE;
////        g_keyInfo[i].prvSysTime = 0;
//    }
//    
//    /* 特别注意：PA15默认用于JTAG，需要禁用JTAG功能 */
//    // 方法1：禁用JTAG，保留SWD（推荐）
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
//    
//    // 或者方法2：完全禁用JTAG和SWD（不推荐，会失去调试功能）
//    // GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
//}


//static uint8_t KeyScan(uint8_t keyIndex)
//{
//	uint64_t curSysTime;
//	uint8_t keyPress;
//	
//	keyPress = GPIO_ReadInputDataBit(g_gpioList[keyIndex].gpio, g_gpioList[keyIndex].pin);

//	switch (g_keyInfo[keyIndex].keyState)
//	{
//		case KEY_RELEASE:                                          //  释放状态：判断有无按键按下
//			if (!keyPress)                                         //  有按键按下
//			{ 
//				g_keyInfo[keyIndex].keyState = KEY_CONFIRM;        //  获取系统运行时间
//				g_keyInfo[keyIndex].prvSysTime = GetSysRunTime();
//			}
//			break;
//			
//		case KEY_CONFIRM:
//			if (!keyPress)
//			{
//				curSysTime = GetSysRunTime();
//				if (curSysTime - g_keyInfo[keyIndex].prvSysTime > CONFIRM_TIME) //  超过时间窗，切换到短按
//				{
//					g_keyInfo[keyIndex].keyState = KEY_SHORTPRESS;
//				}
//			}
//			else
//			{
//				g_keyInfo[keyIndex].keyState = KEY_RELEASE;
//			}
//			break;
//			
//		case KEY_SHORTPRESS:           //  短按状态：继续判定是短按，还是长按
//			if (keyPress)
//			{
//				g_keyInfo[keyIndex].keyState = KEY_RELEASE;
//				return (keyIndex + 1); //  返回按键码值，三个按键短按对应0x01, 0x02, 0x03
//			}
//			else
//			{
//				curSysTime = GetSysRunTime();
//				if (curSysTime - g_keyInfo[keyIndex].prvSysTime > LONGPRESS_TIME)
//				{	
//					g_keyInfo[keyIndex].keyState = KEY_LONGPRESS;
//				}
//			}
//			break;
//		case KEY_LONGPRESS:
//			if (keyPress)
//			{
//				g_keyInfo[keyIndex].keyState = KEY_RELEASE;
//				return (keyIndex + 0x81); //返回按键码值，三个按键长按对应0x81, 0x82, 0x83
//			}
//			break;
//		default:
//			g_keyInfo[keyIndex].keyState = KEY_RELEASE;
//			break;
//	}
//	return 0;
//}


//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;
//		else if(KEY1==0)return KEY1_PRES;
//		else if(WK_UP==1)return WKUP_PRES; 
//	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
//	return 0;// 无按键按下
//}



/**
***********************************************************
* @brief 获取按键码值
* @param
* @return 三个按键码值，短按0x01 0x02 0x03，
			长按0x81 0x82 0x83，没有按下为0
***********************************************************
*/
//uint8_t GetKeyVal(void)
//{
//	uint8_t res = 0;

//	for (uint8_t i = 0; i < KEY_NUM_MAX; i++)
//	{
//		res = KeyScan(i);
//		if (res != 0)
//		{
//			break;
//		}
//	}
//	return res;
//}




