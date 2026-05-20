#ifndef __SYS_CONFIG_H__
#define __SYS_CONFIG_H__

#include <reg52.h>
#include <intrins.h>

sbit KEY_MODE = P3^2;   
sbit KEY_PARM = P3^3;   
#define LED_PORT P1

#define FOSC        11059200UL
#define MODE_NUM    8
#define PWM_LEVEL   16

extern unsigned char g_mode;        
extern unsigned char g_speed;       
extern unsigned char g_led_buf;     
extern bit g_transition;            
extern bit g_key1_trig;             

extern unsigned int g_int0_cnt;
extern unsigned int g_int1_cnt;

extern bit g_key0_short;
extern bit g_key0_long;
extern bit g_key0_double;

extern unsigned char g_pos;
extern unsigned char g_dir;
extern unsigned char g_bright;
extern unsigned char g_fade_dir;

void delay_ms(unsigned int ms);
void delay_us(unsigned char us);

void led_all(unsigned char val);
void transition_effect(void);

#endif