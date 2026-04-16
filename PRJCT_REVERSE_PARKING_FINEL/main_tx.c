#include<LPC21XX.H>
#include"header.h"
CAN2 tx;
CAN2 rx;
int flag;
int flag_rx;
void beep_2sec();
void beep_1sec();
void beep_250ms();
void beep_100ms();
void beep_1ms();
int main()
{
u8 data;
int rmt=1;
int data_frm=0;
IODIR0|=(1<<21);
IOCLR0=(1<<21);
can2_init();
en_eint0();
en_can2_intrupt();
uart0_init(9600);
uart0_tx_string("NODE A\r\n");
 while(1)
 {
 if(flag_rx)
 {
 flag_rx=0;
 uart0_tx_string("from NODE B RECUVED dATA=");
  data=rx.byteA;
  //if(data ==='C')
  if(data==0x11)
  {
  uart0_tx_string("CASE 0x11 is Recived\r\n");
  //beep_2sec();
  IOSET0=(1<<21);
  delay_ms(400);
  IOCLR0=(1<<21);
  delay_sec(2);
  }
  else if(data==0x22)
  {
  uart0_tx_string("CASE 0x22 is Recived\r\n");
  //beep_1sec();
  IOSET0=(1<<21);
  delay_ms(400);
  IOCLR0=(1<<21);
  delay_sec(1);
  }
  else if(data==0x33)
  {
  uart0_tx_string("CASE 0x33 is Recived\r\n");
  //beep_250ms();
  IOSET0=(1<<21);
  delay_ms(400);
  IOCLR0=(1<<21);
  delay_ms(250);
  }
  else if(data==0x44)
  {
  uart0_tx_string("CASE 0x44 is Recived\r\n");
  //beep_100ms();
  IOSET0=(1<<21);
  delay_ms(400);
  IOCLR0=(1<<21);
  delay_ms(100);
  }
  else if(data==0x55)
  {
  uart0_tx_string("CASE 0x55 is Recived\r\n");
  //beep_1ms();
  IOSET0=(1<<21);
  delay_ms(400);
  //IOCLR0=(1<<21);
  }
//  IOSET0=(1<<21);
//   delay_ms(100);
//   IOCLR0=(1<<21);
//  uart0_tx_string("\r\n");
 }
 if((flag==1) && (rmt==1))
 {
 data_frm=!data_frm;
 rmt=!rmt;
 tx.id=0x123;
 tx.rtr=1;
 tx.dlc=1;
 can2_tx(tx);
 }
 else if((data_frm==1) && (flag == 0))
 {
 rmt=!rmt;
 data_frm=!data_frm;
 tx.id=0x123;
 tx.rtr=0;
 tx.dlc=1;
 tx.byteA=65;
 can2_tx(tx);
 }
 }
 }

// void beep_2sec()
// {
// IOSET0=(1<<21);
// delay_ms(400);
// IOCLR0=(1<<21);
// delay_ms(1600);
// }

// void beep_1sec()
// {
// IOSET0=(1<<21);
// delay_ms(400);
// IOCLR0=(1<<21);
// delay_ms(600);
// }

// void beep_250ms()
// {
// IOSET0=(1<<21);
// delay_ms(50);
// IOCLR0=(1<<21);
// delay_ms(200);
// }

// void beep_100ms()
// {
// IOSET0=(1<<21);
// delay_ms(50);
// IOCLR0=(1<<21);
// delay_ms(50);
// }
// void beep_1ms()
// {
// IOSET0=(1<<21);
// delay_ms(1);
// IOCLR0=(1<<21);
// }