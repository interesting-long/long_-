#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1 ,1 ,2 ,3 ,4  ,-1 ,-1 ,-1 ,-1 },
        {-1 ,20,20,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,50,50 ,0.8,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 }};//���ݴ洢������

unsigned char Page0_children[Page_Row_Number+1]={0,1, 2,3,4};//���ֽڲ˵�,�ڶ���������ת��Page[1],Page[2]��Page[3]��Page[4]��
unsigned char Page1_children[Page_Row_Number+1]={0, 5, 6};//���ֽڲ˵�,�ڶ�����ת��Page[5],Page[6]


/*�ṹ���һ����   ���кš����������ڿ�����ʾ���ݵ��߼�(���к��Ƕ��٣�����ʾ��һ���������)
 *�ṹ��ڶ�����   ��ʾ������
 *�ṹ���������   ��ָ����(�����Զ����ã�
 *�ṹ���������   ��ָ������(λ�ö�Ӧ����)�ú�������
 */
struct Menu Page[Struct_Number]={
    {   2,
            {"back","PID","PWM","Time","di_a","Prot","duqu",""}},
    {   0,
            {"back","Max_K","Max_K","Min_K","Min_K","ser_y","","",""}},
    {   1,
            {"back","R_PWM","L_PWM","","","","","",""}},
    {   3,
            {"back","M_Te","sp_e","Slowe","long","lvv_","Kai","",""}},
    {   4,
            {"back","diyu","dikp","sper","s_add","","","",""}},
    {   5,
            {"back","2-5","hallo","hallo","hallo","hallo","hallo","hallo","hallo"}},
    {   6,
            {"back","e2-5","hallo","hallo","hallo","hallo","hallo","hallo","hallo"}},
};

struct Menu *Pin=&Page[0];//���ָ��

//ADC��������	                                   			
float ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0;  			//ADC����ֵ