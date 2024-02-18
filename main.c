#include<LPC21XX.h>
#include "header.h"
#define sw1 ((IOPIN0>>13)&1)
#define sw2 ((IOPIN0>>14)&1)
#define sw3 ((IOPIN0>>15)&1)
int main(){
IODIR0&=~(1<<13);
IODIR0&=~(1<<14);
IODIR0&=~(1<<15);
u8 s,m,h,w,dd,mm,yy,M,c2f=0;
u32 c=0,c2=0;
char *a[8]={" ","SUN","MON","TUE","WED","THU","FRI","SAT"};
lcd_init();
uart0_init(9600);
i2c_init();
SETUP:
while(1){
if (sw1==1)
		{
			while (sw1==1);
			{
				lcd_cmd(0x01);
				lcd_string("SET HH: ");
				c++;
				lcd_int(c);
				if(c==12)
					c=0;
			}
		}
//		if (sw2==1)
//		{
//			while (sw2==1);
//			{
//				lcd_cmd(0x01);
//				lcd_string("AM or PM ");
//				c2=0;
//				if (sw1==1)
//					{
//						while (sw1==1);
//						{
//							c++;
//							if (c2%2==0)
//							{
//								lcd_cmd(0x89);
//								lcd_string("AM");
//							}
//							else
//							{
//								lcd_cmd(0x89);
//								lcd_string("PM");
//							}
//						}
//					}
					if (sw2==1)
					{
						while (sw2==1);
						{
							goto TIME;
						}
					}
				}
//			}
//		}
	TIME:

          i2c_wr(0xD0,0x0,0x56);
          i2c_wr(0xD0,0x1,0x59);
          i2c_wr(0xD0,0x2,0X60+c);
          i2c_wr(0xD0,0x3,0x01);
          i2c_wr(0xD0,0x4,0x22);
          i2c_wr(0xD0,0x5,0x11);
          i2c_wr(0xD0,0x6,0x23);
while(1)
{
	if (sw2==1)
		{
			while (sw2==1);
			{
				goto SETUP;
			}
		}
h=i2c_rd(0xD0,0x2);
     m=i2c_rd(0xD0,0x01);
     s=i2c_rd(0xD0,0x0);
if ((c2%2==0&&c2f==0))
{
	c2f=1;
	M=1;
}
else if(h>>5&1)
M=1;
else
M=0;
h=h&0x1f;
lcd_cmd(0x80);
lcd_data((h/0x10)+48);
lcd_data((h%0x10)+48);
lcd_data(':');
lcd_data((m/0x10)+48);
lcd_data((m%0x10)+48);
lcd_data(':');
lcd_data((s/0x10)+48);
lcd_data((s%0x10)+48);

if(M)
lcd_string("PM");
else
lcd_string("AM");
 
dd=i2c_rd(0xD0,0x04);
     mm=i2c_rd(0xD0,0x05);
     yy=i2c_rd(0xD0,0x06);
w=i2c_rd(0xD0,0x3);
lcd_cmd(0xc0);
lcd_data((dd/0x10)+48);
lcd_data((dd%0x10)+48);
lcd_data('/');
lcd_data((mm/0x10)+48);
lcd_data((mm%0x10)+48);
lcd_data('/');
lcd_data((yy/0x10)+48);
lcd_data((yy%0x10)+48);
lcd_string(a[w]);
}
}
	
