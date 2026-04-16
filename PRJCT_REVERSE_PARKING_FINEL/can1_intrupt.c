#include<LPC21XX.H>
#include"header.h"
extern CAN2 rx;
extern u8 flag_rx;
void can2_isr(void) __irq
{
	flag_rx=1;
rx.id=C2RID;
	rx.dlc=(C2RFS>>16)&0xF;
	 rx.rtr=(C2RFS>>30);
	if(rx.rtr == 0)
	{
		rx.byteA=C2RDA;
		rx.byteB=C2RDB;
	}
	C2CMR=(1<<2);//relese reciver buffer
	VICVectAddr=0;
}

void en_can2_intrupt(void)
{
//config can1 intrupt
VICIntSelect=0;	
VICIntEnable|=(1<<27);//can1 rx intrupt is unable
VICVectAddr6=(u32)can2_isr;
VICVectCntl6=27 | (1<<5);	
	
	//enable can1 intrupt
	C2IER=1;//rx intrupt is active
	
}	