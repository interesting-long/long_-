#include "function.h"
int Set_T=0;
int T3=0;
int PRO_Set_Time=0;
PID servo_pid;
int dajiao=0;

unsigned char Servo_Flag=0;

unsigned char ADC_Show_Flag=0;
unsigned char Key_Flag=1;
unsigned char Init_Fg=0;

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
    int16_t left_1  = filtered_adc[0];
    int16_t left_2  = filtered_adc[1];
    int16_t right_2 = filtered_adc[2];
    int16_t right_1 = filtered_adc[3];

    int32_t he = left_2 + right_2;
    if (he < 10) return 0.0f;
    return (fast_sqrt(left_1) - fast_sqrt(right_1)) * (100.0f / he);
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
	if(CAR_Mode!= STOP)
	{
		if((ADC_1+ADC_2+ADC_3+ADC_4)<Pro )
		{
			CAR_Mode=STOP;
			Turn_mode_Init();
		}
	}
}
/*自定义初始化函数库*/
void init_all()
{
	EA=0;
	system_delay_ms(10);
	Motor_Init();
	Servo_Init();
	PT1H = 0;
    PT0H = 1;
	system_delay_ms(5);
	Buzzer_Init();
	Buzzer_OFF();
	
	ADC_GetInit();
	tft180_init();
	system_delay_ms(100);
	tft180_set_color(RGB565_RED,RGB565_WHITE);
//	eeprom_read_Num();
	menu_Init();
	system_delay_ms(10);
	
	pit_ms_init(TIM0_PIT, 20);
	pit_ms_init(TIM1_PIT, 5);
	system_delay_ms(5);
    EA=1;
	
}
void show_test_info(const char* info) 
{
    tft180_clear(RGB565_WHITE);
    system_delay_ms(5);
    tft180_show_string(0, 3*16, info);
    system_delay_ms(1000);
    tft180_clear(RGB565_WHITE);
}
//切换模式的初始函数
void Turn_mode_Init(void)
{
	EA=0;
	Set_T=0;
	switch(CAR_Mode)
	{
		case STOP:
		{
			CAR_STOP();
			Buzzer_OFF();
			ADC_Show_Flag=0;
			Key_Flag=1;
			Servo_Flag=0;
			show_test_info("Test for Stop");
			Refesh_arrow();
			menu_display_content();
			Show_bujin();
			CAR_STOP();
			break;
		}
		case GO:
		{
			ADC_Show_Flag=0;
			Key_Flag=0;
			Servo_Flag=1;
			show_test_info("Test for GO");
			
			
			Motor_Update(0);
			PID_Update();
			Cycle_Update();
			break;
		}
		case GO_Pararm1:
		{
			ADC_Show_Flag=0;
			Key_Flag=0;
			Servo_Flag=1;
			show_test_info("Test for GOP1");
			
			Motor_Update(0);
			PID_Update();
			Cycle_Update();
			break;
		}
		case GO_Pararm2:
		{
			ADC_Show_Flag=0;
			Key_Flag=0;
			Servo_Flag=1;
			show_test_info("Test for GOP2");
			
			Motor_Update(0);
			PID_Update();
			Cycle_Update();
			break;
		}
		case GO_Pararm3:
		{
			ADC_Show_Flag=0;
			Key_Flag=0;
			Servo_Flag=1;
			show_test_info("Test for GOP3");
			
			Motor_Update(0);
			PID_Update();
			Cycle_Update();
			break;
		}
		case TEST_PWM:
		{
			Key_Flag=1;
			Servo_Flag=0;
			show_test_info("Test for PWM_TEST");
			
			break;
		}
		case TEST_SERVO:
		{
			Key_Flag=1;
			Servo_Flag=0;
			show_test_info("Test for Servo");
			break;
		}
		case ADC_Show:
		{
			ADC_Show_Flag=1;
			Key_Flag=1;
			Servo_Flag=0;
			show_test_info("Test for ADC_Show");
			break;
		}
		case Seta_Servo:
		{
			Key_Flag=1;
			Servo_Flag=0;
			show_test_info("Test for Seta_Servo");
			break;
		}
	}
	EA=1;
}

void Show_pararm()
{
	switch(CAR_Mode)
	{
		case STOP:break;
		case TEST_PWM:
		{
			tft180_show_string(0,4*16,"LPW:");  tft180_show_float(5*8,4*16,Test_LPWM,2,2);
			tft180_show_string(0,5*16,"RPW:");  tft180_show_float(5*8,5*16,Test_RPWM,2,2);
		}break;
		case GO:
		{
			tft180_show_string(0,1*16,"cha:");tft180_show_float(5*8,1*16,dajiao,2,2);
			tft180_show_string(0,2*16,"err:");  tft180_show_float(5*8,2*16,unification(),2,2);
			tft180_show_string(0,4*16,"KP:");  tft180_show_float(5*8,4*16,KP,2,2);
			tft180_show_string(0,5*16,"KD:");  tft180_show_float(5*8,5*16,KD,2,2);
			tft180_show_string(0,3*16,"TIME:");  tft180_show_float(5*8,3*16,Set_T,3,0);
		}break;
		case TEST_SERVO:break;
		case GO_Pararm1:
		{
			tft180_show_string(0,1*16,"cha:");tft180_show_float(5*8,1*16,dajiao,2,2);
			tft180_show_string(0,2*16,"err:");  tft180_show_float(5*8,2*16,unification(),2,2);
			tft180_show_string(0,4*16,"KP1:");  tft180_show_float(5*8,4*16,KP1,2,2);
			tft180_show_string(0,5*16,"KD1:");  tft180_show_float(5*8,5*16,KD1,2,2);
			tft180_show_string(0,3*16,"TIME:");  tft180_show_float(5*8,3*16,Set_T,2,0);
		}break;
		case GO_Pararm2:
		{
			tft180_show_string(0,1*16,"cha:");tft180_show_float(5*8,1*16,dajiao,2,2);
			tft180_show_string(0,2*16,"err:");  tft180_show_float(5*8,2*16,unification(),2,2);
			tft180_show_string(0,4*16,"KP2:");  tft180_show_float(5*8,4*16,KP2,2,2);
			tft180_show_string(0,5*16,"KD2:");  tft180_show_float(5*8,5*16,KD2,2,2);
			tft180_show_string(0,3*16,"TIME:");  tft180_show_float(5*8,3*16,Set_T,2,0);
		}break;
		case GO_Pararm3:
		{
			tft180_show_string(0,2*16,"err:");  tft180_show_float(5*8,2*16,unification(),2,2);
			tft180_show_string(0,4*16,"KP3:");  tft180_show_float(5*8,4*16,KP3,2,2);
			tft180_show_string(0,5*16,"KD3:");  tft180_show_float(5*8,5*16,KD3,2,2);
			tft180_show_string(0,3*16,"TIME:");  tft180_show_float(5*8,3*16,Set_T,2,0);
		}break;
		case ADC_Show:
		{
			tft180_show_string(0,0*16,"ADC1:");tft180_show_int16(5*8,0*16,ADC_1);
			tft180_show_string(0,1*16,"ADC2:");tft180_show_int16(5*8,1*16,ADC_2);
			tft180_show_string(0,2*16,"ADC3:");tft180_show_int16(5*8,2*16,ADC_3);
			tft180_show_string(0,3*16,"ADC4:");tft180_show_int16(5*8,3*16,ADC_4);
			tft180_show_string(0,4*16,"Help");tft180_show_int16(5*8,4*16,Help_turn());
		}break;
		case Seta_Servo:
		{
			tft180_show_string(0,0*16,"Value:");tft180_show_int16(5*8,0*16,S_Value);
		}break;
	}

}
//void SET_Time()
//{
//	if(Set_T>Time && CAR_Mode!=STOP)
//	{
//		CAR_Mode=STOP;
//		Turn_mode_Init();
//	}
//}

void GO_Function(void)
{
	if(Init_Flag==1)
	{
		Turn_mode_Init();
		Init_Flag=0;
	}
}