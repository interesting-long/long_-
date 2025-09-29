#include "Key.h"

int Press_time=0;
int Trigg_time=0;
unsigned char keynumber=0;
unsigned char last_keynumber=0;
unsigned char State=0;
unsigned char Key_count=0;
unsigned Time_dou=0;
unsigned char Init_Flag=0;


unsigned char Key_Number(void)
{
    unsigned char KeyNumber=0;

//    if(gpio_get_level(IO_P26)==0){KeyNumber=1;}//下
//    if(gpio_get_level(IO_P07)==0){KeyNumber=2;}//右
//    if(gpio_get_level(IO_P45)==0){KeyNumber=3;}//左
//    if(gpio_get_level(IO_P46)==0){KeyNumber=4;}//上
	
	if(gpio_get_level(IO_P45)==0){KeyNumber=1;}//下
    if(gpio_get_level(IO_P26)==0){KeyNumber=2;}//右
    if(gpio_get_level(IO_P46)==0){KeyNumber=3;}//左
    if(gpio_get_level(IO_P07)==0){KeyNumber=4;}//上
	if(gpio_get_level(IO_P52)==0){KeyNumber=5;}//中
    return KeyNumber;
}
void Turn_mode(void)
{
	if((void *)Pin==(void *)&Page[0])
	{
		switch(Flag)
		{
			case 2:CAR_Mode=(CAR_Mode==GO) ? STOP : GO;break;
			case 3:CAR_Mode=(CAR_Mode==GO_Pararm1) ? STOP : GO_Pararm1;break;
			case 4:CAR_Mode=(CAR_Mode==GO_Pararm2) ? STOP : GO_Pararm2;break;
			case 5:CAR_Mode=(CAR_Mode==GO_Pararm3) ? STOP : GO_Pararm3;break;
			case 8:CAR_Mode=(CAR_Mode==ADC_Show) ? STOP : ADC_Show;break;
			default :break;
		}
	}
	else if((void *)Pin==(void *)&Page[5])
	{
		switch(Flag)
		{
			case 3:CAR_Mode=(CAR_Mode==TEST_SERVO) ? STOP : TEST_SERVO;break;
			case 4:CAR_Mode=(CAR_Mode==Seta_Servo) ? STOP : Seta_Servo;break;
			default :break;
		}
		
	}
	else if((void *)Pin==(void *)&Page[6])
	{
		CAR_Mode=(CAR_Mode==TEST_PWM) ? STOP : TEST_PWM;
	}
	else if((void *)Pin==(void *)&Page[1])
	{
		CAR_Mode=(CAR_Mode==GO) ? STOP : GO;
	}
	else if((void *)Pin==(void *)&Page[2])
	{
		CAR_Mode=(CAR_Mode==GO_Pararm1) ? STOP : GO_Pararm1;
	}
	else if((void *)Pin==(void *)&Page[3])
	{
		CAR_Mode=(CAR_Mode==GO_Pararm2) ? STOP : GO_Pararm2;
	}
	else if((void *)Pin==(void *)&Page[4])
	{
		CAR_Mode=(CAR_Mode==GO_Pararm3) ? STOP : GO_Pararm3;
	}
//		Turn_mode_Init();
}
void Key_scaner(void)
{
	keynumber=Key_Number();
	switch(State)
	{
		case State_Release:
		{
			if(keynumber!=0)
			{
				State=State_Press_dou;
				Key_count=0;
			}
			break;
		}
		case State_Press_dou:
		{
			if(keynumber==0)
			{
				State=State_Release;
			}
			else
			{
				Key_count++;
				if(Key_count>=Time_dou)
				{
					State=State_Press;
					last_keynumber=keynumber;
//					Key=keynumber;
				}
			}
			break;
		}
		case State_Press:
		{
			if(keynumber==0)
			{
//				Key=last_keynumber;
				State=State_Release_dou;
				Key_count=0;
				Press_time=0;
			}
			else
			{
				Press_time++;
				if(Press_time>Flag_press_time)
				{
					Trigg_time++;
					if(keynumber==5)//长按触发的操作
					{
						Turn_mode();
						Init_Flag=1;
						Press_time=0;
						last_keynumber=0;
					}
					else if(Trigg_time>Flag_trigg_time)
					{
						Trigg_time=0;
						Key=keynumber;
						//多次触发的操作
					}
				}
			}
			break;
		}
		case State_Release_dou:
		{
			if(keynumber==0)
			{
				Key_count++;
				if(Key_count>=Time_dou)
				{
					State=State_Release;
					Key=last_keynumber;  // 松开时清零
				}
			}
			else
			{
				State=State_Press;
			}
			break;
		}
	}
}
