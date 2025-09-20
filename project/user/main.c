#include "zf_common_headfile.h"
int T;
int T3;
void pit_handler0 (void);
//void pit_handler1 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// 务必保留
	debug_init();								// 务必保留
	/****************************************************/
	tim0_irq_handler = pit_handler0;// 设置定时器0中断回调函数
//	tim1_irq_handler = pit_handler1;// 设置定时器0中断回调函数
	init_all();
	
    while(1)
	{
//		tft180_show_int16(5*8,6*16,Set_T);
//		tft180_show_int16(5*8,7*16,T3);
		switch(CAR_Mode)
		{
			case STOP:if(Key)
			{
				EA=0;
				menu_handle_key(Key);
				Key=0;
				EA=1;
			}break;
			case GO:
			{
				EA=0;
				Servo_turn_pid(unification(),-80,80);
				SET_Time();
				Protect();
				EA=1;
			}break;
			/****测试程序*****/
			case TEST_LM: LM_Test();break;
			case TEST_RM: RM_Test();break;
			case TEST_SERVO: Serve_Test();break;
			case GO_Pararm1: 
			{
				EA=0;
				Servo_turn_pid(unification(),-80,80);
				SET_Time();
				Protect();
				EA=1;
			}break;
			case GO_Pararm2: 
			{
				EA=0;
				Servo_turn_pid(unification(),-80,80);
				SET_Time();
				Protect();
				EA=1;
			}break;
			case GO_Pararm3: 
			{
				EA=0;
				Servo_turn_pid(unification(),-80,80);
				SET_Time();
				Protect();
				EA=1;
			}break;
		}
		
   }
}
void pit_handler0(void)
{
	T++;
	T3++;
	ADC_SampleAndFilter();
	Key_scaner();
	switch(CAR_Mode)
	{
		case GO:
		{
			if(T>20)
			{
				T=0;
				Show_pararm();
			}
			if(T3>200)
			{
				T3=0;
				Set_T++;
			}
		}break;
	}
	
}

//void pit_handler1(void)
//{
//	Servo_turn_pid(unification(),-80,80);
//}
