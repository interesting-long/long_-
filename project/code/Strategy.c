#include "Strategy.h"
float uni=0;
float last_uni=0;
int if_time=0;
int if2_time=0;
int no_time=0;
int over_time=0;
int Continue_Time=0;
unsigned char Enter_Flag_Left=0;
unsigned char Enter_Flag_Right=0;
unsigned char Cycle_Over=0;
unsigned char Cycle_Stat=EXIT;
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
					Cycle_Over=0;
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