#include "sys.h"
#include "74HC595.h"
#include "delay.h"



void HC595_Init(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
	
}  



void 	Send595NIX0(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
		DATA0 =1;
		else DATA0=0;
		SHCP0  = 1;
		SHCP0  = 0;
		dat<<=1;
	}
		STCP0	=	1;	
		STCP0	=	0;

}	 


void 	Send595NIX1(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
		DATA1 =1;
		else DATA1=0;
		SHCP1  = 1;
		SHCP1  = 0;
		dat<<=1;
	}
		STCP1	=	1;	
		STCP1	=	0;

}	



void 	Send595NIX2(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
		DATA2 =1;
		else DATA2=0;
		SHCP2  = 1;
		SHCP2  = 0;
		dat<<=1;
	}
		STCP2	=	1;	
		STCP2	=	0;

}	



void 	Send595NIX3(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
		DATA3 =1;
		else DATA3=0;
		SHCP3  = 1;
		SHCP3  = 0;
		dat<<=1;
	}
		STCP3	=	1;	
		STCP3	=	0;

}	




void 	Send595NIX4(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
		DATA4 =1;
		else DATA4=0;
		SHCP4  = 1;
		SHCP4  = 0;
		dat<<=1;
	}
		STCP4	=	1;	
		STCP4	=	0;

}	




void 	Send595NIX5(u16 dat)
{
u16 count;
	for(count=16;count>0;count--)
{
		if(dat&0x8000)
	 	DATA5 =1;
		else DATA5=0;
		SHCP5  = 1;
		SHCP5  = 0;
		dat<<=1;
	}
		STCP5	=	1;	
		STCP5	=	0;

}	


