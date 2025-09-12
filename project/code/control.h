#ifndef __CONTROL_H__
#define __CONTROL_H__


#include "zf_common_headfile.h"

/***舵机引脚定义*****/
#define Servo_Pwm PWMA_CH1P_P00

/****电机引脚定义****/
#define MotorL_pwm2 PWMB_CH2_P51
#define MotorL_pwm1 PWMB_CH4_P53
#define MotorR_pwm2 PWMB_CH1_P50
#define MotorR_pwm1 PWMB_CH3_P52

/*外部调用函数*/
void Servo_turn_pid(unsigned char point,int min,int max);
void Motor_Update();
void Ser_Servo_Duty(int value);
/*内部调用函数*/
void MotorL_SetSpeed(int pwm);
void MotorR_SetSpeed(int pwm);
void Ser_Servo_Duty(int value);
#endif