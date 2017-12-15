#include <STC15F2K60S2.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit DIG1=P3^7;
sbit DIG2=P3^6;
sbit DIG3=P3^5;
sbit DIG4=P3^4;
uchar Num[10]={0x7d,0x18,0xd5,0xd9,0xb8,0xe9,0xed,0x58,0xfd,0xf9};
void delayms(uint);
void shut()
{
	DIG1=1;
	DIG2=1;
	DIG3=1;
	DIG4=1;
}
void main()
{
	while(1)
	{
		P2=~Num[0];		  
        DIG4=0; 
		delayms(1);
		shut();
		
		P2=~Num[0]; 		
		DIG3=0;
 		delayms(1);
		shut();
		
		P2=~Num[5]; 		
		DIG2=0; 
		delayms(1);
		shut();

		P2=~(Num[2]+2);
		 DIG1=0; 
		delayms(1);
		shut();		
				

	 }
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}