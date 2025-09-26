#include "zf_common_headfile.h"
int T;
int T3;
int T4;
unsigned char pit_Flag;
void pit_handler0 (void);
void pit_handler1 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// 务必保留
	debug_init();								// 务必保留
	/****************************************************/
	tim0_irq_handler = pit_handler0;// 设置定时器0中断回调函数
	tim1_irq_handler = pit_handler1;// 设置定时器0中断回调函数
	init_all();
	
    while(1)
	{
		if(pit_Flag==1)
		{
			if(CAR_Mode==GO || CAR_Mode==GO_Pararm1 || CAR_Mode==GO_Pararm2 || CAR_Mode==GO_Pararm3 || CAR_Mode==ADC_Show)
			{
				ADC_SampleAndFilter();
				Servo_turn_pid(unification());
			}
			pit_Flag=0;
		}
		switch(CAR_Mode)
		{
			case STOP:
			{
				EA=0;
				if(Key)
				{
					menu_handle_key(Key);
					Key=0;
				}
				EA=1;
			}break;
			case GO:
			{
				SET_Time();
				Protect();
//				LineLossProtection();
			}break;
			case TEST_PWM: PWM_Test();break;
			case TEST_SERVO: Serve_Test();break;
			case GO_Pararm1: 
			{
				SET_Time();
				Protect();
//				LineLossProtection();
			}break;
			case GO_Pararm2: 
			{
				SET_Time();
				Protect();
//				LineLossProtection();
			}break;
			case GO_Pararm3: 
			{
				SET_Time();
				Protect();
//				LineLossProtection();
			}break;
		}
		
   }
}
void pit_handler0(void)
{
	pit_Flag=1;
}

void pit_handler1(void)
{
	T++;
	T3++;
	if(CAR_Mode==STOP || CAR_Mode==ADC_Show)
	{
		Key_scaner();
	}
	if(T>50)
	{
		T=0;
		Show_pararm();
	}
	if(T3>100)
	{
		T3=0;
		Set_T++;
	}
}
