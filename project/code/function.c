#include "function.h"
int Set_T;
PID servo_pid;
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
    pwm_init(Servo_Pwm,50,Servo_Mide);
}
void CAR_STOP()
{
	MotorL_SetSpeed(0);
	MotorR_SetSpeed(0);
	Ser_Servo_Duty(Servo_Mide);
}

//停车检测
void Protect()
{
    if((ADC_1+ADC_2+ADC_3+ADC_4)<PRO)
	{
		CAR_Mode=STOP;
		Turn_mode_Init();
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
	eeprom_read_Num();
	menu_Init();
	pit_ms_init(TIM0_PIT, 5);
//	pit_ms_init(TIM1_PIT, 20);
}

//切换模式的初始函数
void Turn_mode_Init(void)
{
	CAR_STOP();
	Set_T=0;
	switch(CAR_Mode)
	{
		case STOP:
		{
			CAR_STOP();
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for STOP");
			system_delay_ms(1000);
			tft180_clear(RGB565_WHITE);
			Refesh_arrow();
			menu_display_content();
		}break;
		case GO:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for GO");
			system_delay_ms(1000);
			tft180_clear(RGB565_WHITE);
			
			Motor_Update();
			PID_Update();
			
		}break;
		case GO_Pararm1:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for GOP1");
			system_delay_ms(1000);
			tft180_clear(RGB565_WHITE);
			
			Motor_Update();
			PID_Update();
			
		}break;
		case GO_Pararm2:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for GOP2");
			system_delay_ms(1000);
			tft180_clear(RGB565_WHITE);
			
			Motor_Update();
			PID_Update();
			
		}break;
		case GO_Pararm3:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for GOP3");
			system_delay_ms(1000);
			tft180_clear(RGB565_WHITE);
			
			Motor_Update();
			PID_Update();
			
		}break;
		case TEST_LM:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for Left_motor");
			system_delay_ms(1000);
		}break;
		case TEST_RM:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for Right_motor");
			system_delay_ms(1000);
		}break;
		case TEST_SERVO:
		{
			tft180_clear(RGB565_WHITE);
			tft180_show_string(0,3*16,"Test for Servo");
			system_delay_ms(1000);
		}break;
	}
	
}

void Show_pararm()
{
	tft180_show_string(0,0*16,"ADC1:");tft180_show_int16(5*8,0*16,ADC_1);
	tft180_show_string(0,1*16,"ADC2:");tft180_show_int16(5*8,1*16,ADC_2);
	tft180_show_string(0,2*16,"ADC3:");tft180_show_int16(5*8,2*16,ADC_3);
	tft180_show_string(0,3*16,"ADC4:");tft180_show_int16(5*8,3*16,ADC_4);
	tft180_show_string(0,4*16,"KP:");  tft180_show_float(3*8,4*16,KP,2,2);
	tft180_show_string(0,5*16,"KD:");  tft180_show_float(3*8,5*16,KD,2,2);
}
void SET_Time()
{
	if(CAR_Mode!=STOP && Set_T>Time)
	{
		CAR_Mode=STOP;
		Turn_mode_Init();
	}
}