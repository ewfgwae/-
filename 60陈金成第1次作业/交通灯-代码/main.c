#include <REGX52.H>
#include <INTRINS.H>

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


void main()
{
	while(1)
	{
		//11011110ÂÌºì
		P2=0xde;
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();
		//11011101»Æºì
		P2=0xdd;
		Delay500ms();
		//11011111Ãðºì
		P2=0xdf;
		Delay500ms();
		//11011101»Æºì
		P2=0xdd;
		Delay500ms();
		//11011111Ãðºì
		P2=0xdf;
		Delay500ms();
		//11011101»Æºì
		P2=0xdd;
		Delay500ms();
		
		//11110011ºìÂÌ
		P2=0xf3;
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();		
		Delay500ms();
		Delay500ms();
		//11101011ºì»Æ
		P2=0xeb;
		Delay500ms();
		//11111011Ãð»Æ
		P2=0xfb;
		Delay500ms();		
		//11101011ºì»Æ
		P2=0xeb;
		Delay500ms();
		//11111011Ãð»Æ
		P2=0xfb;
		Delay500ms();		
		//11101011ºì»Æ
		P2=0xeb;
		Delay500ms();
		
	}
}
