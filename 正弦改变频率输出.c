#include <STC15F2K60S2.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
unsigned char n=0;
unsigned char k=0;
void fangbowave()
// ����I/O �˿�
sbit CLK=P0^0;  // ����ʱ�ӣ��½�����Ч
sbit DAT=P0^1;  // ��������
sbit LOAD=P0^3;  // ��������װ�أ��½�����Ч
sbit LDAC =P0^2; //DAC����������ƣ��½�����Ч
sbit ZK=P3^3;//�ܿ���
/**************************************************************************
************************
������ Dac()
���ܣ����������� TLC5620 ����DAC
������
addr ��DAC ͨ����ַ��ȡֵ 0��3����Ӧͨ�� A��D
rng �����ӵķ�Χλ�� rng=0 ʱ�� Vo���ᳬ�� Vref ��rng=1ʱ�� Vo��Ϊ2��
dat ��8λDAC ����
��ʽ��
rng=0 ʱ��Vo=Vref*(dat/256)
rng=1 ʱ��Vo=Vref*(dat/256)*2
***************************************************************************
***********************/
void Dac(unsigned char addr, bit rng, unsigned char dat)
{
	unsigned char n;// ����ͨ����ַ
	n = 2;
	do
	{CLK = 0;
		DAT = (bit)(addr & 0x02);
		addr <<= 1;
	//	CLK = 0;
		CLK = 1;
	} while ( --n != 0 );
	// ���� RNG λ
	CLK = 0;
DAT = rng;
//	CLK = 0;
	CLK = 1;
	// ���� 8λDAC ����
	n = 8;
	do
	{CLK = 0;
		DAT = (bit)(dat & 0x80);
		dat <<= 1;
		
		CLK = 1;
	} while ( --n != 0 );
	// װ������
	LOAD = 0;
	LOAD = 1;
	// �������浽 DAC ת����
	LDAC = 0;
	LDAC = 1;
}


/*
������ Delay()
���ܣ���ʱ 1ms ��256ms
������
t>0 ʱ����ʱ (t)ms
t=0 ʱ����ʱ 256ms
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
void Init_TLC5620()  // ��ʼ�� TLC5620
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





