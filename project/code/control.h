// Header:
// File Name: 
// Author:
// Date:
#ifndef __CONTROL_H__
#define __CONTROL_H__


#include "zf_common_headfile.h"

/***������Ŷ���*****/
#define Servo_Pwm PWMB_CH2_P51

/****������Ŷ���****/
#define MotorL_pwm2 PWMA_CH3N_P05
#define MotorL_pwm1 PWMA_CH4P_P06
#define MotorR_pwm2 PWMA_CH1N_P01
#define MotorR_pwm1 PWMA_CH2P_P02
/******************/
#define Motor_Max 6000
typedef enum
{
	STOP,
	GO,
	TEST_SERVO,
	TEST_PWM,
	GO_Pararm1,
	GO_Pararm2,
	GO_Pararm3,
	ADC_Show,
	Seta_Servo
}MODE;
extern unsigned char CAR_Mode;

float pid_control_tyre(float error);
/*�ⲿ���ú���*/
int Servo_turn_pid(float Current);
void Motor_Update(char X);
void PID_Update();
void Cycle_Update(void);
//int Motor_left_pid(int point);
//int Motor_Right_pid(int point);
int Motor_Left_pi_control(int point);
int Motor_Right_pi_control(int point);
/*�ڲ����ú���*/
void MotorL_SetSpeed(int pwm);
void MotorR_SetSpeed(int pwm);
void Ser_Servo_Duty(int value);
#endif