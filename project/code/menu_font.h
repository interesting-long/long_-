#ifndef __MENU_FONT_H__
#define __MENU_FONT_H__

#include "zf_common_headfile.h"
/*********************�˶�������������********************/
#define Servo_Mide (818)		//��Լ�Ķ����ֵ
#define Servo_max	 (80)		//��������ֵ
#define Servo_min  (-70)		//�������Сֵ		 	
/*********************��ʾ��������***********************/
/***��������*******/
#define Struct_Number 7         //�˵���ҳ��
#define Num_Col 7               //�����ݵ�����   ���12����Flash����
#define max_OLED_ROW 7          //16*8��������Ļ���������ʾ������

/*****��������******/

#define num_float_decimal  2    //���ݵ�С����λ��
#define num_float_int      3    //�����������ֵ�λ��

/******��ʾλ������*******/
#define Page_Row_Number 10       //һ���˵����������
#define Page_Col_Number 8      //һ�е����ַ�������󳤶�
#define ROW_DISTANCE     16      //�м��

#define Show_arrow_x  52        //��ʼ��ʾ��ͷ<��x����
#define Show_bujin_x  75        //��ʼ��ʾ����ֵ��x
#define Show_Num_x  102          //��ʼ��ʾ���ݵ�xֵ
#define Show_String_x  0        //��ʼ��ʾ�ַ�����x

extern float Num[Num_Col][Page_Row_Number];

extern unsigned char Page0_children[Page_Row_Number+1];
extern unsigned char Page1_children[Page_Row_Number+1];

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
extern float ADC_1;
extern float ADC_2;
extern float ADC_3;
extern float ADC_4;

/*******�궨����Ӧ����ֵ*******/



#define duqu_line   Num[2][6]
#define Time Num[3][1]
#define KP Num[1][1]
#define KD Num[1][2]
#define KP1 Num[1][3]
#define KD1 Num[1][4]
#define KP2 Num[1][5]
#define KD2 Num[1][6]
#define KP3 Num[1][7]
#define KD3 Num[1][8]
#define ML Num[2][1]
#define MR Num[2][2]
#define ML1 Num[2][4]
#define MR1 Num[2][5]
#define ML2 Num[2][6]
#define MR2 Num[2][7]
#define ML3 Num[2][8]
#define MR3 Num[2][9]
#define PRO Num[2][3]

#endif 