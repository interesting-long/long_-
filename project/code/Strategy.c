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

unsigned int Not_Time=0;
//环岛判断
void if_Cycle(void)
{
	switch(Cycle_Stat)
	{
		case EXIT:
		{
			
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
			else
			{
				if2_time=0;
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
				Buzzer_OFF();
			}
			break;
		}
		default :
		{
			CAR_STOP();
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
			if(dajiao<Stright_Flag_Value && dajiao>-Stright_Flag_Value)
			{
				Short_Time++;
				if(Short_Time>Short_Judge_Time)
				{
					Buzzer_OFF();
					Short_Time=0;
					Road_Stat=Short_Str;
					Motor_Update(Short_add);
					tft180_show_string(0,0*16,"Short");
				}
			}
			else
            {
                Short_Time=0; // 重要：条件不满足时重置计时
            }
			break;
		}
		case Short_Str:
		{
			if(dajiao<Stright_Flag_Value && dajiao>-Stright_Flag_Value)
			{
				Long_Time++;
				Not_Time=0;
				if(Long_Time>Long_Judge_Time)
				{
					Buzzer_OFF();
					Long_Time=0;
					Road_Stat=Long_Str;
					Motor_Update(Long_add);
					tft180_show_string(0,0*16,"Long");
				}
			}
			else
			{
				Long_Time=0;
				Not_Time++;
				{
					if(Not_Time>30)
					{
						Not_Time=0;
						Road_Stat=Normal_Str;
						tft180_show_string(0,0*16,"Normal");
					}
				}
			}
			break;
		}
		case Long_Str:
		{
			if(dajiao>Bend_Flag_Value || dajiao<-Bend_Flag_Value)
			{
				Bend_Time++;
				if(Bend_Time>5)
				{
					Buzzer_ON();
					Bend_Time=0;
					Road_Stat=Bend;
					Motor_Update(0);
					tft180_show_string(0,0*16,"Bend");
				}
			
			}
			else
			{
				Bend_Time=0;
			}
			break;
		}
		case Bend:
		{
			slow_Time++;
			if(slow_Time<Bend_Slow_Time)
			{
				Motor_Update(Bend_slow);
			}
			else
			{
				if(dajiao>Bend_Flag_Value)
				{
					Motor_Update(0);
				}
				else if( dajiao<-Bend_Flag_Value)
				{
					Motor_Update(0);
				}
				else
				{
					Buzzer_OFF();
					slow_Time=0;
					Road_Stat=Normal_Str;
					Motor_Update(0);
					tft180_show_string(0,0*16,"Normal");
				}
			}
			break;
		}
		default :
		{
			Buzzer_OFF();
			CAR_STOP();
			break;
		}
	
	}	

}