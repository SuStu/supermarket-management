#ifndef __ATIM_H
#define __ATIM_H

#include "stm32f10x.h"


#define ATIM_TIMX_CPLM             TIM1
#define ATIM_TIMX_CPLM_CHY          TIM_Channel_1



void atk_fan_init(void);
void atk_fan_stop(void);
void atk_fan_dir(uint8_t para);
void atk_fan_set_speed(uint16_t para);
void atk_fan_pwm_set(int32_t speed);
void atk_fan_task(void);
int32_t get_fan_speed(void);
#endif