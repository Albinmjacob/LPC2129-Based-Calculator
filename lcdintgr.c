#include<lpc21xx.h>
#include "header.h"
void lcd_integer(int num)
{
int a[10],i;
if(num==0)
{
lcd_data('0');
}
if(num<0)
{
num=-num;
lcd_data('-');
}
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
lcd_data(a[i]);
}
