#include <STC15F2K60S2.H>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit CLK=P0^0;  // 串行时钟，下降沿有效
sbit DAT=P0^1;  // 串行数据
sbit LOAD=P0^3;  // 串行数据装载，下降沿有效
sbit LDAC =P0^2; //DAC更新锁存控制，下降沿有效
sbit ZK=P3^3;//总控制
void tixingwave();
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
void Dac(unsigned char addr,bit rng,unsigned char dat)
{
 unsigned char n;
 n=2;
 do
 {
   DAT=(bit)(addr&0x02);
   addr<<=1;
   CLK=0;
   CLK=1;
 }
  while(--n!=0);
  DAT=rng;
  CLK=0;
  CLK=1;
  n=8;
  do
  {
    DAT=(bit)(dat&0x80);
    dat<<=1;
    CLK=0;
    CLK=1;
  }
  while(--n!=0);
  LOAD=0;
  LOAD=1;
  LDAC=0;
  LDAC=1;
}
void Delay(uint n)
{
 uint x;
 for(x=0;x<n;x++)
	{
		_nop_();
	}
}
void Init_TLC5620()
{
   DAT=1;
   CLK=1;
   LDAC=1;
   LOAD=1;
}
void main()
{	 
	unsigned char n=0;
ZK=0;
tixingwave();
}
void tixingwave()
{
  //uchar i=0;
  //for(i=0;i<0xfe;i++)
  //Dac(1,0,i);
  //for(i=0;i<0xff;i++)
 //{
 // Dac(1,0,0xff);
 //}
  //for(i=0xff;i>0;i--)
  //Dac(1,0,i);
//for(i=1;i<0xff;i++)
//Dac(1,0,0);
	Dac(1,0,0x00);
	delayms(10);
  	Dac(1,0,0xff);

}  	 	