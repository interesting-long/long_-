#ifndef __FUNCTION_H__
#define __FUNCTION_H__


#include "zf_common_headfile.h"

#define ENCODER_DIR_1                 	(TIM0_ENCOEDER)                         // 正交编码器对应使用的编码器接口 这里使用QTIMER1的ENCOEDER1
#define ENCODER_DIR_DIR_1              	(IO_P35)            				 	// DIR 对应的引脚
#define ENCODER_DIR_PULSE_1            	(TIM0_ENCOEDER_P34)            			// PULSE 对应的引脚

#define ENCODER_DIR_2                 	(TIM3_ENCOEDER)                         // 带方向编码器对应使用的编码器接口 这里使用QTIMER1的ENCOEDER2
#define ENCODER_DIR_DIR_2           	(IO_P13)             					// DIR 对应的引脚
#define ENCODER_DIR_PULSE_2       		(TIM3_ENCOEDER_P04)            			// PULSE 对应的引脚
extern int Set_T;
extern int T3;
typedef unsigned char 		uint8_t 	;
typedef unsigned int	 	uint16_t 	;
typedef int	 				int16_t 	;
typedef unsigned long int 	uint32_t 	;
typedef long int 			int32_t 	;
typedef struct
{
        float Kp;
        float Ki;
        float Kd;
        float LowPass;

        float Out_P;
        int32 Out_I;
        float Out_D;

        float PrevError;
        float LastError;
        float Error;
        float Last_Out;
}PID;
extern PID servo_pid;
extern PID M_left_pid;
extern PID M_Right_pid;
extern unsigned char Protect_flag;
extern int16 encoder_data_dir_1;
extern int16 encoder_data_dir_2;
extern unsigned char GO_PID_Control;
extern unsigned char GO_PID_Control1;
extern unsigned char GO_PID_Control2;
extern unsigned char GO_PID_Control3;
/*外部调用函数*/
float unification(void);
float fast_sqrt(float number);
float Normal_PID(PID *PID,float NowData,float Point);
void Protect();
void init_all();
void Turn_mode_Init(void);
void Show_pararm();
void GO_Function(void);
void  enconder_init(void);
void speed_control_ring(void);
void Speed_Control(void);
void Servo_Control(void);
/*内部调用函数*/
void show_test_info(const char* info) ;
void Motor_Init(void);
void Servo_Init();
void CAR_STOP();
void SET_Time();
extern unsigned char Init_Fg;
extern unsigned char Servo_Flag;
extern unsigned char Key_Flag;
extern unsigned char ADC_Show_Flag;
extern int dajiao;
#endif