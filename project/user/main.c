#include "zf_common_headfile.h"
int T=0;

int T4=0;
int Init_Time=0;

void pit_handler0 (void);
void pit_handler1 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// 务必保留
	debug_init();								// 务必保留
	/****************************************************/
	init_all();
	tim0_irq_handler = pit_handler0;// 设置定时器0中断回调函数
	tim1_irq_handler = pit_handler1;// 设置定时器1中断回调函数
	
	
    while(1)
	{
		switch(CAR_Mode)
		{
			case STOP:
			{
EA=0;
				if(Init_Flag==1)
				{
					Turn_mode_Init();
					Init_Flag=0;
				}
				if(Key)
				{
					menu_handle_key(Key);
					Key=0;
				}
EA=1;
				break;
			}
			case GO:
			{
				GO_Function();
				break;
			}
			case GO_Pararm1: 
			{
				GO_Function();
				break;
			}
			case GO_Pararm2: 
			{
				GO_Function();
				break;
			}
			case GO_Pararm3: 
			{
				GO_Function();
				break;
			}
			case TEST_PWM: 
			{
				if(Init_Flag==1)
				{
					EA=0;
					Turn_mode_Init();
					Init_Flag=0;
					EA=1;
				}
				PWM_Test();
				break;
			}
			case TEST_SERVO: 
			{
				if(Init_Flag==1)
				{
					EA=0;
					Turn_mode_Init();
					Init_Flag=0;
					EA=1;
				}
				Serve_Test();break;
			}
			case ADC_Show:
			{
				if(Init_Flag==1)
				{
					Turn_mode_Init();
					Init_Flag=0;
				}
				else
				{
				}
			}
			case Seta_Servo:
			{
				if(Init_Flag==1)
				{
					Turn_mode_Init();
					Init_Flag=0;
				}
				else
				{
					Set_Sevo();
				}
			}
		}

   }
}
void pit_handler0(void)
{
	T3++;
	if(T3>50)
	{
		T3=0;
		Set_T++;
	}
	if(CAR_Mode==GO||CAR_Mode==GO_Pararm1||CAR_Mode==GO_Pararm2||CAR_Mode==GO_Pararm3)
	{
		pwm_set_duty(Servo_Pwm,Servo_Mide-dajiao);
	}

}

void pit_handler1(void)
{
	T++;
	
	ADC_SampleAndFilter();
	uni=100*unification();
	dajiao=Servo_turn_pid(uni);
	Key_scaner();
	if(T>=50)
	{
		T=0;
		Show_pararm();
	}
}
