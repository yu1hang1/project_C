#include<STC15F2K60S2.h>
#include<intrins.h>
#define uchar unsigned char
sbit CLK=P0^0;
sbit DAT=P0^1;
sbit LOAD=P0^3;
sbit LDAC=P0^2;
sbit jidi=P3^3;
sbit sanjiao=P3^4;
sbit juchi=P3^5;
sbit tixing=P3^6;
sbit Sinanjian=P3^7;
uchar flag=0;
void sanjiaowave();
void juchiwave();
void tixingwave();
void SinWave();

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
void delayms(uchar ms)
{
   uchar i;
   while(ms--)
 {
    for(i=0;i<250;i++)
    _nop_();
    _nop_();
    _nop_();
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
   sanjiao=1;
   juchi=1;
   tixing=1;
   Sinanjian=1;
   jidi=0;
   flag=0;
Init_TLC5620();
 while(1)
 {  
    if(!sanjiao)
  {
     delayms(10);
     if(!sanjiao)
     flag=0;
  }
  else if(!juchi)
  {
     delayms(10);
     if(!juchi)
     flag=1;
  }
  else if(!tixing)
  {
     delayms(10);
     if(!tixing)
     flag=2;
  }
  else if(!Sinanjian)
  {
     delayms(10);
     if(!Sinanjian)
     flag=3;
  }
Init_TLC5620();
  if(flag==0)
  {		  
     sanjiaowave();
  }
  else if(flag==1)
  {
     juchiwave();
  }
  else if(flag==2)
  { 
     tixingwave();
  }
  else if(flag==3)
     SinWave();
 }
}
void sanjiaowave()
{
   uchar i=0;
   for(i=0;i<0xff;i++)
  {
     Dac(1,0,i);
     _nop_();
 }
 for(i=0xff;i>0;i--)
  {
     Dac(1,0,i);
     _nop_();
  }
}
void juchiwave()
{
  uchar i=0;
  for(i=0;i<0xff;i++)
  Dac(1,0,i);
  Dac(1,0,0xff);
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
void SinWave()
{
   unsigned char SinTab[]=
 {
   128,147,167,185,202,218,231,241,249,253,
   255,253,249,241,231,218,202,185,167,147,
   127,108,88,70,53,37,24,14,6,2,
   0,2,6,14,24,37,53,70,88,108
 };
  unsigned char n;
  for(n=0;n<40;n++)
 {
    Dac(1,0,SinTab[n]);
    delayms(1);
 }
}
   