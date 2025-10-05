#include "zf_common_headfile.h"
int T=0;

int T4=0;
int Init_Time=0;
unsigned char PIT0_Flag=0;
unsigned char PIT1_Flag=0;

void pit_handler0 (void);
void pit_handler1 (void);
void main()
{
	clock_init(SYSTEM_CLOCK_40M);				// ��ر���
	debug_init();								// ��ر���
	/****************************************************/
	init_all();
	tim0_irq_handler = pit_handler0;// ���ö�ʱ��0�жϻص�����
	tim1_irq_handler = pit_handler1;// ���ö�ʱ��1�жϻص�����
	Buzzer_OFF();
    while(1)
	{
		switch(CAR_Mode)
		{
			case STOP:
			{
				if(Init_Flag==1)
				{
					Turn_mode_Init();
					Init_Flag=0;
				}
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
				MotorR_SetSpeed(100*20);
				MotorL_SetSpeed(100*20);
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
				Serve_Test();
				break;
			}
			case ADC_Show:
			{
				if(Init_Flag==1)
				{
					Turn_mode_Init();
					Init_Flag=0;
				}
				break;
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
				break;
			}
		}
   }
}
void pit_handler0(void)
{
	Protect();
	if(Servo_Flag)
	{
		if(Enter_Flag_Left)
		{
			if(Mode_Flag<-2)//��Բ��
			{
				pwm_set_duty(Servo_Pwm,Servo_Mide+turn_Value);
			}
			else if(Mode_Flag>2)//��Բ��
			{
				pwm_set_duty(Servo_Pwm,Servo_Mide-turn_Value);
			}
			else
			{
				pwm_set_duty(Servo_Pwm,Servo_Mide+dajiao);
			}
		}
		else
		{
			pwm_set_duty(Servo_Pwm,Servo_Mide+dajiao);
		}
		
	}
	if(ADC_Show_Flag)
	{
		if(++T>=10)
		{
			T=0;
			Show_pararm();
		}
	}
	if(Key_Flag)
	{
		Key_scaner();
	}

}

void pit_handler1(void)
{
	ADC_SampleAndFilter();
	dajiao=Servo_turn_pid(unification());
	if_Cycle();
//	State_of_road();
//	
}