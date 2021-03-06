#ifndef __DS1302_H
#define __DS1302_H	
#include "stm32f10x.h"


extern void InitClock(void);
extern void ReadDS1302Clock(u8 *p);
extern void WriteDS1302Clock(u8 *p);
extern void ReadDSRam(u8 *p,u8 add,u8 cnt);
extern void WriteDSRam(u8 *p,u8 add,u8 cnt);
extern void TestDS1302(void);

#endif

