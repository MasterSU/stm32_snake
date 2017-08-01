#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "timer.h"
#include "usart.h"
#include "snake.h"  
u16 count=0;
vu8 key=0;
/************************************************
 ALIENTEK 战舰STM32F103开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 	
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
		count++;
		
		if(count>=speed)
		{
			count=0;
			
			move();
			
		}
	}
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		
	}
}

 int main(void)
 {	 
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	ADC1_Init();
	KEY_Init();
	LCD_Init();	
	initsnake();
	TIM2_Int_Init(499,7199);
	TIM3_Int_Init(1,71999);
  while(1) 
	{		 
		key=KEY_Scan(0);
		if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
					snake_direction(on);
					break;
				case KEY2_PRES:	//控制LED0翻转
					snake_direction(down);
					break;
				case KEY1_PRES:	//控制LED1翻转	 
					snake_direction(right);
					break;
				case KEY0_PRES:	//同时控制LED0,LED1翻转 
					snake_direction(left);
					break;
			}
			key=0;
		} 
		/*LED0=!LED0;				   		 
		delay_ms(1000);	*/
	} 
}
 
