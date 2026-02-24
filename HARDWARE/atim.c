#include "stm32f10x.h"
#include "atim.h"

void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef        GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

    // 开启AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // 时钟：TIM8 + PC6(TIM8_CH1) + PA7(TIM8_CH1N)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 |
                           RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOA, ENABLE);

    // PC6  TIM8_CH1（主通道）
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // PA7  TIM8_CH1N（互补通道）
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 时基配置（参数不变）
    TIM_TimeBaseStructure.TIM_Period        = arr;
    TIM_TimeBaseStructure.TIM_Prescaler     = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    // PWM1 模式（参数不变）
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_Pulse       = 0;
    TIM_OC1Init(TIM8, &TIM_OCInitStructure); // 改为TIM8

    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); // 改为TIM8
    TIM_ARRPreloadConfig(TIM8, ENABLE); // 改为TIM8

    // BDTR配置（高级定时器必须）
    TIM_BDTRInitStructure.TIM_OSSRState        = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState        = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel        = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime         = 0;
    TIM_BDTRInitStructure.TIM_Break            = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity    = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput   = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure); // 改为TIM8

    TIM_Cmd(TIM8, ENABLE); // 改为TIM8
    TIM_CtrlPWMOutputs(TIM8, ENABLE); // 改为TIM8（主输出使能，必须！）
}