#include <reg52.h>	  //???????52??????????
#include <intrins.h>

void Delay10ms(unsigned int c);  


void main()
{
	char num=0;
	unsigned char LED;
	LED = 0xfe;	 
 	while (1)
	{

     P0 = LED;
		if(num==0)
		{
			LED=LED<<1;
			Delay10ms(50);
			if(LED==0x00)
			{
				num=1;
			}
		}
		else
		{
			LED=LED>>1;
			LED |= 0x80;
			Delay10ms(50);
			if(LED==0xfe)
			{
				num=0;
			}
			
		}
   		 		 
	}
}
void Delay10ms(unsigned int c)  
{
    unsigned char a, b;
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}
           
	}       
}