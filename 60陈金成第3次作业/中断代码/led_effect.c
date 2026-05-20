#include "led_effect.h"

void led_all(unsigned char val)
{
    g_led_buf = val;
}

void transition_effect(void)
{
    unsigned char i, j;
    for(i = 0; i < 3; i++)
    {
        LED_PORT = 0x00; delay_ms(30);
        LED_PORT = 0xFF; delay_ms(30);
    }
    for(j = 0; j < 8; j++)
    {
        LED_PORT = ~(0x80 >> j);
        delay_ms(40);
    }
    LED_PORT = 0xFF;
    delay_ms(100);
}

void mode_0(void)
{
    static unsigned char cnt = 0;
    cnt++;
    if(cnt >= (11 - g_speed) * 3)
    {
        cnt = 0;
        g_led_buf = (0x01 << g_pos);
        g_pos++;
        if(g_pos >= 8) g_pos = 0;
    }
}

void mode_1(void)
{
    static unsigned char cnt = 0;
    cnt++;
    if(cnt >= (11 - g_speed) * 2)
    {
        cnt = 0;
        if(g_dir)
        {
            g_led_buf = (0x01 << g_pos) | (0x80 >> g_pos);
            g_pos++;
            if(g_pos >= 4) { g_pos = 2; g_dir = 0; }
        }
        else
        {
            g_led_buf = (0x01 << g_pos) | (0x80 >> g_pos);
            g_pos--;
            if(g_pos == 0) { g_dir = 1; }
        }
    }
}

void mode_2(void)
{
    static unsigned int cnt = 0;
    cnt++;
    if(cnt >= (11 - g_speed) * 8)
    {
        cnt = 0;
        if(g_fade_dir)
        {
            g_bright++;
            if(g_bright >= PWM_LEVEL-1) g_fade_dir = 0;
        }
        else
        {
            g_bright--;
            if(g_bright <= 1) g_fade_dir = 1;
        }
    }
    g_led_buf = (g_bright > 0) ? 0x00 : 0xFF;  
}

void mode_3(void)
{
    static unsigned char cnt = 0;
    cnt++;
    if(cnt >= (11 - g_speed) * 4)
    {
        cnt = 0;
        if(g_dir)
        {
            g_led_buf &= ~(0x01 << g_pos);
            g_pos++;
            if(g_pos >= 8) { g_dir = 0; delay_ms(200); }
        }
        else
        {
            g_led_buf = 0xFF;
            g_pos = 0;
            g_dir = 1;
            delay_ms(200);
        }
    }
}

void mode_4(void)
{
    static unsigned char cnt = 0;
    static unsigned char trail[8] = {0};
    unsigned char i;
    
    cnt++;
    if(cnt >= (11 - g_speed) * 2)
    {
        cnt = 0;
        for(i = 7; i > 0; i--) trail[i] = trail[i-1];
        trail[0] = g_pos;
        
        g_led_buf = 0xFF;
        for(i = 0; i < 4; i++)
        {
            if(trail[i] < 8)
                g_led_buf &= ~(0x01 << trail[i]);
        }
        
        if(g_dir) { g_pos++; if(g_pos >= 8) { g_pos = 6; g_dir = 0; } }
        else      { g_pos--; if(g_pos == 0) { g_dir = 1; } }
    }
}

void mode_5(void)
{
    static unsigned int last_cnt = 0;
    if(g_int0_cnt != last_cnt)
    {
        last_cnt = g_int0_cnt;
        g_led_buf = ~(unsigned char)(g_int0_cnt & 0xFF);
        delay_ms(50);
    }
    else
    {
        g_led_buf = ~(unsigned char)(g_int0_cnt & 0xFF);
    }
}

void mode_6(void)
{
    static unsigned char cnt = 0;
    static unsigned char seed = 0x5A;
    cnt++;
    if(cnt >= (11 - g_speed))
    {
        cnt = 0;
        seed ^= (seed << 3);
        seed ^= (seed >> 5);
        seed ^= (seed << 2);
        g_led_buf = seed;
    }
}

void mode_7(void)
{
    unsigned char i;
    static bit in_demo = 0;
    if(g_key1_trig && !in_demo)
    {
        in_demo = 1;
        g_key1_trig = 0;
        
        for(i = 0; i < 8; i++)
        {
            LED_PORT = ~(0x01 << i);
            delay_ms(300);
        }
        LED_PORT = 0xFF;
        in_demo = 0;
    }
    else
    {
        g_led_buf = 0xE7;
    }
}

void mode_run(unsigned char mode)
{
    switch(mode)
    {
        case 0: mode_0(); break;
        case 1: mode_1(); break;
        case 2: mode_2(); break;
        case 3: mode_3(); break;
        case 4: mode_4(); break;
        case 5: mode_5(); break;
        case 6: mode_6(); break;
        case 7: mode_7(); break;
        default: mode_0(); break;
    }
}