#include "hmitask.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "QDTFT_demo.h" // 引入重置函数声明

// 定义全局变量记录屏幕显示状态（用于按键切换显示）
uint8_t g_screen_mode = 0; // 0:主菜单 1:颜色测试 2:数字测试 3:文字测试

void HmiTask(void)
{
    u8 t = 0;
    // 改为支持连按模式（mode=1），提高按键响应率
    t = KEY_Scan(1);		

    switch(t)				 
    {				 
        case KEY0_PRES:
            LED0 = !LED0;
            // KEY0切换屏幕显示模式
            ResetScreenInitFlag(); // 重置初始化标志，让新模式重新绘制
            g_screen_mode = (g_screen_mode + 1) % 4;
            break;
        case KEY1_PRES:
            LED1 = !LED1;
            break;
        case WKUP_PRES:				
            LED0 = !LED0;
            LED1 = !LED1;
            // WK_UP直接回到主菜单
            ResetScreenInitFlag(); // 重置初始化标志
            g_screen_mode = 0;
            break;	
        default:
            break;
    } 
}