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
 ALIENTEK ս��STM32F103������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
 	
//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		count++;
		
		if(count>=speed)
		{
			count=0;
			
			move();
			
		}
	}
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		
	}
}

 int main(void)
 {	 
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
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
				case WKUP_PRES:	//���Ʒ�����
					snake_direction(on);
					break;
				case KEY2_PRES:	//����LED0��ת
					snake_direction(down);
					break;
				case KEY1_PRES:	//����LED1��ת	 
					snake_direction(right);
					break;
				case KEY0_PRES:	//ͬʱ����LED0,LED1��ת 
					snake_direction(left);
					break;
			}
			key=0;
		} 
		/*LED0=!LED0;				   		 
		delay_ms(1000);	*/
	} 
}
 
