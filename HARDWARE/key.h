//#ifndef __KEY_H
//#define __KEY_H	 
//#include "sys.h"
////////////////////////////////////////////////////////////////////////////////////	 
////本程序只供学习使用，未经作者许可，不得用于其它任何用途
////11111111 miniSTM32开发板
////按键驱动代码	   
////正点原子@11111111
////技术论坛:11111111111.com
////修改日期:2012/9/3
////版本：V1.0
////版权所有，盗版必究。
////Copyright(C) 11111111111111111111111111 2009-2019
////All rights reserved									  
////////////////////////////////////////////////////////////////////////////////////   	 


////#define KEY0 PCin(5)   	
////#define KEY1 PAin(15)	 
////#define WK_UP  PAin(0)	 
// 

//#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
// 

//#define KEY0_PRES	1		//KEY0  
//#define KEY1_PRES	2		//KEY1 
//#define WKUP_PRES	3		//WK_UP  

//void KEY_Init(void);//IO初始化
//u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
//#endif


#ifndef _KEY_H
#define _KEY_H

#include <stdint.h>
#include "sys.h"
#define KEY1_SHORT_PRESS   0X01
#define KEY1_LONG_PRESS    0X81
#define KEY2_SHORT_PRESS   0X02
#define KEY2_LONG_PRESS    0X82
#define KEY3_SHORT_PRESS   0X03
#define KEY3_LONG_PRESS    0X83


#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP

u8 KEY_Scan(u8 mode);


/**
***********************************************************
* @brief 按键硬件初始化
* @param
* @return 
***********************************************************
*/
void KEY_Init(void);

/**
***********************************************************
* @brief 获取按键码值
* @param
* @return 三个按键码值，短按0x01 0x02 0x03，
			长按0x81 0x82 0x83，没有按下为0
***********************************************************
*/
uint8_t GetKeyVal(void);

#endif
