#ifndef __FUNCTION_H__
#define __FUNCTION_H__


#include "zf_common_headfile.h"
extern int Set_T;
extern int T3;
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
extern unsigned char Show_Fg;
extern float dajiao;
#endif