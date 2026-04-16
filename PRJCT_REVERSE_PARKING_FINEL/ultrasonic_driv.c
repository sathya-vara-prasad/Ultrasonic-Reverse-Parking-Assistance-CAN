#include<LPC21xx.h>
#include"header.h"
#define trig (1<<8)  //p0.8
#define echo ((IOPIN0>>9)&1)  //p0.9

void us_init()
{
IODIR0|=(1<<8);
T1TCR=0;
T1PR=59;
}

void send_pulse()
{
T1TC=T1PC=0;
IOSET0=trig;	   //trig=1;
delay_ms(10);
IOCLR0=trig;	   //trig=0;
}

u32 get_range()
{
u32 get=0;
send_pulse();
while(!echo);
T1TCR=0x01;
while(echo);
T1TCR=0;
get=T1TC;
if(get<38000)
get=get/59;
else
get=0;
return get;
}