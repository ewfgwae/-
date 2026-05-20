#ifndef __LED_EFFECT_H__
#define __LED_EFFECT_H__

#include "sys_config.h"

/*================ ???? ================*/
void mode_0(void);      // ????
void mode_1(void);      // ????
void mode_2(void);      // ???
void mode_3(void);      // ??
void mode_4(void);      // ????
void mode_5(void);      // ?????
void mode_6(void);      // ????
void mode_7(void);      // ????

void led_all(unsigned char val);
void transition_effect(void);

void mode_run(unsigned char mode);

#endif