#include<lpc21xx.h>
#include"header.h"
void lcd_data(unsigned char data)
{
unsigned int temp;
//highernibble
IOCLR1=0xFE<<16;
temp=(data&0xF0)<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

//lower nibble
IOCLR1=0xFE<<16;
temp=(data&0x0F)<<20;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(unsigned char cmd)
{
unsigned int temp;
//higher nibble
IOCLR1=0xFE<<16;
temp=(cmd&0xF0)<<16;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

//lower nibble
IOCLR1=0xFE<<16;
temp=(cmd&0x0F)<<20;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init()
{
IODIR1=0xFE<<16;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x03);
lcd_cmd(0x0E);
lcd_cmd(0x01);
}

// string
void lcd_string(char *ptr)
{
while(*ptr!=0)
{
lcd_data(*ptr);
ptr++;
}
} 

