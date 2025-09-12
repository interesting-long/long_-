#include "control.h"

PID servo_pid;

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
void Servo_turn_pid(float point,int min,int max)
{
    float servo_value;
    int temp;
	if(min>max)
	{
		temp=max;
		max=min;
		min=temp;
	}
    servo_value=Normal_PID(&servo_pid,point,0.0);
    temp=func_limit_ab(servo_value,min,max);
	pwm_set_duty(Servo_Pwm,Servo_Mide-temp);
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
	MotorR_SetSpeed(100*MorR_Max);
	MotorL_SetSpeed(100*MorL_Max);
}