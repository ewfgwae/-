#include "interrupt.h"

void Timer0_ISR(void) interrupt 1
{
    static unsigned char tick = 0;
    static unsigned char pwm_cnt = 0;
    
    TH0 = 0xFC;
    TL0 = 0x18;
    
    pwm_cnt++;
    if(pwm_cnt >= PWM_LEVEL) pwm_cnt = 0;
    
    tick++;
    if(tick >= (11 - g_speed))
    {
        tick = 0;
        if(!g_transition && g_mode != 7)
        {
            mode_run(g_mode);
        }
    }
    
    if(g_mode != 7)
    {
        LED_PORT = g_led_buf;
    }
}

void INT0_ISR(void) interrupt 0
{
    unsigned char evt;
		unsigned char i;
    
    g_int0_cnt++;
    
    evt = key0_scan();
    
    if(evt == KEY_EVT_SHORT)
    {
        g_transition = 1;
        g_mode++;
        if(g_mode >= MODE_NUM) g_mode = 0;
        
        transition_effect();
        g_transition = 0;
    }
    else if(evt == KEY_EVT_LONG)
    {
        g_mode = 0;
        g_speed = 3;
        g_int0_cnt = 0;
        g_int1_cnt = 0;
        
        for(i = 0; i < 3; i++)
        {
            LED_PORT = 0x55; delay_ms(100);
            LED_PORT = 0xAA; delay_ms(100);
        }
        LED_PORT = 0xFF;
    }
}

void INT1_ISR(void) interrupt 2
{
    unsigned char evt;
		unsigned char i;
    
    g_int1_cnt++;
    
    evt = key1_scan();
    
    if(evt == KEY_EVT_SHORT)
    {
        if(g_mode == 7)
        {
            g_key1_trig = 1;
        }
        else
        {
            g_speed++;
            if(g_speed > 10) g_speed = 1;
            
            LED_PORT = 0xFF;
            for(i = 0; i < g_speed; i++)
            {
                LED_PORT = 0x00; delay_ms(80);
                LED_PORT = 0xFF; delay_ms(80);
            }
        }
    }
}

void int0_init(void)
{
    IT0 = 1;
    EX0 = 1;
    PX0 = 1;
}

void int1_init(void)
{
    IT1 = 1;
    EX1 = 1;
    PX1 = 0;
}

void timer0_init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    ET0 = 1;
    TR0 = 1;
}