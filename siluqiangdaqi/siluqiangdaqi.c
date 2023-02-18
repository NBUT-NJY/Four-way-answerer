#include <reg52.h>
#include "time.h"
#include "key.h"
#include "smg.h"
#include "beep.h"
#include "public.h"

/*******************************************************************************
* 函 数 名       : answer_time
* 函数功能         : 选手回答倒计时，若成功暂停回答，若失败开启蜂鸣器
* 输    入       : error_plear上一阶段选手台号，time_sec倒计时时间
* 输    出         : 无
*******************************************************************************/
u8 answer_time(u8 error_plear,u16 time_sec)
{
   u8 key = 0;
   u8 time_buf[8];
   if(error_plear == 0)//如果有选手提前抢答，直接跳过倒计时过程
   {
      return 0;
   }
   time0_start(time_sec);//开始计时
   while (1)
   {
      key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
      if(key == ENTER)//回答正确或错误停止计时
      {
         time0_stop();//停止计时
         while (1)
         {
            key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
            if(key == REST)//如果裁判按下重置则退出抢答成功剩余计时展示
               {
                  return 0;
               }
            time_buf[0]=gsmg_code[error_plear];//选手编号
		      time_buf[1]=0x40;
		      time_buf[2]=0x40;
		      time_buf[3]=0x40;
		      time_buf[4]=gsmg_code[last_gsec/1000];
		      time_buf[5]=gsmg_code[(last_gsec%1000)/100];
		      time_buf[6]=gsmg_code[(last_gsec%100)/10];
		      time_buf[7]=gsmg_code[last_gsec%10];          //秒显示
            smg_display(time_buf,1);//显示	
         }
      }
      else if(gsec <= 0)//倒计时结束
      {
         time0_stop();
         while (1)
         {
            key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
            if(key == REST)//如果裁判按下重置则退出倒计时结束展示
            {
               return 0;
            }
            time_buf[0]=gsmg_code[error_plear];//选手编号
		      time_buf[1]=0x40;
		      time_buf[2]=0x40;
		      time_buf[3]=0x40;
		      time_buf[4]=gsmg_code[0];
		      time_buf[5]=gsmg_code[0];
		      time_buf[6]=gsmg_code[0];
		      time_buf[7]=gsmg_code[0]; 
            smg_display(time_buf,1);//显示
            beep_alarm(10,10);//蜂鸣器响
         }
         return 0;
      }
      else//刷新剩余时间
      {
         time_buf[0]=gsmg_code[error_plear];//选手编号
		   time_buf[1]=0x40;
		   time_buf[2]=0x40;
		   time_buf[3]=0x40;
		   time_buf[4]=gsmg_code[gsec/1000];
		   time_buf[5]=gsmg_code[(gsec%1000)/100];
		   time_buf[6]=gsmg_code[(gsec%100)/10];
		   time_buf[7]=gsmg_code[gsec%10]; 
         smg_display(time_buf,1);//显示	  
      }
   }
}

/*******************************************************************************
* 函 数 名       : answer
* 函数功能         : 获取抢答成功的选手台号
* 输    入       : ready阶段的选手台号
* 输    出         : 若抢答成功返回选手台号，若上一阶段有选手提前抢答返回0
*******************************************************************************/
u8 answer(u8 error_plear)
{
   u8 key = 0;
   if(error_plear != 0)//如果有选手提前抢答，直接跳过抢答过程
   {
      return 0;
   }
   while (1)
   {
      key = key_scan(0);
      if(key != 0)//有选手抢答成功返回选手编号
      {
         return key;
      }
   }
   
}

/*******************************************************************************
* 函 数 名       : ready
* 函数功能         : 判断是否有选手提前抢答
* 输    入       : 无
* 输    出         : 如果有选手抢答返回选手台号，若无返回0
*******************************************************************************/
u8 ready(void)
{
   u8 key = 0;
   u8 key_plear = 0;
   u8 ready_buf[8];
   ready_buf[0] = R;
   ready_buf[1] = E;
   ready_buf[2] = A;
   ready_buf[3] = D;
   ready_buf[4] = Y;
   ready_buf[5] = 0x40;
   ready_buf[6] = 0x40;
   ready_buf[7] = 0x40;
   while (1)
   {
      key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
      key_plear = key_scan(0);//检测是否选手提前抢答
      if (key == ENTER)//裁判按下开始健
      {
         break;
      }
      else if(key_plear != 0)//有选手提前抢答
      {
         while(1)
         {
            key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
            if(key == REST)//如果裁判按下重置则退出提前抢答选手展示
            {
               break;
            }
            ready_buf[0] = gsmg_code[key_plear];
            ready_buf[1] = 0x40;
            ready_buf[2] = 0x40;
            ready_buf[3] = E;
            ready_buf[4] = R;
            ready_buf[5] = R;
            ready_buf[6] = O;
            ready_buf[7] = R;
            smg_display(ready_buf,1);//显示提前抢答选手和错误信息
            beep_alarm(10,10);
         }
         return key_plear;
      }
      else//无选手抢答且裁判未按开始建
      {  
         smg_display(ready_buf,1);//显示'READY'
      }
   }
   return 0;
}

/*******************************************************************************
* 函 数 名       : countdown_t
* 函数功能         : 获取倒计时时间
* 输    入       : 无
* 输    出         : 倒计时时间
*******************************************************************************/
u16 countdown_t(void)
{
   u8 key = 0;
   u8 time_buf[8];//储存倒计时
   u8 min = 0;//倒计时分定义
   u16 sec = 0;//倒计时秒定义
   while (1)
   {
      key = key_matrix_ranks_scan();//获取矩阵按键按下的按键
      if(key == MINUP && min < 99)//分钟倒计时+1
      {
         min++;
         //beep_alarm(1000,10);//短暂提示音
      }
      else if(key == SECUP && sec < 99)//秒倒计时+1
      {
         sec++;
         //beep_alarm(1000,10);//短暂提示音
      }
      else if(key == REST)//重置倒计时
      {
         min = 0;
         sec = 0;
         //beep_alarm(1000,10);//短暂提示音
      }
      else if(key == ENTER)//倒计时时间确定
      {
         //beep_alarm(1000,10);//短暂提示音
         break;
      }
      time_buf[0] = gsmg_code[min/10];
      time_buf[1] = gsmg_code[min%10];//分
      time_buf[2] = 0x40;//-
		time_buf[3] = gsmg_code[sec/10];
		time_buf[4] = gsmg_code[sec%10];//秒
		time_buf[5] = 0x40;//-
      time_buf[6] = 0x40;//-
      time_buf[7] = 0x40;//-
      smg_display(time_buf,1);//显示	
   }
   sec = sec + min*60;
   return sec;
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能         : 主程序运行
* 输    入       : 无
* 输    出         : 无
*******************************************************************************/
void main()                                
{   
   u8 answer_plear;                 //抢答选手
   u16 time_sec;                     //倒计时时间
   time0_init();
   while(1)
    {
      time_sec = 0;               //重置倒计时时间
      answer_plear = 0;          //重置成功抢答的选手
      time_sec = countdown_t();  //获取倒计时时间
      answer_plear = ready();     //准备函数
      answer_plear = answer(answer_plear);     //返回抢答成功的选手
      answer_time(answer_plear,time_sec); 
    }
}
