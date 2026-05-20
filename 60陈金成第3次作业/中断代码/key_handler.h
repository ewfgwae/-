#ifndef __KEY_HANDLER_H__
#define __KEY_HANDLER_H__

#include "sys_config.h"

/*================ ?????? ================*/
#define KEY_EVT_NONE    0
#define KEY_EVT_SHORT   1
#define KEY_EVT_LONG    2
#define KEY_EVT_DOUBLE  3

/*================ ???? ================*/
unsigned char key0_scan(void);      // ??INT0??,??????
unsigned char key1_scan(void);      // ??INT1??,??????

#endif