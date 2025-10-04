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
    // 将频繁访问的结构体成员加载到局部变量
    float kp = servo_pid.Kp;           // 缓存到快速存储区
    float kd = servo_pid.Kd;
    float last_error = servo_pid.LastError;
    float error = Current;
	float temp ;
    
    // 使用局部变量计算
    float out = kp * error + kd * (error - last_error)+Help_turn();
    
    // 写回必要的结构体成员
    servo_pid.LastError = error;
    
    temp = func_limit_ab(out, Servo_min, Servo_max);
    return (int)(temp + (temp >= 0 ? 0.5f : -0.5f));
}
//int Servo_turn_pid(float Current)
//{
//    // 放大误差为整数
//    int32_t error = (int32_t)(Current * 100);             // ×100
//    int32_t last_error = (int32_t)(servo_pid.LastError);  // ×100
//    int32_t kp = (int32_t)(servo_pid.Kp * 100);           // ×100
//    int32_t kd = (int32_t)(servo_pid.Kd * 100);           // ×100

//    // 使用32位，防止溢出 ?
//    int32_t out = kp * error + kd * (error - last_error);  // ×10000

//    // 更新误差
//    servo_pid.LastError = error; // ? 保持 ×100 的误差存储方式

//    // 缩回到 ×1 倍输出（比如 -100~+100）
//    out = out / 10000;

//    // 限幅（这里 Servo_min / Servo_max 必须是 ×1 本身的范围） ?
//    if (out > Servo_max) out = Servo_max;
//    if (out < Servo_min) out = Servo_min;

//    return (int)out;  // ? 最终返回还是 "正常倍数"
//}

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
    if(pwm>0)
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
 * 函数名称：Motor_Update();
 * 输入参数：无
 * 输出参数：无
 * 可以进行拓展，写速度策略
 */
void Motor_Update()
{  
	switch(CAR_Mode)
	{
		case GO:
		{
			MotorR_SetSpeed(100*ML);
			MotorL_SetSpeed(100*MR);
		}break;
		case GO_Pararm1:
		{
			MotorR_SetSpeed(100*ML1);
			MotorL_SetSpeed(100*MR1);
		}break;
		case GO_Pararm2:
		{
			MotorR_SetSpeed(100*ML2);
			MotorL_SetSpeed(100*MR2);
		}break;
		case GO_Pararm3:
		{
			MotorR_SetSpeed(100*ML3);
			MotorL_SetSpeed(100*MR3);
		}break;
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
		}break;
		case GO_Pararm1:
		{
			servo_pid.Kp = KP1;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD1;
		}break;
		case GO_Pararm2:
		{
			servo_pid.Kp = KP2;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD2;
		}break;
		case GO_Pararm3:
		{
			servo_pid.Kp = KP3;
			servo_pid.Ki = 0;
			servo_pid.Kd = KD3;
		}break;
	}
	
}
