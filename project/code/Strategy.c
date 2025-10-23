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
unsigned int Accel_Time=0;

int Wait_Time = 0;

unsigned int Entern_Flag_Time=0;
unsigned int Entern_Delay_Time=0;
unsigned int Entern_Continue_Time=0;
int turn_Value=0;
int Mode_Flag=0;


//环岛判断
void if_Cycle(void)
{
	if(Wait_Time>0)
	{
		Wait_Time--;
		return;
	}
	else
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
					Wait_Time = 200;
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
void Help_turn2(int temp, int value, int ADC_Flag)
{
    static int last_dir = 0;    // -1 左，+1 右，0 未定
    static int first_double = 1; // 是否是第一次进入“双小”状态

    int left  = ADC_1 + ADC_2;
    int right = ADC_3 + ADC_4;
	int target=0;
	
	static float smooth_temp = 0;
    const int delta = 30;  // 左右接近的最小差值门限
	const float smooth=0.3;
	if(left < ADC_Flag || right < ADC_Flag)
	{
		if (left < ADC_Flag && right < ADC_Flag)
		{
			if (first_double) // ★第一次双小
			{
				if (left < right)
				{
					target = -value;   // 左
					last_dir = -1;
				}
				else
				{
					target = value;    // 右
					last_dir = 1;
				}
				first_double = 0; // 标记已经处理过第一次
			}
			else // ★后续双小
			{
				if (abs(left - right) < delta)
				{
					// 按照上次方向走
					if (last_dir == -1) target = -value;
					else if (last_dir == 1) target = value;
					else target = value; // 默认
				}
				else if (left < right)
				{
					target = -value;
					last_dir = -1;
				}
				else
				{
					target = value;
					last_dir = 1;
				}
			}
		}
		else if (left < ADC_Flag)
		{
			target = -value;
			last_dir = -1;
			first_double = 1; // 重置，下次再遇到“双小”时重新走第一次逻辑
		}
		else
		{
			target = value;
			last_dir = 1;
			first_double = 1; // 同上
		}
		smooth_temp = smooth_temp * (1 - smooth) + target * smooth;
		pwm_set_duty(Servo_Pwm,Servo_Mide+smooth_temp);
	}
	else 
	{
		if(abs(smooth_temp-temp)<200)
		{
			smooth_temp = temp;
			pwm_set_duty(Servo_Pwm,Servo_Mide+temp);
		}
		else
		{
			smooth_temp = smooth_temp * (1 - smooth) + temp * smooth;
			pwm_set_duty(Servo_Pwm,Servo_Mide+smooth_temp);
		}
	}
}

void Help_turn3(int* temp, int value, int value2,int ADC_Flag ,int ADC_Flag2)
{
	//value2>value1,ADC_Flag1>ADC_Flag2
    static int last_dir = 0;    // -1 左，+1 右，0 未定
    static int first_double = 1; // 是否是第一次进入“双小”状态
    int left  = ADC_1 + ADC_2;
    int right = ADC_3 + ADC_4;
	float K = (float)(value2 - value) / (ADC_Flag - ADC_Flag2);
    const int delta = 30;  // 左右接近的最小差值门限

    if (left < ADC_Flag && right < ADC_Flag)
    {
		if (left < ADC_Flag2 && right < ADC_Flag2)
		{
			if (first_double) // ★第一次双小
			{
				if (left < right)
				{
					*temp = -value2;   // 左
					last_dir = -1;
				}
				else
				{
					*temp = value2;    // 右
					last_dir = 1;
				}
				first_double = 0; // 标记已经处理过第一次
			}
			else // ★后续双小
			{
				if (abs(left - right) < delta)
				{
					// 按照上次方向走
					if (last_dir == -1) *temp = -value2;
					else if (last_dir == 1) *temp = value2;
					else *temp = value2; // 默认
					    // 向左转
      // 向右转
				}
				else if (left < right)
				{
					*temp = -value2;
					last_dir = -1;
				}
				else
				{
					*temp = value2;
					last_dir = 1;
				}
			}
		}
		else if(left < ADC_Flag2)
		{
			*temp = -value2;
			last_dir = -1;
			first_double = 1; 
		}
		else if(right < ADC_Flag2)
		{
			*temp = value2;
			last_dir = 1;
			first_double = 1; // 同上
		}
		else
		{
			if (abs(left - right) < delta)
			{
				// 按照上次方向走
				if (last_dir == -1) *temp = -value;
				else if (last_dir == 1) *temp = value;
				else *temp = value; 
			}
//			else if (left < right)
//			{
//				*temp = -(value + (ADC_Flag - left) * K);
//				last_dir = -1;
//				first_double = 1; 
//			}
//			else
//			{
//				*temp = value + (ADC_Flag - right) * K;
//				last_dir = 1;
//				first_double = 1; 
//			}
		}
    }
    else if (left < ADC_Flag)
    {
        *temp = -(value + (ADC_Flag - left) * K);
		last_dir = -1;
		first_double = 1; 
    }
    else if (right < ADC_Flag)
    {
		*temp = value + (ADC_Flag - right) * K;
		last_dir = 1;
		first_double = 1; 
    }
}

int Help_turn_Two(int temp, int value, int value2, int ADC_Flag, int ADC_Flag2)
{
    int left  = ADC_1 + ADC_2;
    int right = ADC_3 + ADC_4;

    // -------- 第一组阈值判断 --------
    if (left < ADC_Flag && right < ADC_Flag)
    {
        return (left < right) ? (Servo_Mide - value) : (Servo_Mide + value);
    }
    else if (left < ADC_Flag)
    {
        return Servo_Mide - value;
    }
    else if (right < ADC_Flag)
    {
        return Servo_Mide + value;
    }

    // -------- 第二组阈值判断 --------
    if (left < ADC_Flag2 && right < ADC_Flag2)
    {
        return (left < right) ? (Servo_Mide - value2) : (Servo_Mide + value2);
    }
    else if (left < ADC_Flag2)
    {
        return Servo_Mide - value2;
    }
    else if (right < ADC_Flag2)
    {
        return Servo_Mide + value2;
    }

    // -------- 都不满足，返回原值 --------
    return temp;
}

int State_of_road(void)
{
	switch(Road_Stat)
	{
		case Short_Str:
		{
			Motor_Update_Smooth(Short_add);
			if(abs(dajiao)<Stright_Flag_Value)
			{
				Long_Time++;
				Bend_Time=0;
				if(Long_Time>Long_Judge_Time)
				{
					Long_Time=0;
					Road_Stat=Long_Str;
				}
			}
			else
			{
				Long_Time=0;
				Bend_Time++;
				{
					if(Bend_Time>Bend_Judge_Time)
					{
						Bend_Time=0;
						Road_Stat=Short_Bend;
					}
				}
			}
			return Short_add;
			break;
		}
		case Long_Str:
		{
			Motor_Update_Smooth(Long_add);
			Accel_Time++;
			if(abs(dajiao)>Bend_Flag_Value)
			{
				Bend_Time++;
				if(Bend_Time>Bend_Judge_Time)
				{
					if(Accel_Time>150)//加速时间1.5s
					{
						Road_Stat=Long_Bend;
						SLOW_Time = 0;
					}
					else
					{
						Road_Stat=Short_Bend;
					}
					Bend_Time=0;
					Accel_Time=0;
				}
			}
			else
			{
				Bend_Time=0;
			}
			return Long_add;
			break;
		}
		case Short_Bend:
		{
			Motor_Update_Smooth(Bend_speed);
			if(abs(dajiao)>Bend_Flag_Value)
			{
				Short_Time=0;
			}
			else
			{
				Short_Time++;
				if(Short_Time>Short_Judge_Time)
				{
					Short_Time=0;
					Road_Stat=Short_Str;
				}
			}
			return Bend_speed;
			break;
		}
		case Long_Bend:
		{
			SLOW_Time++;
			if(SLOW_Time>L_Turn_B_Slow_Time)
			{
				Buzzer_OFF();
				Motor_Update_Smooth(Bend_speed);//弯道速度
			}
			else
			{
				Buzzer_ON();
				
				Motor_Update_Smooth(L_Turn_B_Slow_Value);//减速
			}
			//检查是否回到了直道
			if(abs(dajiao)<Bend_Flag_Value)
			{
				Short_Time++;
				if(Short_Time>Short_Judge_Time)
				{
					Buzzer_OFF();
					Short_Time=0;
					SLOW_Time=0;
					Road_Stat=Short_Str;
				}
				
			}
			else
			{
				Short_Time=0;
			}
			if(SLOW_Time>L_Turn_B_Slow_Time)
			{
				return Bend_speed;
			}
			else
			{
				return L_Turn_B_Slow_Value;
			}
			
			break;
		}
		default :
		{
			CAR_STOP();
			return 0;
			break;
		}
	
	}
}


