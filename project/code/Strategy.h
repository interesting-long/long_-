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
typedef enum
{
//	Normal_Str,
	Short_Str,
	Long_Str,
	Short_Bend,
	Long_Bend
}Road_State;
extern float uni;
extern float last_uni;
extern unsigned char Enter_Flag_Left;
extern unsigned char Enter_Flag_Right;
extern unsigned int Entern_Flag_Time;
extern unsigned int Entern_Delay_Time;
extern unsigned int Entern_Continue_Time;
extern int turn_Value;
extern int Mode_Flag;
void if_Cycle(void);
int Help_turn();
int Help_turn2(int temp,int value,int ADC_Flag);
void State_of_road(void);
#endif