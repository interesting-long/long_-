#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1  ,1   ,2  ,3  ,4  ,-1 ,10 ,-1 ,-1,72,220,50,400},
        {-1  ,28  ,0  ,6 ,6 ,12,250,30 ,0  ,65 },//GOģʽ
        {-1  ,-1  ,0  ,6.2  ,6.2,12 ,250,30 ,0  ,65},//GPO1ģʽ
        {-1  ,-1  ,0  ,27 ,27 ,6 ,280,35 ,0  ,60},//GPO2ģʽ
        {-1  ,-1  ,0  ,29 ,29 ,6 ,270,30 ,0  ,60 },//GPO3ģʽ
        {-1  ,-1  ,-1 ,840,-1 ,-1,-1 ,-1 ,-1,-1 },
		{-1  ,20  ,20 ,3  ,-1 ,-1,-1 ,-1 ,-1,-1 },
        {-1  ,1.5   ,20 ,2  ,20 ,0.5 ,8 ,-5 ,25, 40,40},//�ٶȲ��Բ���gpo1
		
		{-1  ,30  ,300 ,13  ,3.5,13 ,3.5 ,-1 ,-1,-1 },//GOpid
		{-1  ,32  ,320 ,13  ,3.5,13 ,3.5 ,-1 ,-1,-1 },//GPO1pid
		{-1  ,33  ,330 ,6  ,1,6 ,1,-1 ,-1,-1 },//GPO2pid
		{-1  ,34  ,340 ,6  ,1,6 ,1,-1 ,-1,-1 }};//GPO3pid

unsigned char Page0_children[Page_Row_Number+1]={0,1,2,3,4,7,0,0,5};//���ֽڲ˵�,�ڶ���������ת��Page[1],Page[2]��Page[3]��Page[4]��
unsigned char Page5_children[Page_Row_Number+1]={0, 6};//���ֽڲ˵�,�ڶ�����ת��Page[5],Page[6]
unsigned char Page1_children[Page_Row_Number+1]={0, 8};
unsigned char Page2_children[Page_Row_Number+1]={0, 9};
unsigned char Page3_children[Page_Row_Number+1]={0, 10};
unsigned char Page4_children[Page_Row_Number+1]={0, 11};

/*�ṹ���һ����   ���кš����������ڿ�����ʾ���ݵ��߼�(���к��Ƕ��٣�����ʾ��һ���������)
 *�ṹ��ڶ�����   ��ʾ������
 *�ṹ���������   ��ָ����(�����Զ����ã�
 *�ṹ���������   ��ָ������(λ�ö�Ӧ����)�ú�������
 */
struct Menu Page[Struct_Number]={
    {   0,
            {"back","GOP","GOP1","GOP2","GOP3","Time","Pro","ADC","Test","Valu1","ADC_F1","Valu2","ADC_F2"}},
    {   1,
            {"back","PID","Mode","R_PWM","L_PWM","J_time","C_time","D_Time","LorR","turn"}},
    {   2,
            {"back","PID","Mode","R_PWM1","L_PWM1","J_time1","C_time1","D_Time1","LorR1","turn1"}},
    {   3,
            {"back","PID","Mode","R_PWM2","L_PWM2","J_time2","C_time2","D_Time2","LorR2","turn2"}},
    {   4,
            {"back","PID","Mode","R_PWM3","L_PWM3","J_time3","C_time3","D_Time3","LorR3","turn3"}},
    {   5,
            {"back","PWM","Servo","S_Value","","","","",""}},
    {   6,
            {"back","LPWM","RPWM","","","","","",""}},
	{   7,
            {"back","S_add","S_J_Ti","L_add","L_J_Ti","B_sped","Be_J_T","L_T_B_V","L_T_B_T","S_Val","B_Val"}},
	{   8,
            {"back","S_KP","S_KD","ML_KP","ML_KI","MR_KP","MR_KI","",""}},
	{   9,
            {"back","S_KP1","S_KD1","ML_KP1","ML_KI1","MR_KP1","MR_KI1","",""}},
	{   10,
            {"back","S_KP2","S_KD2","ML_KP2","ML_KI2","MR_KP2","MR_KI2","",""}},
	{   11,
            {"back","S_KP3","S_KD3","ML_KP3","ML_KI3","MR_KP3","MR_KI3","",""}},
};

struct Menu *Pin=&Page[0];//���ָ��

//ADC��������	                                   			
unsigned int ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0,ADC_5 = 0, ADC_6 = 0, ADC_8 = 0;  			//ADC����ֵ