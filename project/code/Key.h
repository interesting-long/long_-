#ifndef __KEY_H__
#define __KEY_H__

#include "zf_common_headfile.h"

typedef enum
{
	State_Release,
	State_Press_dou,
	State_Press,
	State_Release_dou
} Key_State;

#define Flag_press_time 50
#define Flag_trigg_time 20

/*****ö��****/
#define GO 1
#define STOP 2

extern unsigned char State;
extern unsigned char keynumber;
extern unsigned char Key_count;
extern unsigned char CAR_Mode;
/*�ⲿ���ú���*/
void Key_scaner(void);
/*�ڲ����ú���*/
unsigned char Key_Number(void);

#endif