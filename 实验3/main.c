#include <REGX52.H>

//数码管段码表
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

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
//数码管显示子函数
void Nixie(unsigned char Location,Number)
{
	switch(Location)		//位码输出
	{
		case 8:P2_4=1;P2_3=1;P2_2=1;break;
		case 7:P2_4=1;P2_3=1;P2_2=0;break;
		case 6:P2_4=1;P2_3=0;P2_2=1;break;
		case 5:P2_4=1;P2_3=0;P2_2=0;break;
		case 4:P2_4=0;P2_3=1;P2_2=1;break;
		case 3:P2_4=0;P2_3=1;P2_2=0;break;
		case 2:P2_4=0;P2_3=0;P2_2=1;break;
		case 1:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//段码输出
}



void main()
{


	while(1)
	{
		Nixie(1,2);
		Delay(2);
		Nixie(2,3);
		Delay(2);
//		Nixie(3,4);
//		Delay(2);
//		Nixie(4,5);
//		Delay(2);
//		Nixie(5,0);
//		Delay(2);
//		Nixie(6,1);
//		Delay(2);
		Nixie(7,6);
		Delay(2);
		Nixie(8,7);
		Delay(2);		
	
	}
}
