#include<LPC21XX.H>
#include"header.h"
extern int flag;
void eint0_handler(void)__irq
{
flag=!flag;
EXTINT=1;
VICVectAddr=0;
}

void en_eint0(void)
{
         EXTMODE=1;//edge mode select
	     EXTPOLAR=0;//active low
		 PINSEL1|=1;
			VICIntSelect=0;	//Irq
			VICVectCntl2=14 |(1<<5); // EINT0 store in  vic
		    VICVectAddr2=(u32)eint0_handler;	 //isr addresh is store
		    VICIntEnable |= (1<<14);	 // enable eint0 
}