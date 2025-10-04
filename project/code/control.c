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
int Servo_turn_pid(float Current)
{
    // ��Ƶ�����ʵĽṹ���Ա���ص��ֲ�����
    float kp = servo_pid.Kp;           // ���浽���ٴ洢��
    float kd = servo_pid.Kd;
    float last_error = servo_pid.LastError;
    float error = Current;
	float temp ;
    
    // ʹ�þֲ���������
    float out = kp * error + kd * (error - last_error)+Help_turn();
    
    // д�ر�Ҫ�Ľṹ���Ա
    servo_pid.LastError = error;
    
    temp = func_limit_ab(out, Servo_min, Servo_max);
    return (int)(temp + (temp >= 0 ? 0.5f : -0.5f));
}
//int Servo_turn_pid(float Current)
//{
//    // �Ŵ����Ϊ����
//    int32_t error = (int32_t)(Current * 100);             // ��100
//    int32_t last_error = (int32_t)(servo_pid.LastError);  // ��100
//    int32_t kp = (int32_t)(servo_pid.Kp * 100);           // ��100
//    int32_t kd = (int32_t)(servo_pid.Kd * 100);           // ��100

//    // ʹ��32λ����ֹ��� ?
//    int32_t out = kp * error + kd * (error - last_error);  // ��10000

//    // �������
//    servo_pid.LastError = error; // ? ���� ��100 �����洢��ʽ

//    // ���ص� ��1 ����������� -100~+100��
//    out = out / 10000;

//    // �޷������� Servo_min / Servo_max ������ ��1 ����ķ�Χ�� ?
//    if (out > Servo_max) out = Servo_max;
//    if (out < Servo_min) out = Servo_min;

//    return (int)out;  // ? ���շ��ػ��� "��������"
//}

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
