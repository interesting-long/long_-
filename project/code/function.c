#include "function.h"


/*������������PID����
 * ����1���ṹ������ĵ�ַ
 * ����2����ǰֵ
 * ����3��Ŀ��ֵ
 * ���ӣ�Normal_PID(&servo_pid,MID_W-mid,0);//��servo��pid��������Ϊ�����߼�Ȩֵ������ֵ֮������ΪĿ��ֵ��0
 */
float Normal_PID(PID *PID,float NowData,float Point)
{

    PID->LastError=PID->Error;
    PID->Error = Point - NowData;
    PID->Out_D=PID->Error- PID->LastError;              //D��
    PID->Out_I+=PID->Error;                             //I��
    PID->Out_P=PID->Error;                              //P��
    return (PID->Kp * PID->Out_P + PID->Ki*PID->Out_I + PID->Kd * PID->Out_D);
}
/* ��������һ������
 * ����1����
 * ����ֵ����
 * ����/���ã�����ȡ��ADCֵ����Ϊ����
 */
float unification(void) 
{
    float error_val;
    float left_1;
    float left_2;
    float right_2;
    float right_1;
    
    left_1  = (float)filtered_adc[0];
    left_2  = (float)filtered_adc[1];
    right_2 = (float)filtered_adc[2];
    right_1 = (float)filtered_adc[3];
    
    error_val = (fast_sqrt(left_1) - fast_sqrt(right_1)) / (left_2 + right_2);
    
    return error_val;
}
/*���ٿ�������*/
float fast_sqrt(float number) 
{
    unsigned long i;
    float x = number;
    
    if (number <= 0.0f) return 0.0f;
    
    memcpy(&i, &x, 4);
    
    i = 532267893U + (i >> 1);
    
    memcpy(&x, &i, 4);

    x = 0.5f * (x + number / x);
    return x;
}
/*�����ʼ��*/
void Motor_Init(void)
{
    pwm_init(Servo_Pwm,50,Servo_Mide);
    pwm_init(MotorL_pwm2, 17000, 0);
    pwm_init(MotorL_pwm1, 17000, 0);
    pwm_init(MotorR_pwm2, 17000, 0);
    pwm_init(MotorR_pwm1, 17000, 0);
}

void Servo_Init()
{
    system_delay_init();
    pwm_init(Servo_Pwm,50,Servo_Mide+65);
}
void CAR_STOP()
{
	MotorL_SetSpeed(0);
	MotorR_SetSpeed(0);
	Ser_Servo_Duty(Servo_Mide);
}
void CAR_Init()
{
	Ser_Servo_Duty(Servo_Mide);
}
//ͣ�����
void Protect()
{
    if((ADC_1+ADC_2+ADC_3+ADC_4)<10)
	{
		while(CAR_Mode==GO)
		{
			CAR_STOP();
		}
	}
}
/*�Զ����ʼ��������*/
void init_all()
{
	Motor_Init();
	Servo_Init();
	iap_init();
	ADC_GetInit();
	tft180_init();
	tft180_set_color(RGB565_RED,RGB565_WHITE);
//	eeprom_read_Num();
	menu_Init();
	pit_ms_init(TIM0_PIT, 5);
}