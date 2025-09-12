#ifndef __FUNCTION_H__
#define __FUNCTION_H__


#include "zf_common_headfile.h"

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

/*�ⲿ���ú���*/
float unification(void);
float fast_sqrt(float number);
float Normal_PID(PID *PID,float NowData,float Point);
void CAR_STOP();
void CAR_Init();
void Protect();
void init_all();
/*�ڲ����ú���*/
void Motor_Init(void);
void Servo_Init();

#endif