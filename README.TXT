实验器材:
	MiniSTM32F103开发板
	
实验目的:
	学习GPIO作为输入的使用
	
硬件资源:
	1,LED1(连接在PA8),LED2(连接在PD2)
	2,按键KEY0(PC5)/KEY1(PA15)/KEY_UP(PA0,也称之为WK_UP)
	
实验现象:
	本实验通过开发板上载有的3个按钮（KEY_UP、KEY0、KEY1），来控制板上的2个LED（LED1和LED2），
	其中KEY0控制LED1，按一次亮，再按一次，就灭。KEY1控制LED2，效果同KEY0。KEY_UP则同时控制
	LED1和LED2，按一次，他们的状态就翻转一次。
	
注意事项:
	板子上LED1对应程序的LED0.
        板子上LED2对应程序的LED1.