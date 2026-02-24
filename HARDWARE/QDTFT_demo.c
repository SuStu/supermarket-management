/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "delay.h"
#include "Picture.h"
#include "QDTFT_demo.h"
#include <stdio.h>
#include "mq2.h"
#include <string.h>
#include "hmitask.h"

// 全局变量：记录各测试函数的初始化状态（避免重复执行）
static uint8_t g_menu_init = 0;
static uint8_t g_num_init = 0;
static uint8_t g_font_init = 0;
static uint8_t g_color_init = 0;
static uint8_t g_image_init = 0;

static int32_t last_fan_speed = 0x7fffffff;


unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

// 引用MQ2全局变量
extern u8 buff[30];
extern u8 mq2_preheat_flag;

// 引用温湿度/温度上限变量
extern u8 temp;
extern u8 MAX_TEMP;
extern u8 humi;
extern u8 buff1[30];			
extern u8 buff2[30];
extern u8 buff3[30];
u8 fan_speed_buff[32] = {0}; // 初始化全0，避免残留字符

// 主菜单显示函数（只初始化一次）
void Redraw_Mainmenu(void)
{
    if(!g_menu_init) // 仅第一次进入时执行初始化
    {
        Lcd_Clear(GRAY0); // 初始清屏为灰色背景
        
        // 标题
        Gui_DrawFont_GBK16(0,5,BLUE,GRAY0,"校园超市管理系统");
        
        // 固定文本（只画一次）
        Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"环境温度:");
        Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"环境湿度:");
        Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"烟雾浓度:");
        Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"温度上限:");
        Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"通风风扇:");
        
        g_menu_init = 1; // 标记已初始化，后续不再执行
    }
}

/**
  * @brief  更新主菜单数据（仅数值变化时刷新，避免闪屏）
  * @param  无
  * @retval 无
  */
// 在 Update_Mainmenu_Data 函数中，读取风扇速度前添加保护
void Update_Mainmenu_Data(void)
{
    Gui_DrawFont_GBK16(70, 32, RED, GRAY0, (u8*)buff1);
    Gui_DrawFont_GBK16(70, 48, RED, GRAY0, (u8*)buff2);
    Gui_DrawFont_GBK16(70,80,RED, GRAY0, (u8*)buff3);
    Gui_DrawFont_GBK16(70, 64, RED, GRAY0, (u8*)buff);

    // 风扇速度：仅变化时刷新
    memset(fan_speed_buff, 0, sizeof(fan_speed_buff));
    
    // 添加保护，确保读取的值在合理范围内
    int32_t current_speed = get_fan_speed();
    
    // 限制显示范围，避免异常值导致问题
    if(current_speed > 10) current_speed = 10;
    if(current_speed < -10) current_speed = -10;
    
    if (current_speed != last_fan_speed)
    {
        if (current_speed > 0)
        {
            snprintf((char*)fan_speed_buff, sizeof(fan_speed_buff)-1, "%03d", current_speed);
        }
        else if (current_speed < 0)
        {
            snprintf((char*)fan_speed_buff, sizeof(fan_speed_buff)-1, "%03d", current_speed);
        }
        else
        {
            snprintf((char*)fan_speed_buff, sizeof(fan_speed_buff)-1, "000");
        }
        Gui_DrawFont_GBK16(70, 96, RED, GRAY0, fan_speed_buff);
        last_fan_speed = current_speed;
    }
}

// 数字测试函数（只初始化一次）
void Num_Test(void)
{
    u8 i=0;
    if(!g_num_init) 
    {
        Lcd_Clear(GRAY0);
        Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
        delay_ms(1000);
        Lcd_Clear(GRAY0);

        for(i=0;i<10;i++)
        {
            Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i]);
            delay_ms(100);
        }
        
        g_num_init = 1; 
    }
}

// 文字测试函数（只初始化一次）
void Font_Test(void)
{
    if(!g_font_init) 
    {
        Lcd_Clear(GRAY0);
        Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"文字显示测试");

        delay_ms(1000);
        Lcd_Clear(GRAY0);
        Gui_DrawFont_GBK16(16,5,YELLOW,GRAY0,"动动电子技术");
        Gui_DrawFont_GBK16(16,30,BLUE,GRAY0,"专注液晶批发");
        Gui_DrawFont_GBK16(16,55,RED,GRAY0, "全程技术支持");
        Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Tel:11239000975");
        Gui_DrawFont_GBK16(0,105,RED,GRAY0, "QQ:1234656669");    
        delay_ms(1800);
        
        g_font_init = 1; 
    }
}

// 颜色测试函数（只初始化一次）
void Color_Test(void)
{
    if(!g_color_init) 
    {
        Lcd_Clear(GRAY0);
        Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
        delay_ms(200);

        // 只执行一次颜色切换，取消while循环
        Lcd_Clear(WHITE);
        delay_ms(300);
        Lcd_Clear(BLACK);
        delay_ms(300);
        Lcd_Clear(RED);
        delay_ms(300);
        Lcd_Clear(GREEN);
        delay_ms(300);
        Lcd_Clear(BLUE);
        delay_ms(300);
        
        g_color_init = 1; 
    }
}

// 图片显示函数（只初始化一次）
void showimage(const unsigned char *p) 
{
    if(!g_image_init) 
    {
        int i,j,k; 
        unsigned char picH,picL;
        Lcd_Clear(WHITE); //清屏  
        
        for(k=0;k<4;k++)
        {
            for(j=0;j<3;j++)
            {   
                Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		
                for(i=0;i<40*40;i++)
                {	
                    picL=*(p+i*2);	
                    picH=*(p+i*2+1);				
                    LCD_WriteData_16Bit(picH<<8|picL);  						
                }	
            }
        }
        
        g_image_init = 1; 
    }
}

// 重置所有测试函数的初始化状态（切换显示模式时调用）
void ResetScreenInitFlag(void)
{
    g_menu_init = 0;
    g_num_init = 0;
    g_font_init = 0;
    g_color_init = 0;
    g_image_init = 0;
}

// TFT屏幕任务（按模式显示，无阻塞，全程常亮）
void QDTFT_Task(void)
{
	
    extern uint8_t g_screen_mode;
    // 背光初始化（只执行一次）
    static u8 backlight_init = 0;
    if(!backlight_init)
    {
        LCD_LED_SET; // 背光常亮
        backlight_init = 1;
    }

    // 根据模式显示对应内容（全程正常显示，无黑屏）
    switch(g_screen_mode)
    {
        case 0: // 主菜单（默认）
            Redraw_Mainmenu();
            Update_Mainmenu_Data();
            break;
        case 1: // 颜色测试
            Color_Test();
            break;
        case 2: // 数字测试
            Num_Test();
            break;
        case 3: // 文字测试
            Font_Test();
            break;
        case 4: // 图片测试（可选扩展）
            // showimage(gImage_qq); 
            break;
        default:
            g_screen_mode = 0;
            break;
    }
}