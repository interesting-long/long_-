#ifndef __MENU_FONT_H__
#define __MENU_FONT_H__

#include "zf_common_headfile.h"
/*********************运动参数常量设置********************/
#define Servo_Mide 740		//大约
/*********************显示常量设置***********************/
/***基础设置*******/
#define Struct_Number 7         //菜单的页数
#define Num_Col 7               //有数据的行数   最大12！！Flash限制
#define max_OLED_ROW 7          //16*8字体在屏幕当中最多显示的行数

/*****数据设置******/

#define num_float_decimal  2    //数据的小数点位数
#define num_float_int      2    //数据整数部分的位数

/******显示位置设置*******/
#define Page_Row_Number 9       //一级菜单的最大行数
#define Page_Col_Number 8      //一行当中字符串的最大长度
#define ROW_DISTANCE     16          //行间距

#define Show_arrow_x  60        //开始显示箭头<的x坐标
#define Show_bujin_x  75        //开始显示步进值的x
#define Show_Num_x  90          //开始显示数据的x值
#define Show_String_x  0        //开始显示字符串的x

extern float Num[Num_Col][Page_Row_Number];

extern unsigned char Page0_children[Page_Row_Number+1];
extern unsigned char Page1_children[Page_Row_Number+1];

struct Menu
{
    unsigned char index;        //数据行数编号
    char page[Page_Row_Number][Page_Col_Number];           //页面内容
    struct Menu *father;        //父节点
    struct Menu *children[Page_Row_Number];      //子节点
};
extern struct Menu Page[Struct_Number];
extern struct Menu *Pin;//灵活指针
//ADC参数
extern float ADC_1;
extern float ADC_2;
extern float ADC_3;
extern float ADC_4;

/*******宏定义相应的数值*******/
#define ser_Max_KP  Num[0][1]   //最大的KP值
#define ser_Max_KD  Num[0][2]   //最大的KD值
#define ser_Min_KP  Num[0][3]   //最小的KP值
#define ser_Min_KD  Num[0][4]   //最小的KD值
#define ser_yu      Num[0][5]   //舵机pid直弯分离的阈值

#define MorR_Max    Num[1][1]   //右轮的最大速度
#define MorL_Max    Num[1][2]   //左轮的最大速度

#define M_Time      Num[3][1]   //定时时间（s）
#define sp_time     Num[3][2]   //加速的判断时间
#define jian_time   Num[3][3]   //减速的时间
#define long_time   Num[3][4]   //判断长直道的时间
#define lvv_time    Num[3][5]
#define Kai         Num[3][6]

#define diff_yu     Num[4][1]   //判断差速的阈值
#define diff_kp     Num[4][2]   //差速的kp值
#define speed_err   Num[4][3]   //直道加速的阈值
#define speed_add   Num[4][4]   //直道加速大小


#define duqu_line   Num[2][6]

#endif