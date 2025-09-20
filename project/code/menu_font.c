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
    {   0,
            {"back","PID","PWM","Time","Test","","",""}},
    {   1,
            {"back","KP","KD","KP1","KD1","KP2","KD2","KP3","KD3"}},
    {   2,
            {"back","R_PWM","L_PWM","PRO","RPWM1","LPWM2","RPWM2","LPWM2","RPWM3","LPWM3"}},
    {   3,
            {"back","M_Te","sp_e","","","","","",""}},
    {   4,
            {"back","L_M","R_M","Servo","GOP1","GOP2","GOP3","",""}},
    {   5,
            {"back","","","","","","","",""}},
    {   6,
            {"back","","","","","","","",""}},
};

struct Menu *Pin=&Page[0];//灵活指针

//ADC采样参数	                                   			
float ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0;  			//ADC采样值