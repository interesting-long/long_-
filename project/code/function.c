#include "function.h"


/*函数：常见的PID计算
 * 参数1：结构体变量的地址
 * 参数2：当前值
 * 参数3：目标值
 * 例子：Normal_PID(&servo_pid,MID_W-mid,0);//将servo的pid参数设置为以中线加权值和中线值之差设置为目标值：0
 */
float Normal_PID(PID *PID,float NowData,float Point)
{

    PID->LastError=PID->Error;
    PID->Error = Point - NowData;
    PID->Out_D=PID->Error- PID->LastError;              //D项
    PID->Out_I+=PID->Error;                             //I项
    PID->Out_P=PID->Error;                              //P项
    return (PID->Kp * PID->Out_P + PID->Ki*PID->Out_I + PID->Kd * PID->Out_D);
}
/* 函数：归一化函数
 * 参数1：无
 * 返回值：无
 * 例子/作用：将读取的ADC值量化为距离
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
/*快速开方函数*/
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
/*电机初始化*/
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
//停车检测
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
/*自定义初始化函数库*/
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