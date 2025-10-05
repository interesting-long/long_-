#ifndef __MENU_FONT_H__
#define __MENU_FONT_H__

#include "zf_common_headfile.h"
/*********************运动参数常量设置********************/
#define Servo_Mide (907)		//大约的舵机中值818
#define Servo_max	 (85)		//舵机的最大值
#define Servo_min  (-77)		//舵机的最小值		 	
/*********************显示常量设置***********************/
/***基础设置*******/
#define Struct_Number 8         //菜单的页数
#define Num_Col 8               //有数据的行数   最大12！！Flash限制
#define max_OLED_ROW 7          //16*8字体在屏幕当中最多显示的行数

/*****数据设置******/

#define num_float_decimal  2    //数据的小数点位数
#define num_float_int      3    //数据整数部分的位数

/******显示位置设置*******/
#define Page_Row_Number 10       //一级菜单的最大行数
#define Page_Col_Number 8      //一行当中字符串的最大长度
#define ROW_DISTANCE     16      //行间距

#define Show_arrow_x  60        //开始显示箭头<的x坐标
#define Show_bujin_x  110        //开始显示步进值的x
#define Show_Num_x  102          //开始显示数据的x值
#define Show_String_x  0        //开始显示字符串的x

extern float Num[Num_Col][Page_Row_Number];

extern unsigned char Page0_children[Page_Row_Number+1];
extern unsigned char Page5_children[Page_Row_Number+1];

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
extern unsigned int ADC_1;
extern unsigned int ADC_2;
extern unsigned int ADC_3;
extern unsigned int ADC_4;
/*******宏定义相应的数值*******/





#define Pro Num[0][6]

#define KP Num[1][1]
#define KD Num[1][2]
#define ML Num[1][3]
#define MR Num[1][4]
#define Entern_Flag_Time0 		Num[1][5]
#define Entern_Continue_Time0 	Num[1][6]
#define Entern_Delay_Time0 		Num[1][7]
#define Mode_Flag0 				Num[1][8]
#define turn_Value0 			Num[1][9]

#define KP1 Num[2][1]
#define KD1 Num[2][2]
#define ML1 Num[2][3]
#define MR1 Num[2][4]
#define Entern_Flag_Time1 		Num[2][5]
#define Entern_Continue_Time1 	Num[2][6]
#define Entern_Delay_Time1 		Num[2][7]
#define Mode_Flag1 				Num[2][8]
#define turn_Value1 			Num[2][9]

#define KP2 Num[3][1]
#define KD2 Num[3][2]
#define ML2 Num[3][3]
#define MR2 Num[3][4]
#define Entern_Flag_Time2 		Num[3][5]
#define Entern_Continue_Time2 	Num[3][6]
#define Entern_Delay_Time2 		Num[3][7]
#define Mode_Flag2 				Num[3][8]
#define turn_Value2 			Num[3][9]

#define KP3 Num[4][1]
#define KD3 Num[4][2]
#define ML3 Num[4][3]
#define MR3 Num[4][4]
#define Entern_Flag_Time3		Num[4][5]
#define Entern_Continue_Time3 	Num[4][6]
#define Entern_Delay_Time3 		Num[4][7]
#define Mode_Flag3 				Num[4][8]
#define turn_Value3 			Num[4][9]

#define S_Value Num[5][3]

#define Test_LPWM Num[6][1]
#define Test_RPWM Num[6][2]

#define Short_add			Num[7][1]
#define Short_Judge_Time	Num[7][2]
#define Long_add 			Num[7][3]
#define Long_Judge_Time 	Num[7][4]
#define Bend_slow 			Num[7][5]
#define Bend_Slow_Time 		Num[7][6]
#define Stright_Flag_Value 	Num[7][7]
#define Bend_Flag_Value 	Num[7][8]
#endif 