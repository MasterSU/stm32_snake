#ifndef __SNAKE_H
#define __SNAKE_H

#include "stm32f10x.h"
#include "stdio.h"
#include "adc.h"
#include "delay.h"
#include "lcd.h"
#define width 240
#define length 320
#define right 1
#define left 2
#define on 3
#define down 4
typedef struct points
{
    uint16_t x;
    uint16_t y;
}points;
extern u32 speed;
void initsnake(void);
void move(void);
void rule(void);
points create_food(void);
void set_snake_speed(u8 dir);
void game_end(void);
void snake_direction(u8 dire);
void draw_snake(points *list,u16 len);
void draw_map(void);
points snake_rand(void);
#endif
