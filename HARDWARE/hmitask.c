#include "hmitask.h"
#include "key.h"
#include "led.h"
#include "delay.h"

#define MAX_SPEED   10
#define MIN_SPEED   1
#define PWM_STEP    1

extern u8 MAX_TEMP;
extern u8 temp;

#define TEMP_MIN 10
#define TEMP_MAX 50

uint8_t g_screen_mode = 0;

void HmiTask(void)
{
    u8 key = KEY_Scan(0);  
    
    // 只处理按键，风扇交给单独的atk_fan_task
    switch(key)
    {
        case KEY0_PRES:
            if(MAX_TEMP > TEMP_MIN)
            {
                MAX_TEMP -= PWM_STEP;  
            }
            break;
        case KEY1_PRES:
            if(MAX_TEMP < TEMP_MAX)
            {
                MAX_TEMP += PWM_STEP;  
            }
            break;
        case WKUP_PRES:
            LED1 = !LED1;  
            break;
        default:
            break;
    }
}