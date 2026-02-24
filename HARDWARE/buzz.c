#include "buzz.h"
#include "delay.h"

extern u8 temp;
extern u8 MAX_TEMP;

#define BUZZ_PIN    GPIO_Pin_15
#define BUZZ_PORT   GPIOB

static uint8_t buzz_status = 1; // 1=关闭，0=打开

void BUZZ_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    // 配置为推挽输出，速度降低到2MHz，减少EMI干扰
    GPIO_InitStructure.GPIO_Pin  = BUZZ_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 降低速度，减少干扰
    GPIO_Init(BUZZ_PORT, &GPIO_InitStructure);
    
    GPIO_SetBits(BUZZ_PORT, BUZZ_PIN); // 初始关闭
    buzz_status = 1;
}

// 纯GPIO操作，无任何屏幕/全局变量操作
void BUZZ_Task(void)
{
    uint8_t over_temp = (temp > MAX_TEMP);
    if(over_temp != buzz_status)
    {
        if(over_temp)
        {
            GPIO_ResetBits(BUZZ_PORT, BUZZ_PIN);
        }
        else
        {
            GPIO_SetBits(BUZZ_PORT, BUZZ_PIN);
        }
        buzz_status = over_temp;
    }
}