#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "zf_common_headfile.h"

#define abs(a) ((a) < 0 ? -(a) : (a))

typedef enum
{
	APPROACH,  // 
    Right_ENTER,
	Left_ENTER,
    EXIT       //
}Cycle_State;
extern float uni;
extern float last_uni;
extern unsigned char Enter_Flag_Left;
extern unsigned char Enter_Flag_Right;
void if_Cycle(void);
int Help_turn();
#endif