#include <STC15F2K60S2.H>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit CLK=P0^0;
sbit DAT=P0^1;
sbit LOAD=P0^3;
sbit LDAC=P0^2; 	
sbit ZK=P3^3;//×Ü¿ØÖÆ
uchar i=0;
unsigned char n=0;
unsigned char k=0;
void juchiwave();
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
void look_1()
{
       P3=0x7f;
       P2=0x82;
	   delayms(1);
       P3=0xbf;
       P2=0x16;
	   delayms(1);
       P3=0xdf;
       P2=0x82;
	   delayms(1);
       P3=0xef;
       P2=0x82;
	   delayms(1);
}
void look_2()
{
       P3=0x7f;
       P2=0x82;
	   delayms(1);
       P3=0xbf;
       P2=0x2a;
	   delayms(1);
       P3=0xdf;
       P2=0x82;
	   delayms(1);
       P3=0xef;
       P2=0x82;
	   delayms(1);

}
void look_3()
{
       P3=0x7f;
       P2=0x82;
	   delayms(1);
       P3=0xbf;
       P2=0x82;
	   delayms(1);
       P3=0xdf;
       P2=0x82;
	   delayms(1);
       P3=0xef;
       P2=0x16;
	   delayms(1);

}
uchar KeyScan()
{
  uchar cord_l=0;
  P3=0xf0;
  if((P3&0xf0)!=0xf0)
  {
    delayms(5);
	if((P3&0xf0)!=0xf0)
	{
	  cord_l=P3&0xf0;
	  return cord_l;
	}
  }
  else 
  {
	  return cord_l;
  }
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
{look_3();
Init_TLC5620();
		while(1)
	{ 
	uchar s=KeyScan();
			ZK=0;
	   if(s==0x70)
	   {
		delayms(10);
		if(s==0x70)
		{		TMOD=0x01;
				TH0=(65536-46)/256;
				TL0=(65536-46)%256;
				EA=1;
				ET0=1;
				TR0=1;
				TR1=0;
	      while(s==0x70)
		  {
		       uchar m=KeyScan();
			   if (m!=0)
			   {
			      s=m;
			   }
					look_1();
					
				
		  }
	   }
		}
	   if(s==0xb0)
	   {delayms(10);
		if(s==0xb0)
		{		TMOD=0x10;
				TH1=(65536-114)/256;
				TL1=(65536-114)%256;
				EA=1;
				ET1=1;
				TR1=1;
				TR0=0;
	      while(s==0xb0)
		  {
		       uchar m=KeyScan();
			   if (m!=0)
			   {
			      s=m;
			   }
				look_2();
					
		  }
	   }
		}
		
		
	}
}
void juchiwave()
{
  uchar i=0x00;

}
 void T0_time()interrupt 1
{
	TH0=(65536-46)/256;
	TL0=(65536-46)%256;
	Dac(1,1,i);
	i++;
	if(i==0xff)
	{
		i--;
	}
}     
void T1_time()interrupt 3
{
	TH1=(65536-114)/256;
	TL1=(65536-114)%256;
	Dac(1,1,i);
	i++;
	if(i==0xff)
	{
		i--;
	}
}