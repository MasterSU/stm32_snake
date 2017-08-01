#include "snake.h"
u8 d=2;
u8 direction;
u16 location=2;
u32 speed=4;
u8 game_map[width][length];
//u8 score=0;
points snake_body[800];
points food;
points lastbody;
points ti;
void initsnake()
{
    food=create_food();
    snake_body[0].x=width/2;
    snake_body[0].y=length/2;
    snake_body[1].x=width/2;
    snake_body[1].y=length/2-d; 
    snake_direction(down);
    //set_snake_speed();
		draw_map();
}
void move()
{
  u16 i;
	lastbody=snake_body[location-1];
  for(i=location-1;i>0;i--)
      snake_body[i]=snake_body[i-1];
  switch(direction)
  {
    case 1:snake_body[0].x+=d;break;
    case 2:snake_body[0].x-=d;break;
    case 3:snake_body[0].y-=d;break;
    case 4:snake_body[0].y+=d;break;
  }
	ti.x=lastbody.x;
	ti.y=lastbody.y;
	rule();
	draw_snake(snake_body,location);
}

points create_food()
{
	points a;
	a=snake_rand();
	
	LCD_DrawRectangle(a.x,a.y,a.x+d,a.y+d);
	LCD_Fill(a.x,a.y,a.x+d,a.y+d,BLACK);
	return a;
}
void rule()
{
    u16 i;
    for(i=1;i<location;i++)
        if(snake_body[0].x==snake_body[i].x&&snake_body[0].y==snake_body[i].y)
				
					game_end();
					
				
    if(snake_body[0].x==0||snake_body[0].x==width||snake_body[0].y==0||snake_body[0].y==length)
		
			game_end();
		if(snake_body[0].x==food.x&&snake_body[0].y==food.y)
		{
			
			location++;
			snake_body[location-1].x=ti.x;
			snake_body[location-1].y=ti.y;
			food=create_food();
		}
	
}

void set_snake_speed(u8 dir)
{
	direction=dir;
}

void game_end()
{
	u8 str[]="game_over";
	LCD_ShowString(90,100,1000,500,15,str);
	//LCD_ShowChar(90,150,score,15,0);
}

void snake_direction(u8 dire)
{
	direction=dire;
}

void draw_snake(points *list,u16 len)
{
	u16 n=0;
	for(n=0;n<location;n++)
	{
		LCD_DrawRectangle(snake_body[n].x,snake_body[n].y,snake_body[n].x+d,snake_body[n].y+d);
		LCD_Fill(snake_body[n].x,snake_body[n].y,snake_body[n].x+d,snake_body[n].y+d,BLACK);
	}
	LCD_DrawRectangle(lastbody.x,lastbody.y,lastbody.x+d,lastbody.y+d);
	LCD_Fill(lastbody.x,lastbody.y,lastbody.x+d,lastbody.y+d,WHITE);
}

void draw_map()
{
	LCD_DrawRectangle(0,0,width,length);
}

points snake_rand()
{
	points fd;
	u8 x=0,y=0;
	u16 m,n,value1=0,value2=0;
	while(fd.x>=width||fd.x<=0||fd.y>=length||fd.y<=0||fd.x==food.x||fd.y==food.y)
	{
		fd.x=0;fd.y=0;
		
		for(y=0;y<9;y++)
		{
			for(x=0;x<9;x++)
			{
				if(ADC_ConvertedValue>=m)
					value1|=(0<<x);
				else
					value1|=(1<<x);
				m=ADC_ConvertedValue;
				delay_ms(1);
			}
			for(x=0;x<9;x++)
			{
				if(ADC_ConvertedValue>=n)
					value2|=(0<<x);
				else
					value2|=(1<<x);
				n=ADC_ConvertedValue;
				delay_ms(1);
			}
			if(m>=n)
					fd.x|=(1<<y);
				else
					fd.x|=(0<<y);
		}
		for(y=0;y<9;y++)
		{
			for(x=0;x<9;x++)
			{
				if(ADC_ConvertedValue>=m)
					value1|=(0<<x);
				else
					value1|=(1<<x);
				m=ADC_ConvertedValue;
				delay_ms(1);
			}
			for(x=0;x<9;x++)
			{
				if(ADC_ConvertedValue>=n)
					value2|=(0<<x);
				else
					value2|=(1<<x);
				n=ADC_ConvertedValue;
				delay_ms(1);
			}
			if(m>=n)
					fd.y|=(1<<y);
				else
					fd.y|=(0<<y);
		}
	}
	return fd;
}
