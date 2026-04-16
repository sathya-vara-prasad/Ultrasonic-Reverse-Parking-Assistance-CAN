typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short int u16;
typedef struct TIME
{
u8 sec,min,hour,day,date,month,year;
}RTC; 
typedef struct CAN_MSG
{
u8 rtr;
u8 dlc;
u32 byteA;
u32 byteB;
u32 id;
}CAN2;
extern void can2_init(void);
extern void can2_tx(CAN2 v);
//extern void can2_rx(CAN2 *ptr);

extern void en_can2_intrupt(void);
 extern void print_am(RTC R);
extern void  print_date(RTC R);
 extern void print_day(RTC R);
 extern void print_time(RTC R);
extern void delay_ms(u32);
extern void delay_sec(u32);
extern void lcd_init(void);
extern void lcd_data(u8);
extern void lcd_cmd(u8);
extern void lcd_integer(s32);
extern void lcd_float(float);
extern void lcd_float1(float);
extern u8 gpio_read(u8 port,u8 pin);
extern void gpio_write(u8 port,u8 pin,u8 val);//val 0 1 
extern void gpio_byte_write(u8 port,u8 pin,u8 val);//val must be in 1 byte
extern void uart0_init(u32 baud);
extern void uart0_tx(u8);
extern u8 uart0_rx(void);
extern void uart0_tx_string(s8 *);
extern void en_eint0(void);
extern void uart0_rx_string(s8 *,s32 byte);
extern void adc_init(void);
extern u16 adc_read(u8 ch_num);
extern void ftoa(float f1,s8 *p);
extern void itoa(int,s8 *);
extern void ier_uart0(void);
extern void config_vic_uart0(void);
extern void config_vic_timer1(void);
extern void en_timer1_intrupt(void);
#define CS0 (1<<7)
extern void spi0_init(void);
extern u8 spi0(u8 data);
	extern void i2c_init(void);
extern	void i2c_byte_write_frame(u8 sa, u8 mr, u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);
extern void us_init();

 extern void us_init();
 extern void send_pulse();
 extern u32 get_range();

 extern void can2_init(void);
 extern void can2_tx(CAN2 tx);
 extern void en_can2_intrupt(void);
 extern void en_eint0(void);
