#ifndef __KEY_H__
#define __KEY_H__

#include "zf_common_headfile.h"
#define Flag_press_time 80
#define Flag_trigg_time 10
#define ANY_ITEM 0xFF
typedef enum
{
	State_Release,
	State_Press_dou,
	State_Press,
	State_Release_dou
} Key_State;

extern unsigned char State;
extern unsigned char keynumber;
extern unsigned char Key_count;
extern unsigned char CAR_Mode;
extern unsigned char Init_Flag;
/*外部调用函数*/
void Key_scaner(void);
/*内部调用函数*/
unsigned char Key_Number(void);
void Turn_mode(void);
#endif