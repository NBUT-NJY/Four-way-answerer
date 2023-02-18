#ifndef _time_H
#define _time_H

#include "public.h"


//变量声明
extern u8 gmsec;//毫秒级定义
extern u16 gsec;//秒级定义
extern u16 last_gsec;//剩余时间存储


//时钟初始化
void time0_init(void);

//倒计时开始函数
void time0_start(u16 time_sec);

//倒计时停止函数
void time0_stop(void);
#endif
