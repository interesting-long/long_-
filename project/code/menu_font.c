#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1  ,1   ,2  ,3  ,4  ,-1,5  ,-1 ,-1,-1},
        {-1  ,28  ,280,32 ,32 ,6 ,400,30 ,5 ,60 },
        {-1  ,30  ,300,35 ,35 ,6 ,310,20 ,5 ,60},
        {-1  ,31  ,310,37 ,37 ,6 ,280,15 ,5 ,60},
        {-1  ,32.5,325,39 ,39 ,6 ,250,10 ,5 ,60 },
        {-1  ,-1  ,-1 ,840,-1 ,-1,-1 ,-1 ,-1,-1 },
		{-1  ,20  ,20 ,3  ,-1 ,-1,-1 ,-1 ,-1,-1 },
        {-1  ,1  ,5 ,2 ,16 ,-30,10 ,15 ,40, }};//���ݴ洢������

unsigned char Page0_children[Page_Row_Number+1]={0,1,2,3,4,7,0,0,5};//���ֽڲ˵�,�ڶ���������ת��Page[1],Page[2]��Page[3]��Page[4]��
unsigned char Page5_children[Page_Row_Number+1]={0, 6};//���ֽڲ˵�,�ڶ�����ת��Page[5],Page[6]


/*�ṹ���һ����   ���кš����������ڿ�����ʾ���ݵ��߼�(���к��Ƕ��٣�����ʾ��һ���������)
 *�ṹ��ڶ�����   ��ʾ������
 *�ṹ���������   ��ָ����(�����Զ����ã�
 *�ṹ���������   ��ָ������(λ�ö�Ӧ����)�ú�������
 */
struct Menu Page[Struct_Number]={
    {   0,
            {"back","GOP","GOP1","GOP2","GOP3","Time","Pro","ADC","Test"}},
    {   1,
            {"back","KP","KD","R_PWM","L_PWM","J_time","C_time","D_Time","LorR","turn"}},
    {   2,
            {"back","KP1","KD1","R_PWM1","L_PWM1","J_time1","C_time1","D_Time1","LorR1","turn1"}},
    {   3,
            {"back","KP2","KD2","R_PWM2","L_PWM2","J_time2","C_time2","D_Time2","LorR2","turn2"}},
    {   4,
            {"back","KP3","KD3","R_PWM3","L_PWM3","J_time3","C_time3","D_Time3","LorR3","turn3"}},
    {   5,
            {"back","PWM","Servo","S_Value","","","","",""}},
    {   6,
            {"back","LPWM","RPWM","","","","","",""}},
	{   7,
            {"back","S_add","S_J_Ti","L_add","L_J_Ti","B_slow","Slow_T","S_Vue","B_Vue"}},
};

struct Menu *Pin=&Page[0];//���ָ��

//ADC��������	                                   			
unsigned int ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0,ADC_5 = 0, ADC_6 = 0, ADC_8 = 0;  			//ADC����ֵ