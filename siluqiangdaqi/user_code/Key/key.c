#include "key.h"

/*******************************************************************************
* 函 数 名       : key_scan
* 函数功能		 : 检测独立按键是否按下，按下则返回对应键值
* 输    入       : mode=0：单次扫描按键
				   mode=1：连续扫描按键
* 输    出    	 : KEY1_PRESS：K1按下
				   KEY2_PRESS：K2按下
				   KEY3_PRESS：K3按下
				   KEY4_PRESS：K4按下
				   KEY_UNPRESS：未有按键按下
*******************************************************************************/
u8 key_scan(u8 mode)
{
	static u8 key=1;

	if(mode)key=1;//连续扫描按键
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//任意按键按下
	{
		delay_10us(1000);//消抖
		key=0;
		if(KEY1==0)
			return PLEAR_1;
		else if(KEY2==0)
			return PLEAR_2;
		else if(KEY3==0)
			return PLEAR_3;
		else if(KEY4==0)
			return PLEAR_4;	
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)	//无按键按下
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}

/*******************************************************************************
* 函 数 名       : key_matrix_ranks_scan
* 函数功能		 : 使用行列式扫描方法，检测矩阵按键是否按下，按下则返回对应键值
* 输    入       : 无
* 输    出    	 : key_value：1-16，对应S1-S16键，
				   0：按键未按下
*******************************************************************************/
u8 key_matrix_ranks_scan(void)
{
	u8 key_value=0;

	KEY_MATRIX_PORT=0xf7;//给第一列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xf7)//判断第一列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第一列按键按下后的键值	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfb;//给第二列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfb)//判断第二列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第二列按键按下后的键值	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=10;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfd;//给第三列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfd)//判断第三列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第三列按键按下后的键值	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfe;//给第四列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfe)//判断第四列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第四列按键按下后的键值	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe);//等待按键松开
	
	return key_value;		
}
