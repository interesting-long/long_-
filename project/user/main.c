#include "zf_common_headfile.h"
int T=0;
int delta_Speed=0;

int T4=0;
unsigned char speed_update_flag=0;
void pit_handler1 (void);
//void pit_handler2 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// 务必保留
	debug_init();								// 务必保留
	/****************************************************/
	init_all();
	tim1_irq_handler = pit_handler1;// 设置定时器0中断回调函数
//	tim2_irq_handler = pit_handler2;// 设置定时器1中断回调函数
    while(1)
	{
		
		switch(CAR_Mode)
		{
			case STOP:
			{
				GO_Function();
				if(Key)
				{
					EA=0;
					menu_handle_key(Key);
					Key=0;
					EA=1;
				}
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
				GO_Function();
				PWM_Test();
				break;
			}
			case TEST_SERVO: 
			{
				GO_Function();
				Serve_Test();
				break;
			}
			case ADC_Show:
			{
				GO_Function();
				break;
			}
			case Seta_Servo:
			{
				GO_Function();
				Set_Sevo();
				break;
			}
		}
		if(Protect_flag)
		{
			Protect_flag=0;
			CAR_Mode=STOP;
			Turn_mode_Init();
		}

		
   }
}


void pit_handler1(void)
{
	T++;
	ADC_SampleAndFilter();//ADC采样
	Last_dajiao=dajiao;
	dajiao=Servo_turn_pid(unification());//转向值计算
	speed_control_ring();//读取编码器
//	if_Cycle();//环岛检测
	if(Servo_Flag)//舵机控制
	{
		Servo_Control();
		if(Intial>5)
		{
			Inertial_Navigation(IN_Val);//
		}
	}
	if(GO_PID_Control+GO_PID_Control1+GO_PID_Control2+GO_PID_Control3==1)//速度策略
	{
		Speed_diff((float)(dajiao)/100,0.15);
		imu963ra_get_gyro();
		angle+=imu963ra_gyro_y/100;
		if(Intial<5 &&Intial>-5)
		{
		printf("%d\n",angle);
		}
//		if(Speed_Mode>5)
//		{
////			State_of_road();
//			
//		}
		if(Intial<-5)
		{
			Half_State_of_road(IN_Val);
		}
		else
		{
			Speed_Control();
		}
	}
	if(T>=4)
	{
		T=0;
		Protect();
		if(Key_Flag)//按键检测
		{
			Key_scaner();
		}
		if(ADC_Show_Flag)//ADC显示
		{
			Show_pararm();
		}
	}
}
