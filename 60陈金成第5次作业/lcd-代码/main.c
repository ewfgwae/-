#include <REGX52.H>
#include "LCD1602.h"	

extern unsigned int g_busy_count;

void main(void)
{
    unsigned int last_count = 0;
    
    LCD_Init();                 
    
    LCD_ShowString(1, 1, "BusyTest:");
    
    while (1) {
        LCD1602_Clear_2LINE();    
        
        last_count = g_busy_count;
        
        LCD_ShowNum(2, 1, last_count, 5);
        
        if (last_count > 0) {
            LCD_ShowString(2, 8, "OK "); 
        } else {
            LCD_ShowString(2, 8, "NG "); 
        }
		}
}


