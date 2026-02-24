#include "mq2.h"
#include "adcx.h"  // 引入现成的ADC驱动
#include "delay.h"
#include <stdio.h>
// 全局变量（仅保留必要的）
float ppm;
u16 value;
u8 buff[30];
float R0 = 0.0f;  // 动态校准的基准电阻
u8 mq2_preheat_flag = 0; // 预热完成标志

/**
  * @brief  MQ2传感器初始化
  * @param  无
  * @retval 无
  */
void MQ2_Init(void)
{
    #if MODE
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        
        // 初始化AO引脚为模拟输入
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
        GPIO_Init(GPIOA, &GPIO_InitStructure);			
        
        // 调用现成的ADC初始化函数
        ADCx_Init();
    }
    #else
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        
        // 初始化DO引脚为上拉输入
        RCC_APB2PeriphClockCmd(MQ2_DO_GPIO_CLK, ENABLE );	
        GPIO_InitStructure.GPIO_Pin = MQ2_DO_GPIO_PIN;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			
        GPIO_Init(MQ2_DO_GPIO_PORT, &GPIO_InitStructure);			
    }
    #endif
}

/**
  * @brief  校准R0（洁净空气下的基准电阻）
  * @param  无
  * @retval 无
  */
void MQ2_Calibrate_R0(void)
{
    if(R0 == 0.0f) // 仅校准一次
    {
        float tempData = 0;
        // 多次采样取平均，提升校准精度
        for (uint8_t i = 0; i < 50; i++)
        {
            tempData += ADC_GetValue(ADC_CHANNEL, 10);
            delay_ms(10);
        }
        tempData /= 50;
        
        // 计算洁净空气下的R0
        float Vol = (tempData * 5.0f) / 4096.0f;
        R0 = (5.0f - Vol) / (Vol * 0.5f);
        
        // 防止R0为0导致计算异常
        if(R0 < 0.1f) R0 = 5.0f;
    }
}

/**
  * @brief  获取MQ2 ADC原始值（多次平均）
  * @param  无
  * @retval ADC平均值
  */
uint16_t MQ2_GetData(void)
{
    #if MODE
    uint32_t  tempData = 0;
    for (uint8_t i = 0; i < MQ2_READ_TIMES; i++)
    {
        tempData += ADC_GetValue(ADC_CHANNEL, 10);
        delay_ms(5);
    }
    tempData /= MQ2_READ_TIMES;
    return (uint16_t)tempData;
    #else
    // DO模式：返回高低电平（0/1）
    uint16_t tempData;
    tempData = !GPIO_ReadInputDataBit(MQ2_DO_GPIO_PORT, MQ2_DO_GPIO_PIN);
    return tempData;
    #endif
}

/**
  * @brief  计算MQ2烟雾浓度PPM值
  * @param  无
  * @retval PPM浓度值
  */
float MQ2_GetData_PPM(void)
{
    #if MODE
    // 先校准R0
    if(R0 == 0.0f) MQ2_Calibrate_R0();
    
    float tempData = 0;
    for (uint8_t i = 0; i < MQ2_READ_TIMES; i++)
    {
        tempData += ADC_GetValue(ADC_CHANNEL, 10);
        delay_ms(2);
    }
    tempData /= MQ2_READ_TIMES;
    
    // ADC值转电压
    float Vol = (tempData * 5.0f) / 4096.0f;
    // 计算传感器电阻RS
    float RS = (5.0f - Vol) / (Vol * 0.5f);
    // MQ2灵敏度公式（优化参数，提升响应）
    //ppm = pow((10.0f * R0 / RS), 0.7f); 
    ppm = pow((10.0f * R0 / RS), 1.2f); // 临时放大响应，方便演示
    // 限制PPM范围，避免异常值
    if(ppm > 1000) ppm = 1000;
    if(ppm < 0.1f) ppm = 0.0f;
    
    return ppm;
    #endif
    return 0;
}

/**
  * @brief  MQ2任务函数（500ms执行一次）
  * @param  无
  * @retval 无
  */
void MQ2_Task(void)
{
    static uint32_t preheat_cnt = 0;
    preheat_cnt++;

    // 每次先清空buff，避免残留旧字符
    memset(buff, 0, sizeof(buff));

    if (preheat_cnt > 20) // 预热完成
    {
        mq2_preheat_flag = 1;
        value = MQ2_GetData()*100/4095;
        //ppm = MQ2_GetData_PPM();
        // 只显示ppm，例如 "16ppm"
        sprintf((char*)buff, "%d", value);
    }
    else
    {
        // 显示倒计时，例如 "预热:8s"
        sprintf((char*)buff, "预热:%ds", 10 - preheat_cnt/2);
    }
}