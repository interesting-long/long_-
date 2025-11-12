#include "Strategy.h"

unsigned char Protect_Flag_Cycle=1;

/**********环岛的参数******************/
unsigned char Cycle_Stat=EXIT;

unsigned int Wait_Time = 0;
unsigned int if_time=0;
unsigned int if2_time=0;
unsigned int Continue_Time=0;

unsigned int Entern_Flag_Time=0;
unsigned int Entern_Delay_Time=0;
unsigned int Entern_Continue_Time=0;
int turn_Value=0;
int Mode_Flag=0;

unsigned char Enter_Flag_Left=0;
/**********速测的参数******************/
        /**无惯性导航**/
unsigned char Road_Stat=Stright;
unsigned int Short_Time=0;
unsigned int Long_Time=0;
unsigned int Bend_Time=0;
//unsigned int SLOW_Time=0;
unsigned int Accel_Time=0;

unsigned char Normal_Slow_Flag=0;
/***************有惯性导航**********/
			/*******记录函数的数据******/
#define Delta_Angle_Flag	0.3
#define Turn_Mode_Time		7
#define Short_Stright_Flag  4000
#define Long_Stright_Flag  8000
#define dajiao_Value 200
long int all_road=0;
float delta_angle=0;
float angle=0;
unsigned char Max_Item=0;
unsigned char Guan_Dao_Show_Item=0;

int Straightaways_Time=0;
int Turnways_Time=0;
long int Short_road_Data[30]={0};
long int Long_road_Data[30]={0};
long int Long_short_Data[30]={0};
long int Turn_road_Data[30]={0};
long int All_road_Data[100]={0};
float All_angle_Data[100]={0};
unsigned char All_road_Flag[100]={0};

int Now_Item=0;
int Str_Data_Buffer=0;
float angle_buffer=0;
road_Data Now_State_Road=Stright;
unsigned char Last_State_Road=Stright;
			/*******速测函数的数据*******/
#define Data_Error  600
#define ACC_Buffer  300
//#define forword_Error  300
#define Angle_Error  15
#define Short_ACC_Value  3
#define Long_ACC_Value  4
#define Slow_Value -3
unsigned char Guan_Slow_Flag;
int Guan_Slow_Time;
unsigned char Acclerate_Flag=0;

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
						Protect_Flag_Cycle=0;
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
//				angle+=imu963ra_gyro_y/100;
				if(Continue_Time>Entern_Continue_Time)//abs(angle)>Turn_Angle*10
				{
					Cycle_Stat=EXIT;
					Buzzer_OFF();
					Protect_Flag_Cycle=1;
					Wait_Time = 200;
					Continue_Time = 0;  //
					Enter_Flag_Left = 0;     //
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
	
	static float vel = 0;
	float kp=0.3;
	float kd=0.5;
	float error=0;
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
//			first_double = 1; // 重置，下次再遇到“双小”时重新走第一次逻辑
		}
		else
		{
			target = value;
			last_dir = 1;
//			first_double = 1; // 同上
		}
		error = target-smooth_temp;
		vel = vel + kp * error - kd * vel;
		smooth_temp = smooth_temp + vel;
		pwm_set_duty(Servo_Pwm,Servo_Mide+smooth_temp);
	}
	else 
	{
		first_double = 1;
		error = temp-smooth_temp;
		vel = vel + kp * error - kd * vel;
		smooth_temp = smooth_temp + vel;
		if(abs(smooth_temp-temp)<300)
		{
			pwm_set_duty(Servo_Pwm,Servo_Mide+(temp+smooth_temp)/2);
		}
		else
		{
//			smooth_temp = smooth_temp * (1 - smooth) + temp * smooth;
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
/*

*/
void State_of_road(void)
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
						Normal_Slow_Flag=1;
						Bend_Time=0;
						Road_Stat=Short_Bend;
					}
				}
			}
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
						Normal_Slow_Flag=1;
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
			break;
		}
		case Short_Bend:
		{
			if(Normal_Slow_Flag)
			{
				Buzzer_ON();
				Motor_Update_Smooth(L_Turn_B_Slow_Value);//减速
				if((encoder_data_dir_1+encoder_data_dir_2)/2<(Left_Speed+Right_Speed)/2*100)
				{
					Normal_Slow_Flag=0;
				}
			}
			else
			{
				Buzzer_OFF();
				Motor_Update_Smooth(Bend_speed);//弯道速度
				
			}	
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
			break;
		}
		case Long_Bend:
		{
			if(Normal_Slow_Flag)
			{
				Buzzer_ON();
				Motor_Update(L_Turn_B_Slow_Value);//减速
				if((encoder_data_dir_1+encoder_data_dir_2)/2<(Left_Speed+Right_Speed)/2*100-100)
				{
					Normal_Slow_Flag=0;
				}
			}
			else
			{
				Buzzer_OFF();
				Motor_Update_Smooth(Bend_speed);//弯道速度
				
			}			
			//检查是否回到了直道
			if(abs(dajiao)<Bend_Flag_Value)
			{
				Short_Time++;
				if(Short_Time>Short_Judge_Time)
				{
					Buzzer_OFF();
					Short_Time=0;
					Road_Stat=Short_Str;
				}
			}
			else
			{
				Short_Time=0;
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

void Inertial_Navigation(int value)//记录赛道
{
	all_road+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;//得到直道的路程
	
	switch(Now_State_Road)
	{
		case Turn_Ways:
		{
			if(abs(dajiao)<value && abs(delta_angle)<Delta_Angle_Flag)
			{
				Straightaways_Time++;
				if(Straightaways_Time>Turn_Mode_Time)
				{
					Now_State_Road=Stright;
					Straightaways_Time=0;
				}
			}
			else
			{
				Straightaways_Time=0;
			}
			break;
		}
		case Stright:
		{
			Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
			if(abs(dajiao)>value || abs(delta_angle)>Delta_Angle_Flag)
			{
				Turnways_Time++;
				if(Turnways_Time>Turn_Mode_Time)
				{
					Now_State_Road=Turn_Ways;
					Turnways_Time=0;
					/****/
				}
			}
			else
			{
				angle_Get();
				Turnways_Time=0;
			}
			break;
		}

	}
	/**************状态切换*********************/
	if(Last_State_Road!=Now_State_Road)
	{
		if(Last_State_Road == Stright)
		{
			if(Str_Data_Buffer>Long_Stright_Flag)
			{
				Long_road_Data[Now_Item]=Str_Data_Buffer;
				Long_short_Data[Now_Item]=Str_Data_Buffer;
				All_road_Data[Now_Item]=all_road-Str_Data_Buffer;//开始加速的里程
				All_angle_Data[Now_Item]=angle_buffer;
				All_road_Flag[Now_Item]=2;
				printf("L_ZHI,all_road:%ld,angle:%f,Long_road_Data:%d,Start:%d,Now_Item:%d\n",all_road,angle_buffer,Str_Data_Buffer,all_road-Str_Data_Buffer,Now_Item);
				Str_Data_Buffer=0;
				angle_buffer=0;
				Now_Item++;
				
			}
			else if(Str_Data_Buffer>Short_Stright_Flag)
			{
				Short_road_Data[Now_Item]=Str_Data_Buffer;
				Long_short_Data[Now_Item]=Str_Data_Buffer;
				All_road_Data[Now_Item]=all_road-Str_Data_Buffer;//开始加速的里程
				All_angle_Data[Now_Item]=angle_buffer;
				All_road_Flag[Now_Item]=1;
				printf("ZHI,all_road:%ld,angle:%f,Short_road_Data:%d,Start:%d,Now_Item:%d\n",all_road,angle_buffer,Str_Data_Buffer,all_road-Str_Data_Buffer,Now_Item);
				Str_Data_Buffer=0;
				angle_buffer=0;
				Now_Item++;
			}
			else
			{
				printf("None\n");
				Str_Data_Buffer=0;
				angle_buffer=0;
				
			}
		}
		Last_State_Road=Now_State_Road;
		if(Max_Item<Now_Item)
		{
			Max_Item=Now_Item;
		}
	}

}
/*
半惯导的速策
*/
void Half_State_of_road(int value)
{
	all_road+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;//得到直道的路程
	if(Acclerate_Flag==1)
	{
		Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
		if(Str_Data_Buffer<Short_road_Data[Now_Item]-ACC_Buffer)
		{
			Buzzer_ON();//短直道加速
			Motor_Update_Smooth(Short_ACC_Value);
		}
		else
		{
			Acclerate_Flag=0;
			Str_Data_Buffer=0;
			Buzzer_OFF();
			Now_Item++;
			printf("normal_S\n");
		}
		return;
	}
	else if(Acclerate_Flag==2)
	{
		Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
		if(Str_Data_Buffer<Long_road_Data[Now_Item]-ACC_Buffer)
		{
			Buzzer_ON();//chang直道加速
			Motor_Update_Smooth(Long_ACC_Value);
		}
		else
		{
			Acclerate_Flag=0;
			Str_Data_Buffer=0;
			
			Guan_Slow_Flag=1;
			
			Buzzer_OFF();
			Now_Item++;
			printf("normal_L\n");
		}
		return;
	}
	else
	{
		if(Guan_Slow_Flag )
		{
			Buzzer_ON();
			Motor_Update_Smooth(-10);
			if((encoder_data_dir_1 + encoder_data_dir_2)/2<(Left_Speed+Right_Speed)/2*100)
			{
				Guan_Slow_Flag=0;
			}
		}
		else
		{
			Buzzer_OFF();
			Speed_Control();
		}
	}

	if(all_road-All_road_Data[Now_Item]>-Data_Error && all_road-All_road_Data[Now_Item]<Long_short_Data[Now_Item]-Data_Error)
	{
		Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
		if(All_road_Flag[Now_Item]==1 && abs(angle-All_angle_Data[Now_Item])<=Angle_Error && abs(dajiao)<dajiao_Value)//短直道
		{
			Acclerate_Flag=1;
//			printf("ACC_Short!Recode:%ld,Now:%ld.\n",All_road_Data[Now_Item],all_road);
			
		}
		else if(All_road_Flag[Now_Item]==2 && abs(angle-All_angle_Data[Now_Item])<=Angle_Error && abs(dajiao)<dajiao_Value)
		{
			Acclerate_Flag=2;
//			printf("ACC_Long!Recode:%ld,Now:%ld.\n",All_road_Data[Now_Item],all_road);
		}
	}
	else if(all_road-All_road_Data[Now_Item]-Long_short_Data[Now_Item]>=0 && All_road_Data[Now_Item+1]!=0)
	{
		Now_Item++;
		printf("Worn\n");
		Str_Data_Buffer=0;
//		printf("all_road:%ld,All_road_Data:%ld\n",all_road,All_road_Data[Now_Item]);
	}
}
void angle_Get(void)
{
	if(angle_buffer==0)
	{
		angle_buffer=angle;
	}
	else 
	{
		angle_buffer+=angle;
		angle_buffer/=2;
	}
}
//		case Long_Stright:
//		{
//			Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
//			if(abs(dajiao)>value && delta_angle>Delta_Angle_Flag)
//			{
//				Turnways_Time++;
//				if(Turnways_Time>Turn_Mode_Time)
//				{
//					Now_State_Road=Turn_Ways;
//					Turnways_Time=0;
//					/****/
//				}
//			}
//			else
//			{
//				Turnways_Time=0;
//			}
//			break;
//		}
//		case Short_Stright:
//		{
//			Str_Data_Buffer+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
//			if(abs(dajiao)>value && delta_angle>Delta_Angle_Flag)
//			{
//				Turnways_Time++;
//				if(Turnways_Time>Turn_Mode_Time)
//				{
//					Now_State_Road=Turn_Ways;
//					
//					Turnways_Time=0;
//					/****/
//				}
//			}
//			else if(Str_Data_Buffer>Long_Stright_Flag)
//			{
//				Now_State_Road=Long_Stright;
//				angle_buffer=angle;
//			}
//			break;
//		}