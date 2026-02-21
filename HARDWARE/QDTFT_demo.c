/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "delay.h"
#include "Picture.h"
#include "QDTFT_demo.h"

// 全局变量：记录各测试函数的初始化状态（避免重复执行）
static uint8_t g_menu_init = 0;
static uint8_t g_num_init = 0;
static uint8_t g_font_init = 0;
static uint8_t g_color_init = 0;
static uint8_t g_image_init = 0;

unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

// 主菜单显示函数（只初始化一次）
void Redraw_Mainmenu(void)
{
    if(!g_menu_init) // 仅第一次进入时执行初始化
    {
        Lcd_Clear(GRAY0);
        
        Gui_DrawFont_GBK16(16,0,BLUE,GRAY0,"动动电子技术");
        Gui_DrawFont_GBK16(16,20,RED,GRAY0,"液晶测试程序");

        DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
        Gui_DrawFont_GBK16(16,40,YELLOW,GRAY0,"颜色填充测试");

        DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
        Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"文字显示测试");

        DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
        Gui_DrawFont_GBK16(16,100,RED,GRAY0,"图片显示测试");
        
        g_menu_init = 1; // 标记已初始化，后续不再执行
    }
}

// 数字测试函数（只初始化一次）
void Num_Test(void)
{
    u8 i=0;
    if(!g_num_init) // 仅第一次进入时执行初始化
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
        
        g_num_init = 1; // 标记已初始化
    }
}

// 文字测试函数（只初始化一次）
void Font_Test(void)
{
    if(!g_font_init) // 仅第一次进入时执行初始化
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
        
        g_font_init = 1; // 标记已初始化
    }
}

// 颜色测试函数（只初始化一次）
void Color_Test(void)
{
    if(!g_color_init) // 仅第一次进入时执行初始化
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
        
        g_color_init = 1; // 标记已初始化
    }
}

// 图片显示函数（只初始化一次）
// 取模方式 水平扫描 从左到右 低位在前
void showimage(const unsigned char *p) //显示40*40 QQ图片
{
    if(!g_image_init) // 仅第一次进入时执行初始化
    {
        int i,j,k; 
        unsigned char picH,picL;
        Lcd_Clear(WHITE); //清屏  
        
        for(k=0;k<4;k++)
        {
            for(j=0;j<3;j++)
            {   
                Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//坐标设置
                for(i=0;i<40*40;i++)
                {	
                    picL=*(p+i*2);	//数据低位在前
                    picH=*(p+i*2+1);				
                    LCD_WriteData_16Bit(picH<<8|picL);  						
                }	
            }
        }
        
        g_image_init = 1; // 标记已初始化
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

// TFT屏幕任务（按模式显示，无阻塞）
void QDTFT_Task(void)
{
    extern uint8_t g_screen_mode; // 引用hmitask.c中的全局变量
    LCD_LED_SET; // 背光常亮

    // 根据按键控制的模式显示对应内容
    switch(g_screen_mode)
    {
        case 0: // 主菜单
            Redraw_Mainmenu();
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
            // showimage(gImage_qq); // 需确保gImage_qq已定义
            break;
        default:
            g_screen_mode = 0;
            break;
    }
}