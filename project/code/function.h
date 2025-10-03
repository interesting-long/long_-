#ifndef __FUNCTION_H__
#define __FUNCTION_H__


#include "zf_common_headfile.h"
extern int Set_T;
extern int T3;
typedef unsigned char 		uint8_t 	;
typedef unsigned int	 	uint16_t 	;
typedef int	 				int16_t 	;
typedef unsigned long int 	uint32_t 	;
typedef long int 			int32_t 	;
typedef struct
{
        float Kp;
        float Ki;
        float Kd;
        float LowPass;

        float Out_P;
        float Out_I;
        float Out_D;

        float PrevError;
        float LastError;
        float Error;
        float LastData;
}PID;
extern PID servo_pid;
/*外部调用函数*/
float unification(void);
float fast_sqrt(float number);
float Normal_PID(PID *PID,float NowData,float Point);
void Protect();
void init_all();
void Turn_mode_Init(void);
void Show_pararm();
void GO_Function(void);
/*内部调用函数*/
void Motor_Init(void);
void Servo_Init();
void CAR_STOP();
void SET_Time();
extern unsigned char Init_Fg;
extern unsigned char Servo_Flag;
extern unsigned char Key_Flag;
extern unsigned char ADC_Show_Flag;
extern int dajiao;
#endif