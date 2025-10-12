#include "control.h"

unsigned char CAR_Mode=STOP;
void Ser_Servo_Duty(int value)
{
    pwm_set_duty(Servo_Pwm,value);
}
 /*函数：舵机的pid控制
 * 作用：利用电磁归一化后的信号控制舵机，
 * 参数1：设定的归一化目标值
 * 参数2：舵机最小转向值
 * 参数3：舵机最大转向值
 * 例子：Servo_turn_pid(变量,-80,80);
 * 将变量的值与0进行对比，输出信号控制舵机,而舵机的限幅是正负80
 */
int Servo_turn_pid(float Current)
{
    float kp = servo_pid.Kp;           
    float kd = servo_pid.Kd;
    float last_error = servo_pid.LastError;
    float error = Current;
	float temp ;
    
    float out = kp * error + kd * (error - last_error);
    
    servo_pid.LastError = error;
    
    temp = func_limit_ab(out, Servo_min, Servo_max);
    return (int)(temp + (temp >= 0 ? 0.5f : -0.5f));
}
/*
*左路速度环控制
*/
int Motor_left_pid(int point)
{
    // 将频繁访问的结构体成员加载到局部变量
    float kp = M_left_pid.Kp;       
	float ki = M_left_pid.Ki;
    float error = point - encoder_data_dir_1;
	float out = 0 ;
	M_left_pid.Out_I += error;
	if(M_left_pid.Out_I>Motor_Max){M_left_pid.Out_I=Motor_Max;}
	else if(M_left_pid.Out_I<-Motor_Max){M_left_pid.Out_I=-Motor_Max;}
    // 使用局部变量计算
    out = kp * error + ki * M_left_pid.Out_I;
    if (out > 8000) out = 8000;
	else if (out < -8000) out = -8000;
    return (int)(out);
}
/*
*右路速度环控制
*/

int Motor_Right_pid(int point)
{
    // 将频繁访问的结构体成员加载到局部变量
    float kp = M_Right_pid.Kp;       
	float ki = M_Right_pid.Ki;
    float error = point - encoder_data_dir_2;
	float out = 0 ;
    M_Right_pid.Out_I += error;
	if(M_Right_pid.Out_I>Motor_Max){M_Right_pid.Out_I=Motor_Max;}
	else if(M_Right_pid.Out_I<-Motor_Max){M_Right_pid.Out_I=-Motor_Max;}
    // 使用局部变量计算
    out = kp * (error) + ki * (M_Right_pid.Out_I);
    if (out > 8000) out = 8000;
	else if (out < -8000) out = -8000;
    return (int)(out);
}
/*
 * 函数功能：左路电机PWM设置
 * 函数名称：MotorL_SetSpeed(unsigned char);
 * 输入参数：想要的PWM值
 * 输出参数：无
 */
void MotorL_SetSpeed(int pwm)
{

	if(pwm>=0)
    {
        pwm_set_duty(MotorL_pwm1,pwm);
        pwm_set_duty(MotorL_pwm2,0);
    }
    else
    {
        pwm_set_duty(MotorL_pwm2,-pwm);
        pwm_set_duty(MotorL_pwm1,0);
    }
}
/*
 * 函数功能：右路电机PWM设置
 * 函数名称：MotorR_SetSpeed(unsigned char);
 * 输入参数：想要的PWM值
 * 输出参数：无
 */
void MotorR_SetSpeed(int pwm)
{
    if(pwm>=0)
    {
        pwm_set_duty(MotorR_pwm1,pwm);
        pwm_set_duty(MotorR_pwm2,0);
    }
    else
    {
        pwm_set_duty(MotorR_pwm2,-pwm);
        pwm_set_duty(MotorR_pwm1,0);
    }
}
/*
 * 函数功能：电机驱动更新
 * 函数名称：Motor_Update(0);
 * 输入参数：无
 * 输出参数：无
 * 可以进行拓展，写速度策略
 */
void Motor_Update(char X)
{ 
	if(GO_PID_Control+GO_PID_Control1+GO_PID_Control2+GO_PID_Control3==1)
	{
		switch(CAR_Mode)
		{
			case GO:
			{
//				if(M_Mod>1)
//				{
				MotorL_SetSpeed(Motor_left_pid((ML+X)*100));
				MotorR_SetSpeed(Motor_Right_pid((MR+X)*100));
//				}
//				else
//				{
//				MotorL_SetSpeed((ML+X)*100);
//				MotorR_SetSpeed((MR+X)*100);
//				}
				break;
			}	
			case GO_Pararm1:
			{
//				if(M_Mod1>1)
//				{
				MotorL_SetSpeed(Motor_left_pid((ML1+X)*100));
				MotorR_SetSpeed(Motor_Right_pid((MR1+X)*100));
//				}
//				else
//				{
//				MotorL_SetSpeed((ML1+X)*100);
//				MotorR_SetSpeed((MR1+X)*100);
//				}
				break;
			}	
			case GO_Pararm2:
			{
//				if(M_Mod2>1)
//				{
				MotorL_SetSpeed(Motor_left_pid((ML2+X)*100));
				MotorR_SetSpeed(Motor_Right_pid((MR2+X)*100));
//				}
//				else
//				{
//				MotorL_SetSpeed((ML2+X)*100);
//				MotorR_SetSpeed((MR2+X)*100);
//				}
				break;
			}	
			case GO_Pararm3:
			{
//				if(M_Mod3>1)
//				{
				MotorL_SetSpeed(Motor_left_pid((ML3+X)*100));
				MotorR_SetSpeed(Motor_Right_pid((MR3+X)*100));
//				}
//				else
//				{
//				MotorL_SetSpeed((ML3+X)*100);
//				MotorR_SetSpeed((MR3+X)*100);
//				}
				break;
			}		
			default:
			{
				MotorL_SetSpeed(0);
				MotorR_SetSpeed(0);
				M_Right_pid.Out_I=0;
				M_left_pid.Out_I=0;
				break;
			}
		
		}
	}
	
}
void PID_Update()
{  
	switch(CAR_Mode)
	{
		case GO:
		{
			servo_pid.Kp = KP;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD;
			M_left_pid.Kp = ML_KP;
			M_left_pid.Ki = ML_KI;
			M_Right_pid.Kp = MR_KP;
			M_Right_pid.Ki = MR_KI;
		}break;
		case GO_Pararm1:
		{
			servo_pid.Kp = KP1;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD1;
			M_left_pid.Kp = ML_KP1;
			M_left_pid.Ki = ML_KI1;
			M_Right_pid.Kp = MR_KP1;
			M_Right_pid.Ki = MR_KI1;
		}break;
		case GO_Pararm2:
		{
			servo_pid.Kp = KP2;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD2;
			M_left_pid.Kp = ML_KP2;
			M_left_pid.Ki = ML_KI2;
			M_Right_pid.Kp = MR_KP2;
			M_Right_pid.Ki = MR_KI2;
		}break;
		case GO_Pararm3:
		{
			servo_pid.Kp = KP3;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD3;
			M_left_pid.Kp = ML_KP3;
			M_left_pid.Ki = ML_KI3;
			M_Right_pid.Kp = MR_KP3;
			M_Right_pid.Ki = MR_KI3;
		}break;
	}
	
}

void Cycle_Update(void)
{
	switch(CAR_Mode)
	{
		case GO:
		{
			Entern_Flag_Time	=Entern_Flag_Time0		;
			Entern_Delay_Time	=Entern_Delay_Time0		;
			Entern_Continue_Time=Entern_Continue_Time0	;
			Mode_Flag			=Mode_Flag0				;
			turn_Value 			=turn_Value0			;
		}break;
		case GO_Pararm1:
		{
			Entern_Flag_Time	=Entern_Flag_Time1		;
			Entern_Delay_Time	=Entern_Delay_Time1		;
			Entern_Continue_Time=Entern_Continue_Time1	;
			Mode_Flag			=Mode_Flag1				;
			turn_Value 			=turn_Value1			;
		}break;
		case GO_Pararm2:
		{
			Entern_Flag_Time	=Entern_Flag_Time2		;
			Entern_Delay_Time	=Entern_Delay_Time2		;
			Entern_Continue_Time=Entern_Continue_Time2	;
			Mode_Flag			=Mode_Flag2				;
			turn_Value 			=turn_Value2			;
		}break;
		case GO_Pararm3:
		{
			Entern_Flag_Time	=Entern_Flag_Time3		;
			Entern_Delay_Time	=Entern_Delay_Time3		;
			Entern_Continue_Time=Entern_Continue_Time3	;
			Mode_Flag			=Mode_Flag3				;
			turn_Value 			=turn_Value3			;
		}break;
	}
}

