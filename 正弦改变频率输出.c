#include <STC15F2K60S2.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
unsigned char n=0;
unsigned char k=0;
void fangbowave()
// 定义I/O 端口
sbit CLK=P0^0;  // 串行时钟，下降沿有效
sbit DAT=P0^1;  // 串行数据
sbit LOAD=P0^3;  // 串行数据装载，下降沿有效
sbit LDAC =P0^2; //DAC更新锁存控制，下降沿有效
sbit ZK=P3^3;//总控制
/**************************************************************************
************************
函数： Dac()
功能：发送数据至 TLC5620 串行DAC
参数：
addr ：DAC 通道地址，取值 0～3，对应通道 A～D
rng ：附加的范围位， rng=0 时， Vo不会超过 Vref ，rng=1时， Vo变为2倍
dat ：8位DAC 数据
公式：
rng=0 时，Vo=Vref*(dat/256)
rng=1 时，Vo=Vref*(dat/256)*2
***************************************************************************
***********************/
void Dac(unsigned char addr, bit rng, unsigned char dat)
{
	unsigned char n;// 发送通道地址
	n = 2;
	do
	{CLK = 0;
		DAT = (bit)(addr & 0x02);
		addr <<= 1;
	//	CLK = 0;
		CLK = 1;
	} while ( --n != 0 );
	// 发送 RNG 位
	CLK = 0;
DAT = rng;
//	CLK = 0;
	CLK = 1;
	// 发送 8位DAC 数据
	n = 8;
	do
	{CLK = 0;
		DAT = (bit)(dat & 0x80);
		dat <<= 1;
		
		CLK = 1;
	} while ( --n != 0 );
	// 装载数据
	LOAD = 0;
	LOAD = 1;
	// 数据锁存到 DAC 转换器
	LDAC = 0;
	LDAC = 1;
}


/*
函数： Delay()
功能：延时 1ms ～256ms
参数：
t>0 时，延时 (t)ms
t=0 时，延时 256ms
*/
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
void Init_TLC5620()  // 初始化 TLC5620
{
	DAT = 1;
	CLK = 1;
	LDAC = 1;
	LOAD = 1;
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
void main()
{	 

	while(1)
	{    {
    Dac(1,0,0x00); 
    delayms(100);
    Dac(1,0,0xff);    
    delayms(100);
    }
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
void T0_time()interrupt 1
{
	TH0=(65536-46)/256;
	TL0=(65536-46)%256;
	Dac(1,1,juchiwave());
	k++;
	n++;
	if(k==41)
	{
		k=0;
	}
}
void T1_time()interrupt 3
{
	TH1=(65536-114)/256;
	TL1=(65536-114)%256;
	Dac(0,0,juchiwave());
	n++;
	if(n==41)
	{
		n=0;
	}

}





