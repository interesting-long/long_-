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
extern unsigned char Protect_Flag_Cycle;
/*****惯导速策****/
extern unsigned char Acclerate_Flag;

/******记录赛道****/
extern long int all_road;
extern float delta_angle;
extern float angle;
extern unsigned char Max_Item;
extern unsigned char Guan_Dao_Show_Item;
extern int Now_Item;
extern int Str_Data_Buffer;
extern float angle_buffer;
//int Straightaways_Time=0;
//int Turnways_Time=0;
extern unsigned char Long_Flag;
extern unsigned char Short_Flag;

extern long int Short_road_Data[30];
extern long int Long_road_Data[30];
extern long int Long_short_Data[30];
extern long int Turn_road_Data[30];
extern long int All_road_Data[100];
extern unsigned char All_road_Flag[100];
extern float All_angle_Data[100];

extern Now_State_Road;
extern unsigned char Last_State_Road;

void if_Cycle(void);
int Help_turn();
void Help_turn2(int temp, int value, int ADC_Flag);
void Help_turn3(int* temp, int value, int value2,int ADC_Flag ,int ADC_Flag2);
int Help_turn_Two(int temp, int value, int value2, int ADC_Flag, int ADC_Flag2);
void State_of_road(void);

typedef enum
{
	Stright,
	Long_Stright,
	Short_Stright,
	Turn_Ways
}road_Data;

void Inertial_Navigation(int value);
void Half_State_of_road(int value);
void angle_Get(void);
#endif