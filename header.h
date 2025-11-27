// header.h for uart
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;

extern void delay_ms(unsigned int ms);
extern void delay_sec(unsigned int sec);

extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *ptr);
extern void lcd_integer(int num);
extern void lcd_float(float f);

extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(char *ptr);
extern void uart0_rx_string(char *a);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float f);
extern int uart0_rx_integer(void);
extern void uart0_binary(int num);

extern void config_eint0(void);
extern void config_vic_for_eint0(void);

extern void uart0_interrupt(void);
extern void uart0_Handler(void)__irq;