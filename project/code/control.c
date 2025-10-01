#include "control.h"

unsigned char CAR_Mode=STOP;
void Ser_Servo_Duty(int value)
{
    pwm_set_duty(Servo_Pwm,value);
}
 /*函数：舵机的pid控制
 * 作用：利用电磁归一化后的信号控制舵机，
 * 参数1：设定的归一化目标值
 * 参数2：舵机最小转向值
 * 参数3：舵机最大转向值
 * 例子：Servo_turn_pid(变量,-80,80);
 * 将变量的值与0进行对比，输出信号控制舵机,而舵机的限幅是正负80
 */
float Servo_turn_pid(float Current)
{
	float servo_value;
	float temp=0;
	servo_value=Normal_PID(&servo_pid,Current,0.0);
	temp=func_limit_ab(servo_value,-85,87);
	
//	pwm_set_duty(Servo_Pwm,Servo_Mide-temp);
	return temp;
	
}


/*
 * 函数功能：左路电机PWM设置
 * 函数名称：MotorL_SetSpeed(unsigned char);
 * 输入参数：想要的PWM值
 * 输出参数：无
 */
void MotorL_SetSpeed(int pwm)
{
    if(pwm>=0)
    {
        pwm_set_duty(MotorL_pwm1,pwm);
        pwm_set_duty(MotorL_pwm2,0);
    }
    else
    {
        pwm_set_duty(MotorL_pwm2,-pwm);
        pwm_set_duty(MotorL_pwm1,0);
    }
}
/*
 * 函数功能：右路电机PWM设置
 * 函数名称：MotorR_SetSpeed(unsigned char);
 * 输入参数：想要的PWM值
 * 输出参数：无
 */
void MotorR_SetSpeed(int pwm)
{
    if(pwm>0)
    {
        pwm_set_duty(MotorR_pwm1,pwm);
        pwm_set_duty(MotorR_pwm2,0);
    }
    else
    {
        pwm_set_duty(MotorR_pwm2,-pwm);
        pwm_set_duty(MotorR_pwm1,0);
    }
}
/*
 * 函数功能：电机驱动更新
 * 函数名称：Motor_Update();
 * 输入参数：无
 * 输出参数：无
 * 可以进行拓展，写速度策略
 */
void Motor_Update()
{  
	switch(CAR_Mode)
	{
		case GO:
		{
			MotorR_SetSpeed(100*ML);
			MotorL_SetSpeed(100*MR);
		}break;
		case GO_Pararm1:
		{
			MotorR_SetSpeed(100*ML1);
			MotorL_SetSpeed(100*MR1);
		}break;
		case GO_Pararm2:
		{
			MotorR_SetSpeed(100*ML2);
			MotorL_SetSpeed(100*MR2);
		}break;
		case GO_Pararm3:
		{
			MotorR_SetSpeed(100*ML3);
			MotorL_SetSpeed(100*MR3);
		}break;
	}
	
}
void PID_Update()
{  
	switch(CAR_Mode)
	{
		case GO:
		{
			servo_pid.Kp = KP;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD;
		}break;
		case GO_Pararm1:
		{
			servo_pid.Kp = KP1;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD1;
		}break;
		case GO_Pararm2:
		{
			servo_pid.Kp = KP2;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD2;
		}break;
		case GO_Pararm3:
		{
			servo_pid.Kp = KP3;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD3;
		}break;
	}
	
}
