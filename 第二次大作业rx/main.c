#include "si24r2.h"

/* LED?? */
sbit LED = P2^7;

void main(void)
{
    unsigned char rxBuf[PAYLOAD_LEN];
    unsigned char status;
    
    LED = 1;            /* LED???? */
    
    SI24R2_Init();
    
    /* ????????,??????? */
    if(!SI24R2_Check())
    {
        while(1)
        {
            LED = ~LED;
            DelayMs(100);
        }
    }
    
    SI24R2_SetRXMode();
    
    while(1)
    {
        if(SI24R2_RxPacket(rxBuf))
        {
            /* ????,LED?? */
            LED = ~LED;
            
            /* ????????,?????? */
            /* if(rxBuf[1] == 0xAA && rxBuf[2] == 0x55) { LED = ~LED; } */
        }
        
        DelayMs(10);
    }
}