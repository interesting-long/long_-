#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1 ,1 ,2 ,3 ,4  ,-1 ,-1 ,-1 ,-1 },
        {-1 ,20,20,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,50,50 ,0.8,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 },
        {-1 ,1 ,2 ,3 ,-1 ,-1 ,-1 ,-1 ,-1 }};//数据存储的数组

unsigned char Page0_children[Page_Row_Number+1]={0,1, 2,3,4};//子字节菜单,第二三四五行转到Page[1],Page[2]，Page[3]，Page[4]，
unsigned char Page1_children[Page_Row_Number+1]={0, 5, 6};//子字节菜单,第二三行转到Page[5],Page[6]


/*结构体第一行是   序列号————用于控制显示数据的逻辑(序列号是多少，就显示哪一数组的数据)
 *结构体第二行是   显示的数据
 *结构体第三行是   父指针用(函数自动配置）
 *结构体第四行是   子指针数组(位置对应行数)用函数配置
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

struct Menu *Pin=&Page[0];//灵活指针

//ADC采样参数	                                   			
float ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0;  			//ADC采样值