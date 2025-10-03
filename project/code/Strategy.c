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
unsigned char Cycle_Stat=0;
//?°Ë®®??°§¶Ão
//®®??°§¶Ão
//3??°§¶Ão
//ª∑µ∫≈–∂œ
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
				if(Cycle_Over)
				{
					over_time++;
					if(over_time>NOT_Time)
					{
						Cycle_Over=0;
						over_time=0;
					}
				}
			}
			break;
		}
		case APPROACH:
		{
			if(ADC_2!=1023 || ADC_3!=1023)
			{
				Cycle_Stat=Left_ENTER;
			}
			else
			{
				no_time++;
				if(no_time>20)
				{
					Cycle_Stat=EXIT;
					no_time=0;
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
				Cycle_Over=1;
			}
			break;
		}
	}

}
//«–Õ‰≤π∂°
int Help_turn()
{
	if(Cycle_Over!=1)
	{
		if(ADC_1+ADC_2<220)
		{
			return -50;
		}
		else if(ADC_3+ADC_4<220)
		{
			return 50;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}