#ifndef _key_H
#define _key_H

#include "public.h"

//使用宏定义矩阵按键控制口	
#define KEY_MATRIX_PORT	P1	

//定义独立按键控制脚
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

//使用宏定义独立按键按下的键值
#define PLEAR_1	    1   //选手1
#define PLEAR_2	    2   //选手2
#define PLEAR_3	    3   //选手3
#define PLEAR_4	    4   //选手4
#define KEY_UNPRESS	0   //无选手按键

//使用宏定义矩阵按键按下的键值
#define MINUP       1   //分钟时间+1
#define SECUP       2   //秒时间+1
#define REST        3   //重置按键
#define ENTER       4   //确认、开始按键

u8 key_scan(u8 mode);   //独立按键按下检测

u8 key_matrix_ranks_scan(void);     //矩阵键盘按下检测
#endif
