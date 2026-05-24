#include <REGX52.H>
#include "nixie.h"



unsigned char num1,num2,num3,num4;

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
	EA=1;

	while(1)
	{
		Nixie(1,num1);
		Delay(1);
		Nixie(3,num2);
		Delay(1);
		Nixie(5,num3);
		Delay(1);
		Nixie(7,num4);
		Delay(1);

	}
}

void Timer0_Isr(void) interrupt 1
{

	static unsigned int T0Count1,T0Count2,T0Count3,T0Count4;
	
	T0Count1++;

	if(T0Count1/10==10)
	{
		T0Count1=0;
		num1++;
		T0Count2++;
		if(num1==10)
		{
			num1=0;
		}
		if(T0Count2==10)
		{
			T0Count3++;
			T0Count2=0;
			num2++;
			if(num2==10)
			{
				num2=0;
			}
			if(T0Count3==10)
			{
				T0Count4++;
				T0Count3=0;
				num3++;
				if(num3==10)
				{
					num3=0;
				}
				if(T0Count4==10)
				{
					T0Count4=0;
					num4++;
					if(num4==10)
					{
						num4=0;
					}
				}
			}
		}
	}
}
