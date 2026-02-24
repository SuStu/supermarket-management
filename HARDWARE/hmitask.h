
#ifndef __HMITASK_H
#define __HMITASK_H


#include "sys.h"

extern int32_t g_fan_speed; // 声明全局风扇速度变量
int32_t get_fan_speed(void); // 获取风扇速度的函数声明
void HmiTask(void);






#endif