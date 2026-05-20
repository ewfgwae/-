#include <REGX52.H>
#include <INTRINS.H>
sbit output=P0^0;
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Timer0_Init(void)		//500??@12.000MHz
{
	TMOD &= 0xF0;			//???????
	TMOD |= 0x01;			//???????
	TL0 = 0x0C;				//???????
	TH0 = 0xFE;				//???????
	TF0 = 0;				//??TF0??
	TR0 = 1;				//???0????
}


void Timer_use()
{
	
	TL0 = 0x0C;				
	TH0 = 0xFE;				
	output=~output;

}

void main()
{
	output=0;
	Timer0_Init();
	EA=1;
	while(1)
	{
		if(TF0)
		{
			TF0=0;
			Timer_use();
		}
	}
}
