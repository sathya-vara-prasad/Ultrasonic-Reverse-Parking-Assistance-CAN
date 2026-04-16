#include<LPC21XX.H>
#include"header.h"
void can2_init(void)
{
VPBDIV=1;
PINSEL1|=0x14000;
C2MOD=1;
AFMR=2;
C2BTR=0x001c001d;
C2MOD=0;
}
#define TCS ((C2GSR>>3)&1)
void can2_tx(CAN2 tx)
{
C2TID1=tx.id;
C2TFI1=((tx.dlc)<<16);
if(tx.rtr == 0)
{
C2TDA1=tx.byteA;
C2TDB1=tx.byteB;
}
else
C2TFI1|=(1<<30);
C2CMR=0x21;
while(TCS == 0);
}
// #define RBS (C2GSR&1)
//void can2_rx(CAN2 *rx)
//{
//while(RBS == 0);
//rx->id=C2RID;
//rx->dlc=((C2RFS>>16)&0x3FF);
//rx->rtr=((C2RFS>>30)&1);
//if(rx->rtr== 0)
//{
//rx->byteA=C2RDA;
//rx->byteB=C2RDB;
//}
//C2CMR=(1<<2);
//}

