#include "zf_common_headfile.h"
int T=0;
int delta_Speed=0;

int T4=0;
unsigned char speed_update_flag=0;
void pit_handler1 (void);
//void pit_handler2 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// ��ر���
	debug_init();								// ��ر���
	/****************************************************/
	init_all();
	tim1_irq_handler = pit_handler1;// ���ö�ʱ��0�жϻص�����
//	tim2_irq_handler = pit_handler2;// ���ö�ʱ��1�жϻص�����
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
				if(Key)
				{
//					EA=0;
//					menu_handle_key(Key);
//					Key=0;
//					EA=1;
				}
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
	ADC_SampleAndFilter();//ADC����
	dajiao=Servo_turn_pid(unification());//ת��ֵ����
	if_Cycle();//�������
	if(Servo_Flag)//�������
	{
		Servo_Control();
	}
	speed_control_ring();//��ȡ������
	
	if(GO_PID_Control+GO_PID_Control1+GO_PID_Control2+GO_PID_Control3==1)//�ٶȲ���
	{
		Speed_diff((float)(dajiao)/100,0.8);
		if(Speed_Mode>5)
		{
			State_of_road();
		}
		else
		{
			Speed_Control();
		}
	}
//	printf("%d,%d\n",encoder_data_dir_1,(int)((ML+delta_Speed)*100));
	if(T>=4)
	{
		T=0;
		Protect();
		if(Key_Flag)//�������
		{
			Key_scaner();
		}
		if(ADC_Show_Flag)//ADC��ʾ
		{
			Show_pararm();
		}
	}
}

//void pit_handler2(void)
//{
//	
//}