#include "key_handler.h"

unsigned char key0_scan(void)
{
    unsigned int press_t = 0;
    
    if(KEY_MODE != 0) return KEY_EVT_NONE;
    
    delay_ms(10);           // ??
    if(KEY_MODE != 0) return KEY_EVT_NONE;
    
    // ??
    while(KEY_MODE == 0 && press_t < 1200)
    {
        delay_ms(1);
        press_t++;
    }
    
    // ????
    while(KEY_MODE == 0);
    delay_ms(10);
    
    if(press_t >= 800)
        return KEY_EVT_LONG;
    else if(press_t >= 30)
        return KEY_EVT_SHORT;
    
    return KEY_EVT_NONE;
}

unsigned char key1_scan(void)
{
    unsigned int press_t = 0;
    
    if(KEY_PARM != 0) return KEY_EVT_NONE;
    
    delay_ms(10);
    if(KEY_PARM != 0) return KEY_EVT_NONE;
    
    while(KEY_PARM == 0 && press_t < 500)
    {
        delay_ms(1);
        press_t++;
    }
    
    while(KEY_PARM == 0);
    delay_ms(10);
    
    if(press_t >= 30)
        return KEY_EVT_SHORT;
    
    return KEY_EVT_NONE;
}