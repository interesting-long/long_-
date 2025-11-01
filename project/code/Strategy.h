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
/****环岛*****/
extern unsigned char Enter_Flag_Left;
extern unsigned char Enter_Flag_Right;
extern unsigned int Entern_Flag_Time;
extern unsigned int Entern_Delay_Time;
extern unsigned int Entern_Continue_Time;
extern int turn_Value;
extern int Mode_Flag;

/*****惯导速策****/
extern float angle;
extern float delta_angle;
extern int Inertial_Time;
extern int current_angle_time;
extern float angle_buffer1;
extern unsigned char ACC_Flag;
extern unsigned char finsh_Flag;
extern unsigned char Show_Init;

/******记录赛道****/
extern Type_road;
extern unsigned char Last_stact;
extern unsigned char Road_Stat;
extern unsigned char Fires_Init;
extern unsigned char Long_road_Time;
extern float Str_Data;
extern float Bend_Data;
extern float State_Data_Str;
extern float State_Data_Bend;



void if_Cycle(void);
int Help_turn();
void Help_turn2(int temp, int value, int ADC_Flag);
void Help_turn3(int* temp, int value, int value2,int ADC_Flag ,int ADC_Flag2);
int Help_turn_Two(int temp, int value, int value2, int ADC_Flag, int ADC_Flag2);
int State_of_road(void);

typedef enum
{
	str_data,
	wan_data,
	long_str_data
}road_Data;

void Inertial_Navigation(int value);
void Half_State_of_road(int value);
void angle_Get(int value,int Count);
#endif