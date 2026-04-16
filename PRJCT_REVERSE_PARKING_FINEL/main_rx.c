#include<LPC21XX.H>
#include"header.h"
CAN2 rx;
CAN2 tx;
volatile u32 range=0;
int flag_rx=0;
int main()
{
//uart0_init(9600);
can2_init();
uart0_init(9600);
us_init();
en_can2_intrupt();
uart0_tx_string("NODE B\r\n");
while(1)
{
 if(flag_rx==1)
 {
 flag_rx=0;
   uart0_tx_string("RMOTE FRAME iS RECIVED\r\n");
   while(1)
   {
    tx.id=0x456;
	tx.dlc=1;
	tx.rtr=0;
	range=get_range();
	if(range>=150)
	{
	tx.byteA=0x11;
	}
	else if(range>=100 && range<150)
	{
	tx.byteA=0x22;
	}
	else if(range>=50 && range<100)
	{
	tx.byteA=0x33;
	}
	else if(range>=10 && range<50)
	{
	tx.byteA=0x44;
	}
	else if(range<=9)
	{
	tx.byteA=0x55;
	}
	can2_tx(tx);
	if(flag_rx == 1)
	{
	uart0_tx_string("data frame is recived\r\n");
	flag_rx=0;
	break;
     }
    delay_ms(50);
	}
  }
  }
  }
	
	



