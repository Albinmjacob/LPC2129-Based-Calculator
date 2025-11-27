#include<lpc21xx.h>
#include"header.h"
void lcd_float(float f)
{
int num;
if(f==0)
{
lcd_string("0.0");
return;
}
if(f<0)
{
f=-f;
lcd_data('-');
}
num=f;
lcd_integer(num);
lcd_data('.');
num=(f-num)*1000000;
lcd_integer(num);
}
