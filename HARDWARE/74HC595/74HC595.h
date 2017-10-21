/********************************************************************* 
* 项目名称: QS30-1辉光模组 目标板试验程序
* 子项名称: F340模块
* 功能描述: 全局定义
*
* 立项时间：2012-06
* 设 计 者：严泽远 
* 日    期：2012-06-29
* Blog	  ：http://www.nixieclock.org
* E-mail  ：yanzeyuan@163.com
*
* 版    本：v1.0.0
*********************************************************************/ 
														   
/********************************************************************* 
* 功能描述: 接口定义
*********************************************************************/ 

#include "sys.h"
#define DATA0 PAout(4)
#define STCP0 PAout(5)
#define SHCP0 PAout(6)
#define DATA1 PAout(1)
#define STCP1 PAout(2)
#define SHCP1 PAout(3)
#define DATA2 PBout(2)
#define STCP2 PBout(10)
#define SHCP2 PBout(11)
#define DATA3 PAout(7)
#define STCP3 PBout(0)
#define SHCP3 PBout(1)
#define DATA4 PBout(15)
#define STCP4 PAout(8)
#define SHCP4 PAout(9)
#define DATA5 PBout(12)
#define STCP5 PBout(13)
#define SHCP5 PBout(14)
/********************************************************************* 
* 功能描述: 常量定义
*********************************************************************/ 


#define	LED_OFF			0x7000
#define	LED_WHITE		0x0000
#define	LED_PURPLE		0x4000
#define	LED_CYAN		0x2000
#define	LED_YELLOW		0x1000
#define	LED_BLUE		0x6000
#define	LED_GREEN		0x3000
#define	LED_RED			0x5000

#define	CLO_OFF			0x0000
#define	CLO_DOWN		0x0400
#define	CLO_UP  		0x0800
#define	CLO_BOTH		0x0C00

#define	NUM_OFF			0x0000
#define	NUM_1			0x0200
#define	NUM_0			0x0001
#define	NUM_9			0x0002
#define	NUM_8			0x0004
#define	NUM_7			0x0008
#define	NUM_6			0x0010
#define	NUM_5			0x0020
#define	NUM_4			0x0040
#define	NUM_3			0x0080
#define	NUM_2			0x0100

void HC595_Init(void);
void Send595NIX0(u16);
void Send595NIX1(u16);
void Send595NIX2(u16);
void Send595NIX3(u16);
void Send595NIX4(u16);
void Send595NIX5(u16);
