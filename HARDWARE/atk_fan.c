#include "atk_fan.h"
#include "atim.h"
#include "delay.h"
#include <stdlib.h>

#define PWM_ARR    8 - 1
#define PWM_PSC    72 - 1
#define FAN_MAX_VAL 10
#define FAN_MIN_VAL 1

static int32_t g_fan_speed = 0;
static uint8_t last_temp_status = 0;
extern u8 temp;
extern u8 MAX_TEMP;

void atk_fan_init(void)
{
    atim_timx_cplm_pwm_init(PWM_ARR, PWM_PSC); 
    atk_fan_stop();
    
    // 禁用TIM8所有中断，避免抢占SysTick
    NVIC_DisableIRQ(TIM8_CC_IRQn);
    NVIC_DisableIRQ(TIM8_UP_IRQn);
    NVIC_DisableIRQ(TIM8_TRG_COM_IRQn);
    NVIC_DisableIRQ(TIM8_BRK_IRQn);
}

void atk_fan_stop(void)
{
    TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Disable);
    TIM_CCxNCmd(TIM8, TIM_Channel_1, TIM_CCxN_Disable);
    TIM8->CCR1 = 0;
    g_fan_speed = 0;
}

void atk_fan_set_speed(uint16_t target_val)
{
    if(target_val > FAN_MAX_VAL) target_val = FAN_MAX_VAL;
    if(target_val < FAN_MIN_VAL) target_val = 0;
    TIM8->CCR1 = target_val;
}

void atk_fan_dir(uint8_t para)
{
    atk_fan_stop();
    delay_ms(10);
    
    if(para == 0)
    {
        TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Enable);
    }
    else
    {
        TIM_CCxNCmd(TIM8, TIM_Channel_1, TIM_CCxN_Enable);
    }
}

// 风扇任务单独拆分，1s执行一次，减少干扰
void atk_fan_task(void)
{
    uint8_t current_temp_status = (temp > MAX_TEMP);
    if(current_temp_status != last_temp_status)
    {
        g_fan_speed = current_temp_status ? 10 : 0;
        if(g_fan_speed > 0)
        {
            atk_fan_dir(0);
            atk_fan_set_speed(g_fan_speed);
        }
        else
        {
            atk_fan_stop();
        }
        last_temp_status = current_temp_status;
    }
}

int32_t get_fan_speed(void)
{
    return g_fan_speed;
}