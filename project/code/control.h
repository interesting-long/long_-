// Header:
// File Name: 
// Author:
// Date:
#ifndef __CONTROL_H__
#define __CONTROL_H__


#include "zf_common_headfile.h"

/***舵机引脚定义*****/
#define Servo_Pwm PWMB_CH2_P51

/****电机引脚定义****/
#define MotorL_pwm2 PWMB_CH1_P01
#define MotorL_pwm1 PWMA_CH2P_P02
#define MotorR_pwm2 PWMB_CH3_P05
#define MotorR_pwm1 PWMA_CH4P_P06
typedef enum
{
	STOP,
	GO,
	TEST_SERVO,
	TEST_PWM,
	GO_Pararm1,
	GO_Pararm2,
	GO_Pararm3,
	ADC_Show
}MODE;
extern unsigned char CAR_Mode;

float pid_control_tyre(float error);
/*外部调用函数*/
float Servo_turn_pid(float Current);
void Motor_Update();
void PID_Update();
//void Ser_Servo_Duty(int value);
/*内部调用函数*/
void MotorL_SetSpeed(int pwm);
void MotorR_SetSpeed(int pwm);
void Ser_Servo_Duty(int value);
#endif