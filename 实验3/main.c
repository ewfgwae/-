#include <REGX52.H>
#include "nixie.h"
static unsigned char num;
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}


void main()
{

	Timer0Init();

	while(1)
	{
		Nixie(1,num);
	
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;

	if(T0Count>1000)
	{
		T0Count=0;
		num++;
		if(num>9)
		{
			num=0;
		}
		
	}
	
}
