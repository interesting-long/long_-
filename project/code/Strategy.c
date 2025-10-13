#include "Strategy.h"
unsigned int if_time=0;
unsigned int if2_time=0;
unsigned int Continue_Time=0;
unsigned char Enter_Flag_Left=0;
unsigned char Cycle_Stat=EXIT;

unsigned char Road_Stat=Short_Str;
unsigned int Short_Time=0;
unsigned int Long_Time=0;
unsigned int Bend_Time=0;
unsigned int SLOW_Time=0;

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
				if2_time++;
				if(if2_time>Entern_Delay_Time)
				{
					Cycle_Stat=Left_ENTER;
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
			return -50;   // 左
		else
			return 50;    // 右
	}
	else if (left < 200)
	{
		return -50;   // 左
	}
	else if (right < 200)
	{
		return 50;    // 右
	}
	else
	{
		return 0;     // 不转
	}
}
int Help_turn2(int temp,int value,int ADC_Flag)
{
	int left  = ADC_1 + ADC_2;
	int right = ADC_3 + ADC_4;
	if (left < ADC_Flag && right < ADC_Flag)
	{
		// 同时满足，取较小一侧优先
		if (left < right)
			return Servo_Mide-value;   // 左
		else
			return Servo_Mide+value;    // 右
	}
	else if (left < ADC_Flag)
	{
		return Servo_Mide-value;   // 左
	}
	else if (right < ADC_Flag)
	{
		return Servo_Mide+value;    // 右
	}
	else
	{
		return temp;     
	}
}
void State_of_road(void)
{
	switch(Road_Stat)
	{
//		case Normal_Str:
//		{
//			Motor_Update(0);
//			if(dajiao<Stright_Flag_Value && dajiao>-Stright_Flag_Value)
//			{
//				Short_Time++;
//				Bend_Time=0;
//				if(Short_Time>Short_Judge_Time)
//				{
////					Buzzer_OFF();
//					Short_Time=0;
//					Road_Stat=Short_Str;
//				}
//			}
//			else
//            {
//				Bend_Time++;
//				Short_Time=0; // 重要：条件不满足时重置计时
//				if(Bend_Time>10)
//				{
////					Buzzer_ON();
//					Bend_Time=0;
//					Road_Stat=Bend;
//				}
//                
//            }
//			break;
//		}
		case Short_Str:
		{
			Motor_Update(Short_add);
			if(dajiao<Stright_Flag_Value && dajiao>-Stright_Flag_Value)
			{
				Long_Time++;
				Not_Time=0;
				if(Long_Time>Long_Judge_Time)
				{
					Long_Time=0;
					Road_Stat=Long_Str;
				}
			}
			else
			{
				Long_Time=0;
				Not_Time++;
				{
					if(Not_Time>No_Tim)
					{
						Not_Time=0;
						Road_Stat=Short_Bend;
					}
				}
			}
			break;
		}
		case Long_Str:
		{
			Motor_Update(Long_add);
			if(dajiao>Bend_Flag_Value || dajiao<-Bend_Flag_Value)
			{
				Bend_Time++;
				if(Bend_Time>5)
				{
					Bend_Time=0;
					Road_Stat=Long_Bend;
				}
			
			}
			else
			{
				Bend_Time=0;
			}
			break;
		}
		case Short_Bend:
		{
			Motor_Update(Bend_slow);
			if(dajiao>Bend_Flag_Value)
			{
				Not_Time=0;
			}
			else if( dajiao<-Bend_Flag_Value)
			{
				Not_Time=0;
			}
			else
			{
				Not_Time++;
				if(Not_Time>No_Tim)
				{
					Not_Time=0;
					Road_Stat=Short_Str;
				}
			}
			break;
		}
		case Long_Bend:
		{
			SLOW_Time++;
			if(SLOW_Time>2)
			{
				//减速时间
			}
			else
			{
				if(dajiao>Bend_Flag_Value || dajiao<-Bend_Flag_Value)
				{
					//弯道时间
					Not_Time=0;
				}
				else
				{
					Not_Time++;
					if(Not_Time>No_Tim)
					{
						Not_Time=0;
						Road_Stat=Short_Str;
					}
				}
			}
			
			break;
		}
		default :
		{
//			Buzzer_OFF();
			CAR_STOP();
			break;
		}
	
	}

}