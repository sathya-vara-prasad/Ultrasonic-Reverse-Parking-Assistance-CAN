#include"header.h"
#include<LPC21XX.H>


void uart0_init(u32 baud)
{
int a[]={15,60,30,15,15};
u32 pclk;
u32 result;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0 |=0x5;
U0LCR=0x83;
U0DLL=result&0xFF;
U0DLM=(result>>8)&0xFF;
U0LCR=0x03;
}
 #define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data)
{
U0THR=data;
while(THRE==0);
}
 #define RDR (U0LSR&1)
u8 uart0_rx(void)
{
while(RDR==0);
 return U0RBR;
 }
 void uart0_tx_string(s8 *p)
 {
   while(*p)
   {
   U0THR=*p;
   while(THRE==0);
   p++;
   }
 }
 void uart0_rx_string(s8 *p,s32 max)
 {
  s32 i;
 for(i=0;i<max;i++)
 {
 while(RDR==0);
 p[i]=U0RBR;
 if(p[i]=='\r')
 break;
 uart0_tx(p[i]);
 }
 p[i]=0;
 }

 







	 
