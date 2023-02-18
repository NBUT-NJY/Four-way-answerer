#ifndef _smg_H
#define _smg_H

#include "public.h"


#define SMG_A_DP_PORT	P0	//使用宏定义数码管段码口

//对字母的宏定义 
#define A 0x77
#define B 0x7c
#define C 0x39
#define D 0x5e
#define E 0x79
#define F 0x71
#define G 0x3d
#define H 0x76
#define I 0x0f
#define J 0x0e
#define K 0x75
#define L 0x38
#define M 0x37
#define N 0x54
#define O 0x5c
#define P 0x73
#define Q 0x67
#define R 0x31
#define S 0x49
#define T 0x78
#define U 0x3e
#define V 0x1c
#define W 0x7e
#define X 0x64
#define Y 0x6e
#define Z 0x59

//定义数码管位选信号控制脚
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//储存数字字符串定义
extern u8 gsmg_code[17];

//数码管显示推送函数
void smg_display(u8 dat[],u8 pos);

#endif
