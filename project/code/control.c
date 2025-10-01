#include "control.h"

unsigned char CAR_Mode=STOP;
void Ser_Servo_Duty(int value)
{
    pwm_set_duty(Servo_Pwm,value);
}
 /*�����������pid����
 * ���ã����õ�Ź�һ������źſ��ƶ����
 * ����1���趨�Ĺ�һ��Ŀ��ֵ
 * ����2�������Сת��ֵ
 * ����3��������ת��ֵ
 * ���ӣ�Servo_turn_pid(����,-80,80);
 * ��������ֵ��0���жԱȣ�����źſ��ƶ��,��������޷�������80
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
 * �������ܣ���·���PWM����
 * �������ƣ�MotorL_SetSpeed(unsigned char);
 * �����������Ҫ��PWMֵ
 * �����������
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
 * �������ܣ���·���PWM����
 * �������ƣ�MotorR_SetSpeed(unsigned char);
 * �����������Ҫ��PWMֵ
 * �����������
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
 * �������ܣ������������
 * �������ƣ�Motor_Update();
 * �����������
 * �����������
 * ���Խ�����չ��д�ٶȲ���
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
