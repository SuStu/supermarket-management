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


typedef struct
{
    uint8_t run;                // 调度标志
    uint16_t timCount;          // 时间片计数值
    uint16_t timRload;          // 时间片重载值
    void (*pTaskFuncCb)(void);  // 函数指针
} TaskComps_t;

/* 简化任务表，只保留HMI任务 */
static TaskComps_t g_taskComps[] = 
{
    {0, 10,10, HmiTask},  // 10ms执行一次
//	{0,20,20,MQ2_Task},
	{0,20,20,MFRC522Task},
	{0,200,200,Usb2ComTask},
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
	Delay_Init();	    	 //延时函数初始化	  
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	KEY_Init();          	//初始化与按键连接的硬件接口
    Usb2ComDrvInit();       // USB转串口驱动初始化
    MFRC522_Init();
	MQ2_Init();
}

static void AppInit(void)
{
   TaskScheduleCbReg(TaskScheduleCb);
}



 int main(void)
 {	
    DrvInit(); 
	AppInit();
	while(1)
	{
		TaskHandler();
	}
	 
}
