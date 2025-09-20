#ifndef __CONTROL_H__
#define __CONTROL_H__


#include "zf_common_headfile.h"

/***������Ŷ���*****/
#define Servo_Pwm PWMB_CH2_P51

/****������Ŷ���****/
#define MotorL_pwm2 PWMB_CH1_P01
#define MotorL_pwm1 PWMA_CH2P_P02
#define MotorR_pwm2 PWMB_CH3_P05
#define MotorR_pwm1 PWMA_CH4P_P06
typedef enum
{
	STOP,
	GO,
	TEST_SERVO,
	TEST_LM,
	TEST_RM,
	GO_Pararm1,
	GO_Pararm2,
	GO_Pararm3
}MODE;
extern unsigned char CAR_Mode;

/*�ⲿ���ú���*/
void Servo_turn_pid(float Current,int min,int max);
void Motor_Update();
void PID_Update();
void Ser_Servo_Duty(int value);
/*�ڲ����ú���*/
void MotorL_SetSpeed(int pwm);
void MotorR_SetSpeed(int pwm);
void Ser_Servo_Duty(int value);
#endif