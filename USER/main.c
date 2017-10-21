#include "delay.h"
#include "sys.h"
#include "remote.h"
#include "ds1302.h"
#include "74HC595.h"
#include "beep.h"
#include "timer.h"


/************************************************
NIXIE CLOCK---------IN14
Alucard   
2016.1.17
Steins Gate;
El psy congroo!
************************************************/



u8 key;
u8 keyval;
u8 pp=0,num=0;
u8 setting[2];
u8 prt;
u8 prtt=0;

u16 NixieData[6];
u16 LED[6];
u16 CLO=CLO_BOTH;
u16 NUM[6];

u8 flagsetting=0;
u8 flagtime=1;
u8 flagpwm=0;
u8 flagshine=0;
u8 flagpwmdelay=0;


u8 times[7];
u8 NIXIEtimes[12];


u16 led0pwmval=0;
u8 dir=1;


void searchkey(void);
void Settingmode(void);
void Dispsetting(void);
u16 NIXIEdecode(u8 message);
void NIXIEonload(void);
void SendNIXIEdata(void);
void Shinemode(void);
void PWMmode(void);
void Protectmode (void);
void BI(void);
void BI_BI_BI(void);
void BIIIII(void);



	int main(void)
 {	 

	  delay_init();	    	
	  InitClock();       
	  HC595_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    TIM3_PWM_Init(899,0);
    Remote_Init();			
	  BEEP_Init();	 

		 	  		    							  
	while(1)
	{

	  Dispsetting();
		
    Settingmode();
		
		ReadDS1302Clock(times);
		
    NIXIEonload();
		 
    SendNIXIEdata();
		
    Shinemode();
		
		PWMmode();
		
		Protectmode();
		

	}
		 		
 }	

//		







//以下是各个函数定义







void Dispsetting(void)
{
	u8 j;
key=Remote_Scan();	
		if(key)
		{	 
      BI();
			switch(key)
			{

				case 162:flagsetting=1;break;

				case 2 :if(flagtime){flagtime=0; CLO= CLO_BOTH; } //显示时间 
					       else {flagtime=1;CLO= CLO_DOWN;}//显示日期
								 break; 
				case 66 : if(flagpwm){flagpwm=0;}//关闭PWM      按键0
				         else {flagpwm=1;}    //打开PWM
								 break;								 
				case 104:for(j=0;j<6;j++) LED[j]=LED_RED;break;		  
				case 152:for(j=0;j<6;j++) LED[j]=LED_GREEN;break;	   
				case 176:for(j=0;j<6;j++) LED[j]=LED_BLUE;break;	    
				case 48: for(j=0;j<6;j++) LED[j]=LED_YELLOW;break;		    
				case 24: for(j=0;j<6;j++) LED[j]=LED_CYAN;break;		    
				case 122:for(j=0;j<6;j++) LED[j]=LED_PURPLE;break;		  
				case 16: for(j=0;j<6;j++) LED[j]=LED_OFF;break;
				case 56: LED[0]=LED_RED; 	  LED[1]=LED_GREEN;  LED[2]=LED_BLUE; 
								 LED[3]=LED_YELLOW; LED[4]=LED_CYAN; LED[5]=LED_PURPLE;break;  //数字键8 七彩模式
        case 90: flagshine=!flagshine;	  break;                                //数字键9 七彩变换LED
        case 82: for(j=0;j<6;j++) LED[j]=LED_WHITE;break;	//退格键 关闭LED				 
        default:	BI_BI_BI();break;								 
					}

			}
}




void searchkey(void)
{

	switch(key)
	{
				case 104:keyval=1;break;		  
				case 152:keyval=2;break;	   
				case 176:keyval=3;break;	    
				case 48:keyval=4;break;		    
				case 24:keyval=5;break;		    
				case 122:keyval=6;break;		  
				case 16:keyval=7;break;			   					
				case 56:keyval=8;break;	 
				case 90:keyval=9;break;
				case 66:keyval=0;break;
	}

}



void Settingmode(void)
{
	 while(flagsetting)
			{
					key=Remote_Scan();
          if(key) BI();
				
				if(flagtime)
					{
				  searchkey();
						switch(key)
						{
						case 34:if(pp==0)pp=2;
							      else pp--;num=0;break;
						case 194:pp++;if(pp>2)pp=0;num=0;break;
						case 104:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
				    case 152:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
				    case 176:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
			    	case 48:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
				    case 24:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
				    case 122:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												 
			     	case 16:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												 
			     	case 56:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;										 
			    	case 90:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;											 
				    case 66:
                       if(!num)
											 {
                       times[pp+3]=(times[pp+3]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp+3]=(times[pp+3]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;										 
		        case 226:	
							if(times[3]<0x24&&times[4]<0x60&&times[5]<0x60)
							{
								WriteDS1302Clock(times); 
							}
							else BI_BI_BI();
							num=0;pp=0;
							flagsetting=0;break;								
						}
						
					}						
          if(!flagtime)
			{
				  searchkey();
						switch(key)
						{
						case 34:if(pp==0)pp=2;
							      else pp--;num=0;break;
						case 194:pp++;if(pp>2)pp=0;num=0;break;
						case 104:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;								
				    case 152:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
				    case 176:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;                        												
			    	case 48:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
				    case 24:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
				    case 122:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
			     	case 16:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
			     	case 56:
                       if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;												
			    	case 90:
                        if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;
				    case 66:
				               if(!num)
											 {
                       times[pp]=(times[pp]&0x0f)+(keyval<<4);
											 num++; 
											 NIXIEonload();
		                   SendNIXIEdata();
											 }
                      else
												{
                       times[pp]=(times[pp]&0xf0)+keyval;
											 num=0; 
											 NIXIEonload();
		                   SendNIXIEdata();
											  }
                       break;
		        case 226:	
							if(times[1]<0x13)
							{
								switch(times[1])
								{
									
									case 0x02:if(times[2]<0x30){ WriteDS1302Clock(times);}
                         else BI_BI_BI();												 
									       break;
							
									case 0x04:if(times[2]<0x31){ WriteDS1302Clock(times);}
                         else BI_BI_BI();									
									       break;
									
									case 0x06:if(times[2]<0x31){ WriteDS1302Clock(times);}
                         else BI_BI_BI();
       									break;
								
									case 0x09:if(times[2]<0x31){ WriteDS1302Clock(times);} 
                         else BI_BI_BI();									
									       break;
									
									case 0x11:if(times[2]<0x31){ WriteDS1302Clock(times);} 
		                     else BI_BI_BI();
								        	break;
									default:if(times[2]<0x32){ WriteDS1302Clock(times);} 
                         else BI_BI_BI();
							         		break;
								}

						 }

							num=0;pp=0;
						  flagsetting=0;break;								
						}
						
					}	
}
}







u16 NIXIEdecode(u8 message)
{
	u16 buffer;
 switch (message)
 {
	 case 0:  buffer = NUM_0;break;
	 case 1:  buffer =  NUM_1;break;
	 case 2:  buffer =  NUM_2;break;
	 case 3:  buffer =  NUM_3;break;
	 case 4:  buffer =  NUM_4;break;
	 case 5:  buffer =  NUM_5;break;
	 case 6:  buffer =  NUM_6;break;
	 case 7:  buffer =  NUM_7;break;
	 case 8:  buffer =  NUM_8;break;
	 case 9:  buffer =  NUM_9;break;
 }
return buffer;
}



void NIXIEonload(void)
	
{
	   u8 i;
	   NIXIEtimes[0]=times[0]>>4;
		 NIXIEtimes[1]=times[0]&0x0f;
		 NIXIEtimes[2]=times[1]>>4;
		 NIXIEtimes[3]=times[1]&0x0f;
		 NIXIEtimes[4]=times[2]>>4;
		 NIXIEtimes[5]=times[2]&0x0f;
		 NIXIEtimes[6]=times[3]>>4;
		 NIXIEtimes[7]=times[3]&0x0f;
		 NIXIEtimes[8]=times[4]>>4;
		 NIXIEtimes[9]=times[4]&0x0f;
		 NIXIEtimes[10]=times[5]>>4;
		 NIXIEtimes[11]=times[5]&0x0f;


		 if(flagtime)
		 {		 
			 for(i=6;i<12;i++)
		 NUM[i-6]=NIXIEdecode(NIXIEtimes[i]);
			 
		 }
		 if(!flagtime)
		 {
	 for(i=0;i<6;i++)
		 NUM[i]=NIXIEdecode(NIXIEtimes[i]);
			 
		 } 
		 for(i=0;i<6;i++)
		 NixieData[i]=NUM[i]+CLO+LED[i];
		 
}




void SendNIXIEdata(void)
{
  Send595NIX0(NixieData[0]);
	Send595NIX1(NixieData[1]);
	Send595NIX2(NixieData[2]);
	Send595NIX3(NixieData[3]);
	Send595NIX4(NixieData[4]);
  Send595NIX5(NixieData[5]);

}




void Shinemode(void)
{
		if(flagshine)
		{
		u8 i;
		u16 BUF;
    BUF=LED[0];
    for(i=0;i<5;i++) LED[i]=LED[i+1];
    LED[5]=BUF;			
		}
		if(!flagpwm) delay_ms(1000);
	}		
		
	
	
	

void PWMmode(void)
	{
	   if(flagpwm)
		 {
		 		
		while(!flagpwmdelay)	
		{delay_ms(10);	
				if(dir)led0pwmval=led0pwmval+10;
		else led0pwmval=led0pwmval-10;

 		if(led0pwmval>950){dir=0;flagpwmdelay=1;}
		if(led0pwmval==0){dir=1;	flagpwmdelay=1;}									 
		TIM_SetCompare2(TIM3,led0pwmval);	
    }
		flagpwmdelay=0;
		 	 
		 }
	
	}
	
	
	
	

void 		Protectmode (void)
{
	 u8 h,k;
	 prt=times[5]&0X0F;
	 if(prt==0)
	 {
	 prtt++;
		 if(prtt==60)
		 {

		for(k=0;k<10;k++)
 {
	 for(h=0;h<6;h++)
	 {
		 NUM[h]=NIXIEdecode(9-k);
   NixieData[h]=NUM[h]+CLO+LED[h];
	 }
   SendNIXIEdata();
	 delay_ms(500);
 }			 
		 BIIIII(); 
     prtt=0;
		 }
	 }
}






void BI(void)
{
		  BEEP=1;
			delay_ms(10);
			BEEP=0;
}

void BI_BI_BI(void)
{
		  BEEP=1;
			delay_ms(50);
			BEEP=0;
	    delay_ms(30);
      BEEP=1;
			delay_ms(50);
			BEEP=0;
		  delay_ms(30);
      BEEP=1;
			delay_ms(50);
			BEEP=0;
}

void BIIIII(void)
{
		  BEEP=1;
			delay_ms(80);
			BEEP=0;
}

