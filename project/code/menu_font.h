#ifndef __MENU_FONT_H__
#define __MENU_FONT_H__

#include "zf_common_headfile.h"
/*********************�˶�������������********************/
#define Servo_Mide (907)		//��Լ�Ķ����ֵ818
#define Servo_max	 (85)		//��������ֵ
#define Servo_min  (-77)		//�������Сֵ		 	
/*********************��ʾ��������***********************/
/***��������*******/
#define Struct_Number 8         //�˵���ҳ��
#define Num_Col 8               //�����ݵ�����   ���12����Flash����
#define max_OLED_ROW 7          //16*8��������Ļ���������ʾ������

/*****��������******/

#define num_float_decimal  2    //���ݵ�С����λ��
#define num_float_int      3    //�����������ֵ�λ��

/******��ʾλ������*******/
#define Page_Row_Number 10       //һ���˵����������
#define Page_Col_Number 8      //һ�е����ַ�������󳤶�
#define ROW_DISTANCE     16      //�м��

#define Show_arrow_x  60        //��ʼ��ʾ��ͷ<��x����
#define Show_bujin_x  110        //��ʼ��ʾ����ֵ��x
#define Show_Num_x  102          //��ʼ��ʾ���ݵ�xֵ
#define Show_String_x  0        //��ʼ��ʾ�ַ�����x

extern float Num[Num_Col][Page_Row_Number];

extern unsigned char Page0_children[Page_Row_Number+1];
extern unsigned char Page5_children[Page_Row_Number+1];

struct Menu
{
    unsigned char index;        //�����������
    char page[Page_Row_Number][Page_Col_Number];           //ҳ������
    struct Menu *father;        //���ڵ�
    struct Menu *children[Page_Row_Number];      //�ӽڵ�
};
extern struct Menu Page[Struct_Number];
extern struct Menu *Pin;//���ָ��
//ADC����
extern unsigned int ADC_1;
extern unsigned int ADC_2;
extern unsigned int ADC_3;
extern unsigned int ADC_4;
/*******�궨����Ӧ����ֵ*******/





#define Time Num[0][6]

#define KP Num[1][1]
#define KD Num[1][2]
#define ML Num[1][3]
#define MR Num[1][4]

#define KP1 Num[2][1]
#define KD1 Num[2][2]
#define ML1 Num[2][3]
#define MR1 Num[2][4]

#define KP2 Num[3][1]
#define KD2 Num[3][2]
#define ML2 Num[3][3]
#define MR2 Num[3][4]

#define KP3 Num[4][1]
#define KD3 Num[4][2]
#define ML3 Num[4][3]
#define MR3 Num[4][4]

#define S_Value Num[5][3]

#define Test_LPWM Num[6][1]
#define Test_RPWM Num[6][2]

#define turn_Value 				Num[7][1]
#define Entern_Flag_Time 		Num[7][2]
#define Entern_Continue_Time 	Num[7][3]
#define NOT_Time 				Num[7][4]
#define Mode_Flag 				Num[7][5]
#endif 