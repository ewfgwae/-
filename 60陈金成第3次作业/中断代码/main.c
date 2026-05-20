#include "sys_config.h"
#include "interrupt.h"
#include "led_effect.h"

unsigned char g_mode = 0;
unsigned char g_speed = 3;
unsigned char g_led_buf = 0xFF;
bit g_transition = 0;
bit g_key1_trig = 0;

unsigned int g_int0_cnt = 0;
unsigned int g_int1_cnt = 0;

bit g_key0_short = 0;
bit g_key0_long = 0;
bit g_key0_double = 0;

unsigned char g_pos = 0;
unsigned char g_dir = 1;
unsigned char g_bright = 0;
unsigned char g_fade_dir = 1;

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}

void delay_us(unsigned char us)
{
    while(us--)
    {
        _nop_(); _nop_(); _nop_(); _nop_();
    }
}

void power_on_test(void)
{
    unsigned char i;
    
    for(i = 0; i < 8; i++)
    {
        LED_PORT = ~(0x01 << i);
        delay_ms(60);
    }
    for(i = 0; i < 8; i++)
    {
        LED_PORT = ~(0x80 >> i);
        delay_ms(60);
    }
    LED_PORT = 0x00;
    delay_ms(200);
    LED_PORT = 0xFF;
}

void sys_init(void)
{
    timer0_init();
    int0_init();
    int1_init();
    EA = 1;
    LED_PORT = 0xFF;
}

void main(void)
{
    sys_init();
    power_on_test();
    
    while(1)
    {
        _nop_();
    }
}