#include "Key.h"

int Press_time;
int Trigg_time;
unsigned char keynumber;
unsigned char State;
unsigned char Key_count;
unsigned Time_dou;

unsigned char CAR_Mode=STOP;

unsigned char Key_Number(void)
{
    unsigned char KeyNumber=0;

    if(gpio_get_level(IO_P46)==0){KeyNumber=1;}//左
    if(gpio_get_level(IO_P45)==0){KeyNumber=2;}//右
    if(gpio_get_level(IO_P37)==0){KeyNumber=3;}//中
    if(gpio_get_level(IO_P36)==0){KeyNumber=4;}//上
    return KeyNumber;
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
					Key=keynumber;
				}
			}
			break;
		}
		case State_Press:
		{
			if(keynumber==0)
			{
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
					if(keynumber==3)//长按触发的操作
					{
						if(CAR_Mode==STOP)
						{
							CAR_Mode=GO;
						}
						else
						{
							CAR_Mode=STOP;
						}
						Press_time=0;
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
					Key=0;  // 松开时清零
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
