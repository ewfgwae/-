#include "si24r1_89.h"

/* 板上LED/按键 */
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;

void main(void)
{
    u8 buf[32] = {0};
    u8 i;

    SI24R1_Init();

    /* 检测SI24R1模块, 快闪1次=在线, 慢闪3次=不在线 */
    if(SI24R1_Check())
    {
        LED1 = 0; delay_ms(100);
        LED1 = 1;
    }
    else
    {
        for(i = 0; i < 3; i++)
        {
            LED1 = 0; delay_ms(500);
            LED1 = 1; delay_ms(500);
        }
        while(1);   /* 模块不在线, 停在这里 */
    }

    SI24R1_RX_Mode();

    while(1)
    {
        if(!KEY1 || !KEY2)
        {
            delay_ms(10);
            if(!KEY1)
            {
                buf[0] = 0x55;
                SI24R1_TX_Mode();
                SI24R1_TxPacket(buf);
                delay_ms(200);
            }
            if(!KEY2)
            {
                buf[0] = 0xAA;
                SI24R1_TX_Mode();
                SI24R1_TxPacket(buf);
                delay_ms(200);
            }
            buf[0] = 0;
            SI24R1_RX_Mode();
        }

        if(!SI24R1_RxPacket(buf))
        {
            switch(buf[0])
            {
                case 0x55:
                    LED1 = 0; delay_ms(100);
                    LED1 = 1; delay_ms(100);
                    break;
                case 0xAA:
                    LED2 = 0; delay_ms(100);
                    LED2 = 1; delay_ms(100);
                    break;
                default:
                    break;
            }
            buf[0] = 0;
        }
    }
}
