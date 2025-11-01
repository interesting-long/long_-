#include "Strategy.h"



/**********�����Ĳ���******************/
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
/**********�ٲ�Ĳ���******************/
        /**�޹��Ե���**/
unsigned char Road_Stat=Long_Str;
unsigned int Short_Time=0;
unsigned int Long_Time=0;
unsigned int Bend_Time=0;
unsigned int SLOW_Time=0;
unsigned int Accel_Time=0;
/***************�й��Ե���**********/
			/*��¼����������*/
//#define Panduan_Time 30		//״̬ת������ֵ
//#define tuoluo 0.4			//�Ǽ��ٶ��ж�ֱ����ֵ
//#define long_Str_yuzhi 10000
float angle = 0;						//�Ƕ�
long int Range_Data[100]={0};				//�����ĳ�����Ϣ
long int Last_Range_Data[100]={0};			//�ϴ������ĳ�����Ϣ
unsigned char Fires_Init=1;					//�Ƿ��һ�μ�¼�ı�־λ
unsigned char Road_information[100]={0};	//�����ı�ǩ��Ϣ
int Inertial_Time=0;						//�洢λֵ��ʱ��

long int Long_road[20]={0};					//�������ĳ�����Ϣ	
float long_road_angle[20]={0};			//��ֱ���Ƕ���Ϣ
float  Str_Data=0;							//ֱ���洢
int Zhi_Falg=0;
float  Bend_Data=0;							//����洢
int Wan_Falg=0;
road_Data Type_road=str_data;				//��ǰ����״̬
unsigned char Last_stact=str_data;			//�ϴ�����״̬
			/*******�ٲ⺯��������*******/
#define angle_num 300		//anglec����������
//#define cha_angle 15		//��֤�Ƕȵ�ƫ����
//#define Iner_Acc_Value 3.5	//���ٵ��ٶ�
//#defien Iner_Slo_Value -0.5
#define Iner_Divade 5		//��ֱ����·��(n-1)/n
#define Iner_Divade_Value 3		//��ֱ����·��(n-1)/n

float delta_angle=0;
//unsigned char Road_Stat=Long_Str;		
float State_Data_Str=0;					//��ֱ�洢
float State_Data_Bend=0;				//����洢

unsigned char Long_road_Time=0;			//�ٲ��ִ�м�����
unsigned char finsh_Flag = 0;			//����ִ�б�־λ
unsigned char ACC_Flag = 0;				//���ټ���־λ
unsigned char Show_Init = 1;
float angle_buffer1=0;					//�Ƕȼ��㻺��
int current_angle_time=0;				//�Ƕȼ��������		

//�����ж�
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
					if2_time++;
					if(if2_time>Entern_Delay_Time)
					{
						Cycle_Stat=Left_ENTER;
						angle=0;
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
//���䲹��
int Help_turn()
{
	int left  = ADC_1 + ADC_2;
	int right = ADC_3 + ADC_4;
	if (left < 200 && right < 200)
	{
		// ͬʱ���㣬ȡ��Сһ������
		if (left < right)
			return -50;   // ��
		else
			return 50;    // ��
	}
	else if (left < 200)
	{
		return -50;   // ��
	}
	else if (right < 200)
	{
		return 50;    // ��
	}
	else
	{
		return 0;     // ��ת
	}
}
void Help_turn2(int temp, int value, int ADC_Flag)
{
    static int last_dir = 0;    // -1 ��+1 �ң�0 δ��
    static int first_double = 1; // �Ƿ��ǵ�һ�ν��롰˫С��״̬

    int left  = ADC_1 + ADC_2;
    int right = ADC_3 + ADC_4;
	int target=0;
	
	static float smooth_temp = 0;
    const int delta = 30;  // ���ҽӽ�����С��ֵ����
	const float smooth=0.4;
	if(left < ADC_Flag || right < ADC_Flag)
	{
		if (left < ADC_Flag && right < ADC_Flag)
		{
			if (first_double) // ���һ��˫С
			{
				if (left < right)
				{
					target = -value;   // ��
					last_dir = -1;
				}
				else
				{
					target = value;    // ��
					last_dir = 1;
				}
				first_double = 0; // ����Ѿ��������һ��
			}
			else // �����˫С
			{
				if (abs(left - right) < delta)
				{
					// �����ϴη�����
					if (last_dir == -1) target = -value;
					else if (last_dir == 1) target = value;
					else target = value; // Ĭ��
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
			first_double = 1; // ���ã��´���������˫С��ʱ�����ߵ�һ���߼�
		}
		else
		{
			target = value;
			last_dir = 1;
			first_double = 1; // ͬ��
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
    static int last_dir = 0;    // -1 ��+1 �ң�0 δ��
    static int first_double = 1; // �Ƿ��ǵ�һ�ν��롰˫С��״̬
    int left  = ADC_1 + ADC_2;
    int right = ADC_3 + ADC_4;
	float K = (float)(value2 - value) / (ADC_Flag - ADC_Flag2);
    const int delta = 30;  // ���ҽӽ�����С��ֵ����

    if (left < ADC_Flag && right < ADC_Flag)
    {
		if (left < ADC_Flag2 && right < ADC_Flag2)
		{
			if (first_double) // ���һ��˫С
			{
				if (left < right)
				{
					*temp = -value2;   // ��
					last_dir = -1;
				}
				else
				{
					*temp = value2;    // ��
					last_dir = 1;
				}
				first_double = 0; // ����Ѿ��������һ��
			}
			else // �����˫С
			{
				if (abs(left - right) < delta)
				{
					// �����ϴη�����
					if (last_dir == -1) *temp = -value2;
					else if (last_dir == 1) *temp = value2;
					else *temp = value2; // Ĭ��
					    // ����ת
      // ����ת
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
			first_double = 1; // ͬ��
		}
		else
		{
			if (abs(left - right) < delta)
			{
				// �����ϴη�����
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

    // -------- ��һ����ֵ�ж� --------
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

    // -------- �ڶ�����ֵ�ж� --------
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

    // -------- �������㣬����ԭֵ --------
    return temp;
}
/*

*/
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
					if(Accel_Time>150)//����ʱ��1.5s
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
				Motor_Update_Smooth(Bend_speed);//����ٶ�
			}
			else
			{
				Buzzer_ON();
				
				Motor_Update_Smooth(L_Turn_B_Slow_Value);//����
			}
			//����Ƿ�ص���ֱ��
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

void Inertial_Navigation(int value)//��¼����
{
	switch(Type_road)
	{
		case str_data:
		{
			Str_Data+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
			if(abs(dajiao)>=value && abs(delta_angle)>=tuoluo)//error,detal_error,ƫ���ǣ�abs(dajiao)>=value&& abs(imu963ra_gyro_y/100)>=30 && abs(Last_dajiao-dajiao)>=100
			{
				Wan_Falg++;
				if(Wan_Falg>Panduan_Time)
				{
					Type_road=wan_data;
					current_angle_time=0;
					angle_buffer1=0;
					Wan_Falg=0;
				}
			}
			else 
			{
				Wan_Falg=0;
				if(Str_Data>2000 && Str_Data<long_Str_yuzhi*100-2000)				//��¼��ֱ���ĽǶ�
				{
					angle_Get(angle,angle_num);
				}
				else if(Str_Data>long_Str_yuzhi*100)
				{
					Type_road=long_str_data;
					current_angle_time=0;
				}
			}
			break;
		}
		case long_str_data:
		{
			Str_Data+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
			if(abs(dajiao)>=value && abs(delta_angle)>=tuoluo)//error,detal_error,ƫ���ǣ�abs(dajiao)>=value&& abs(imu963ra_gyro_y/100)>=30 && abs(Last_dajiao-dajiao)>=100
			{
				Wan_Falg++;
				if(Wan_Falg>Panduan_Time)
				{
					Type_road=wan_data;
					Wan_Falg=0;
				}
			}
			else
			{
				Wan_Falg=0;
			}
			break;
		}
		case wan_data:
		{
			Bend_Data+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;
			if(abs(delta_angle)<tuoluo && abs(Last_dajiao-dajiao)<100)
			{
				Zhi_Falg++;
				if(Zhi_Falg>Panduan_Time)
				{
					Type_road=str_data;
					Zhi_Falg=0;
				}
			}
			else
			{
				Zhi_Falg=0;
			}
			break;
		}
	}
	if(Type_road != Last_stact)
	{
		if(Last_stact == wan_data)
		{
			Road_information[Inertial_Time]=1;//1Ϊ���
			Range_Data[Inertial_Time]=Bend_Data;
			if(Fires_Init)
			{
				Last_Range_Data[Inertial_Time]=Range_Data[Inertial_Time];
				Fires_Init=0;
			}
			else
			{
				Last_Range_Data[Inertial_Time]=(Last_Range_Data[Inertial_Time]+Range_Data[Inertial_Time])/2;
			}
			Inertial_Time++;
			Bend_Data=0;
		}
		else if(Last_stact == str_data && Type_road==wan_data)
		{
			Road_information[Inertial_Time]=2;//2Ϊֱ��
			Range_Data[Inertial_Time]=Str_Data;
			if(Fires_Init)
			{
				Last_Range_Data[Inertial_Time]=Range_Data[Inertial_Time];
				Fires_Init=0;
			}
			else
			{
				Last_Range_Data[Inertial_Time]=(Last_Range_Data[Inertial_Time]+Range_Data[Inertial_Time])/2;
			}
			Inertial_Time++;
			Str_Data=0;
		}
		else if(Last_stact == long_str_data)
		{
			Road_information[Inertial_Time]=3;//3Ϊ��ֱ��
			Range_Data[Inertial_Time]=Str_Data;
			/****��ֱ����****/
			Long_road[Long_road_Time]=Str_Data;
			long_road_angle[Long_road_Time]=angle_buffer1;
			if(Fires_Init)
			{
				Last_Range_Data[Inertial_Time]=Range_Data[Inertial_Time];
				Fires_Init=0;
			}
			else
			{
				Last_Range_Data[Inertial_Time]=(Last_Range_Data[Inertial_Time]+Range_Data[Inertial_Time])/2;
			}
//			printf("Num:%d,%f,%f\n",Long_road_Time,angle_buffer1,Str_Data);
			Inertial_Time++;
			Long_road_Time++;
			Str_Data=0;
			angle_buffer1=0;
		}
		Last_stact=Type_road;
	}
}
/*
��ߵ����ٲ�
*/
void Half_State_of_road(int value)
{
	switch(Road_Stat)
	{
		case Long_Str:			//������־λfinsh_Flag�������Ƿ����	ACC_Flag���Ƿ�ʼ����
		{
			State_Data_Str+=(encoder_data_dir_1 + encoder_data_dir_2) / 20;//�õ�ֱ����·��
			if(Show_Init && State_Data_Str>long_Str_yuzhi*100)
			{
//				printf("angle:%f,buffer:%f,Num:%d\n",angle,long_road_angle[Long_road_Time],Long_road_Time);
				Show_Init=0;
			}
			if(		finsh_Flag==0 										//��֤һ��ֱ��ִ��һ��
				&& abs(angle -long_road_angle[Long_road_Time])<cha_angle 	//��֤����λ��
				&& abs(delta_angle)<tuoluo)
			{
				ACC_Flag=1;
			}
			if(ACC_Flag==1)
			{
				if((int)State_Data_Str<=Long_road[Long_road_Time]*Iner_Divade_Value/Iner_Divade)//3/4��·�̽��м��٣�ֻҪ����ͼ����꣩
				{
					Motor_Update_Smooth(Iner_Acc_Value);
					finsh_Flag=1;
					Buzzer_ON();
				}
				else
				{
					ACC_Flag=2;
				}
			}
			else if(ACC_Flag == 2)
			{
				Buzzer_OFF();
				Motor_Update_Smooth(Iner_Slo_Value);
			}
			else
			{
				Buzzer_OFF();
				Motor_Update_Smooth(0);
			}
			if(abs(dajiao)>=value && abs(delta_angle)>=tuoluo)
			{
				Bend_Time++;
				if(Bend_Time>Panduan_Time)
				{
					Road_Stat = Short_Bend;
					State_Data_Str=0;				//·���ۼ���
					Show_Init=1;
					ACC_Flag=0;
					if(finsh_Flag)
					{
					Long_road_Time++;
					finsh_Flag=0;
					}
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
			Motor_Update_Smooth(0);
			Buzzer_OFF();
			if(abs(dajiao)<value&& abs(delta_angle)<tuoluo)
			{
				Long_Time++;
				if(Long_Time>Panduan_Time)
				{
					Road_Stat = Long_Str;
					Long_Time=0;
				}
			}
			else
			{
				Long_Time = 0;
			}
			break;
		}
	}
}

void angle_Get(int value,int Count)
{
	if(angle_buffer1==0)
	{
		angle_buffer1=value;
	}
	else if(current_angle_time<Count)
	{
		current_angle_time++;
		angle_buffer1+=value;
		angle_buffer1/=2;
	}
}