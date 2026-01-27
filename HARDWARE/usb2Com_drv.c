#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "led.h"
#include "usb2Com_drv.h"
/**
***********************************************************************
包格式：帧头0  帧头1  数据长度  功能字   LED编号  亮/灭  异或校验数据
        0x55   0xAA    0x03      0x06     0x00     0x01      0xFB
***********************************************************************
*/
#define FRAME_HEAD_0        0x55  
#define FRAME_HEAD_1        0xAA
#define CTRL_DATA_LEN       3     //数据域长度
#define PACKET_DATA_LEN     (CTRL_DATA_LEN + 4)  //包长度
#define FUNC_DATA_IDX       3     //功能字数组下标
#define LED_CTRL_CODE       0x06  //功能字

#define MAX_BUF_SIZE        20
static uint8_t g_rcvDataBuf[MAX_BUF_SIZE];
static bool g_pktRcvd = false;

typedef struct
{
    uint8_t ledNo;
    uint8_t ledState;
} LedCtrlInfo_t;

/**
***********************************************************
* @brief USART1 GPIO初始化
* @param
* @return 
***********************************************************
*/

static void Usb2ComGpioInit(void)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOA和USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    // USART1_TX -> PA.9 复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // USART1_RX -> PA.10 浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
***********************************************************
* @brief USART1初始化
* @param baudRate: 波特率
* @return 
***********************************************************
*/
static void Usb2ComUartInit(uint32_t baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    
    // USART1配置
    USART_InitStructure.USART_BaudRate = baudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART1, &USART_InitStructure);
    
    // 使能USART1接收空闲中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    
    // 使能USART1
    USART_Cmd(USART1, ENABLE);
}

/**
***********************************************************
* @brief DMA初始化
* @param
* @return 
***********************************************************
*/
static void Usb2ComDmaInit(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    // 使能DMA1时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    // DMA1 Channel5配置 (USART1_RX)
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)g_rcvDataBuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = MAX_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    
    // 使能DMA通道5
	DMA_Cmd(DMA1_Channel5, ENABLE);
    // USART1 DMA接收使能
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}

/**
***********************************************************
* @brief 中断优先级配置
* @param
* @return 
***********************************************************
*/
static void Usb2ComNvicInit(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // USART1中断优先级配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
***********************************************************
* @brief USB转串口硬件初始化
* @param
* @return 
***********************************************************
*/
void Usb2ComDrvInit(void)
{
    Usb2ComGpioInit();
    Usb2ComUartInit(115200);
    Usb2ComDmaInit();
    Usb2ComNvicInit();
}

/**
***********************************************************
* @brief 对数据进行异或运算
* @param data, 存储数组的首地址
* @param len, 要计算的元素的个数
* @return 异或运算结果
***********************************************************
*/
static uint8_t CalXorSum(const uint8_t *data, uint32_t len)
{
    uint8_t xorSum = 0;
    for (uint32_t i = 0; i < len; i++)
    {
        xorSum ^= data[i];
    }
    return xorSum;
}

/**
***********************************************************
* @brief LED控制处理函数
* @param ctrlData，结构体指针，传入LED的编号和状态
* @return 
***********************************************************
*/
static void CtrlLed(LedCtrlInfo_t *ctrlData)
{
    ctrlData->ledState != 0 ? TurnOnLed(ctrlData->ledNo) : TurnOffLed(ctrlData->ledNo);
}

/**
***********************************************************
* @brief USB转串口任务处理函数
* @param
* @return 
***********************************************************
*/
void Usb2ComTask(void)
{
    if (!g_pktRcvd)
    {
        return;
    }
    g_pktRcvd = false;
    
    if (g_rcvDataBuf[0] != FRAME_HEAD_0 || g_rcvDataBuf[1] != FRAME_HEAD_1)
    {
        return;
    }
    if (CalXorSum(g_rcvDataBuf, PACKET_DATA_LEN - 1) != g_rcvDataBuf[PACKET_DATA_LEN - 1])
    {
        return;
    }
    if (g_rcvDataBuf[FUNC_DATA_IDX] == LED_CTRL_CODE)
    {
        CtrlLed((LedCtrlInfo_t *)(&g_rcvDataBuf[FUNC_DATA_IDX + 1]));
    }
}

/**
***********************************************************
* @brief 串口1中断服务函数
* @param
* @return 
***********************************************************
*/
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        uint16_t receivedCount;
        
        // 清除空闲中断标志
        USART_ReceiveData(USART1);  // 读DR寄存器清除空闲中断
        
        // 停止DMA传输
        DMA_Cmd(DMA1_Channel5, DISABLE);
        
        // 获取接收到的数据长度
        receivedCount = MAX_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);
        
        // 检查是否接收到完整的数据包
        if (PACKET_DATA_LEN == receivedCount)
        {
            g_pktRcvd = true;
        }
        
        // 重新配置DMA传输
        DMA_SetCurrDataCounter(DMA1_Channel5, MAX_BUF_SIZE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
    }
}

/**
***********************************************************
* @brief printf函数默认打印输出到显示器，如果要输出到串口，
         必须重新实现fputc函数，将输出指向串口，称为重定向
* @param
* @return 
***********************************************************
*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}