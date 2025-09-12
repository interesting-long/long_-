#ifndef __MENU_FONT_H__
#define __MENU_FONT_H__

#include "zf_common_headfile.h"
/*********************�˶�������������********************/
#define Servo_Mide 740		//��Լ
/*********************��ʾ��������***********************/
/***��������*******/
#define Struct_Number 7         //�˵���ҳ��
#define Num_Col 7               //�����ݵ�����   ���12����Flash����
#define max_OLED_ROW 7          //16*8��������Ļ���������ʾ������

/*****��������******/

#define num_float_decimal  2    //���ݵ�С����λ��
#define num_float_int      2    //�����������ֵ�λ��

/******��ʾλ������*******/
#define Page_Row_Number 9       //һ���˵����������
#define Page_Col_Number 8      //һ�е����ַ�������󳤶�
#define ROW_DISTANCE     16          //�м��

#define Show_arrow_x  60        //��ʼ��ʾ��ͷ<��x����
#define Show_bujin_x  75        //��ʼ��ʾ����ֵ��x
#define Show_Num_x  90          //��ʼ��ʾ���ݵ�xֵ
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
#define ser_Max_KP  Num[0][1]   //����KPֵ
#define ser_Max_KD  Num[0][2]   //����KDֵ
#define ser_Min_KP  Num[0][3]   //��С��KPֵ
#define ser_Min_KD  Num[0][4]   //��С��KDֵ
#define ser_yu      Num[0][5]   //���pidֱ��������ֵ

#define MorR_Max    Num[1][1]   //���ֵ�����ٶ�
#define MorL_Max    Num[1][2]   //���ֵ�����ٶ�

#define M_Time      Num[3][1]   //��ʱʱ�䣨s��
#define sp_time     Num[3][2]   //���ٵ��ж�ʱ��
#define jian_time   Num[3][3]   //���ٵ�ʱ��
#define long_time   Num[3][4]   //�жϳ�ֱ����ʱ��
#define lvv_time    Num[3][5]
#define Kai         Num[3][6]

#define diff_yu     Num[4][1]   //�жϲ��ٵ���ֵ
#define diff_kp     Num[4][2]   //���ٵ�kpֵ
#define speed_err   Num[4][3]   //ֱ�����ٵ���ֵ
#define speed_add   Num[4][4]   //ֱ�����ٴ�С


#define duqu_line   Num[2][6]

#endif