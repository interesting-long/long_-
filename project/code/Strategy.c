#include "Strategy.h"
float uni=0;
float last_uni=0;
unsigned int if_time=0;
unsigned int if2_time=0;
unsigned int Continue_Time=0;
unsigned char Enter_Flag_Left=0;
unsigned char Cycle_Stat=EXIT;

unsigned char Road_Stat=Normal_Str;
unsigned int Short_Time=0;
unsigned int Long_Time=0;
unsigned int Bend_Time=0;
unsigned int slow_Time=0;

unsigned int Entern_Flag_Time=0;
unsigned int Entern_Delay_Time=0;
unsigned int Entern_Continue_Time=0;
int turn_Value=0;
int Mode_Flag=0;
//环岛判断
void if_Cycle(void)
{
	switch(Cycle_Stat)
	{
		case EXIT:
		{
			Buzzer_OFF();
			if(ADC_2==1023 || ADC_3==1023 )
			{
				if_time++;
				if(if_time>Entern_Flag_Time)
				{
					Cycle_Stat=APPROACH;
					if_time=0;
				}
			}
			else
			{
				if_time=0;
			}
			break;
		}
		case APPROACH:
		{
			if(ADC_2!=1023 || ADC_3!=1023)
			{
				if2_time++;
				if(if2_time>Entern_Delay_Time)
				{
					Cycle_Stat=Left_ENTER;
					if2_time=0;
				}
			}
			break;
		}
		case Left_ENTER:
		{
			Enter_Flag_Left=1;
			Buzzer_ON();
			Continue_Time++;
			if(Continue_Time>Entern_Continue_Time)
			{
				Cycle_Stat=EXIT;
				Continue_Time = 0;  //
                Enter_Flag_Left = 0;     //
			}
			break;
		}
	}

}
//切弯补丁
int Help_turn()
{
	int left  = ADC_1 + ADC_2;
	int right = ADC_3 + ADC_4;
	if (left < 200 && right < 200)
	{
		// 同时满足，取较小一侧优先
		if (left < right)
			return -40;   // 左
		else
			return 40;    // 右
	}
	else if (left < 200)
	{
		return -40;   // 左
	}
	else if (right < 200)
	{
		return 40;    // 右
	}
	else
	{
		return 0;     // 不转
	}
}

void State_of_road(void)
{
	switch(Road_Stat)
	{
		case Normal_Str:
		{
			if(dajiao<20 && dajiao>-20)
			{
				Short_Time++;
				if(Short_Time>20)
				{
					Short_Time=0;
					Road_Stat=Short_Str;
					Motor_Update(2);
					Buzzer_ON();
				}
			}
			break;
		}
		case Short_Str:
		{
			if(dajiao<20 && dajiao>-20)
			{
				Long_Time++;
				if(Long_Time>100)
				{
					Long_Time=0;
					Road_Stat=Long_Str;
					Buzzer_OFF();
					Motor_Update(5);
				}
			}
			break;
		}
		case Long_Str:
		{
			if(dajiao>50 || dajiao<-50)
			{
				Bend_Time++;
				if(Bend_Time>5)
				{
					Bend_Time=0;
					Road_Stat=Bend;
					Motor_Update(0);
					Buzzer_ON();
				}
			
			}
			break;
		}
		case Bend:
		{
			slow_Time++;
			if(slow_Time<20)
			{
				MotorR_SetSpeed(100*0);
				MotorL_SetSpeed(100*0);
			}
			else
			{
				if(dajiao>50)
				{
					Motor_Update(0);
				}
				else if( dajiao<-50)
				{
					Motor_Update(0);
				}
				else
				{
					slow_Time=0;
					Road_Stat=Normal_Str;
					Motor_Update(0);
					Buzzer_OFF();
				}
			}
			break;
		}
	
	}	

}