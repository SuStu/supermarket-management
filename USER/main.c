#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "hmitask.h"
#include <stdio.h>
#include "systick.h"
#include "usb2Com_drv.h"
#include "MFRC522.h"
#include "mq2.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "dht11.h"
#include "atk_fan.h"
#include "atim.h"
#include "buzz.h"

typedef struct
{
    uint8_t run;                // 调度标志
    uint16_t timCount;          // 时间片计数值
    uint16_t timRload;          // 时间片重载值
    void (*pTaskFuncCb)(void);  // 函数指针
} TaskComps_t;

/* 修正任务表注释（和实际数值匹配） */
static TaskComps_t g_taskComps[] = 
{
    {0,50,50,QDTFT_Task},       // 10ms 屏幕任务（高频刷新，更稳定）
    {0,100,100, HmiTask},         // 50ms 按键任务
    {0,100,100,DHT11_Task},     // 200ms 温湿度读取
    {0,500,500,BUZZ_Task},      // 200ms 蜂鸣器任务
    {0,200,200,Usb2ComTask},    // 200ms 串口任务
};

#define TASK_NUM_MAX   (sizeof(g_taskComps) / sizeof(g_taskComps[0]))

static void TaskHandler(void)
{
    for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
    {
        if (g_taskComps[i].run)
        {
            g_taskComps[i].run = 0;
            if (g_taskComps[i].pTaskFuncCb != NULL)
            {
                g_taskComps[i].pTaskFuncCb();
            }
        }
    }
}

static void TaskScheduleCb(void)
{
    for (uint8_t i = 0; i < TASK_NUM_MAX; i++)
    {
        if (g_taskComps[i].timCount > 0)
        {
            g_taskComps[i].timCount--;
            if (g_taskComps[i].timCount == 0)
            {
                g_taskComps[i].run = 1;
                g_taskComps[i].timCount = g_taskComps[i].timRload;
            }
        }
    }
}

static void DrvInit(void)
{
    SystickInit();
    Delay_Init();	    	//延时函数初始化	  
    LED_Init();		  	 	//初始化与LED连接的硬件接口
    KEY_Init();          	//初始化与按键连接的硬件接口
    Usb2ComDrvInit();       // USB转串口驱动初始化
    Lcd_Init();            // LCD初始化
    DHT11_Init();          // DHT11初始化
    atk_fan_init();        // 风扇初始化
    BUZZ_Init();           // 蜂鸣器初始化
}

static void AppInit(void)
{
   TaskScheduleCbReg(TaskScheduleCb);
}



// 在 main 函数开始处添加
int main(void)
{
    DrvInit(); 
    AppInit();
    
    while(1)
    {
        TaskHandler();
    }
}