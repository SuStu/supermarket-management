/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
	
  /* Go to infinite loop when Hard Fault exception occurs */
		    // 在这里添加代码，查看进入硬件错误前的地址
    volatile uint32_t *pSP = (uint32_t *)__get_MSP();  // 获取堆栈指针
    
    // 这些是进入硬件错误前压入堆栈的寄存器
    volatile uint32_t r0 = pSP[0];  // R0
    volatile uint32_t r1 = pSP[1];  // R1
    volatile uint32_t r2 = pSP[2];  // R2
    volatile uint32_t r3 = pSP[3];  // R3
    volatile uint32_t r12 = pSP[4]; // R12
    volatile uint32_t lr = pSP[5];  // LR - 返回地址
    volatile uint32_t pc = pSP[6];  // PC - 程序计数器
    volatile uint32_t psr = pSP[7]; // PSR
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */

  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
