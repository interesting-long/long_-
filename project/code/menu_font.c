#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1  ,1   ,2  ,3  ,4  ,-1,5  ,-1 ,-1,-1},
        {-1  ,28  ,280,32 ,32 ,6 ,400,30 ,5 ,60 },
        {-1  ,30  ,300,35 ,35 ,6 ,310,20 ,5 ,60},
        {-1  ,31  ,310,37 ,37 ,6 ,280,15 ,5 ,60},
        {-1  ,32.5,325,39 ,39 ,6 ,250,10 ,5 ,60 },
        {-1  ,-1  ,-1 ,840,-1 ,-1,-1 ,-1 ,-1,-1 },
		{-1  ,20  ,20 ,3  ,-1 ,-1,-1 ,-1 ,-1,-1 },
        {-1  ,1  ,5 ,2 ,16 ,-30,10 ,15 ,40, }};//数据存储的数组

unsigned char Page0_children[Page_Row_Number+1]={0,1,2,3,4,7,0,0,5};//子字节菜单,第二三四五行转到Page[1],Page[2]，Page[3]，Page[4]，
unsigned char Page5_children[Page_Row_Number+1]={0, 6};//子字节菜单,第二三行转到Page[5],Page[6]


/*结构体第一行是   序列号————用于控制显示数据的逻辑(序列号是多少，就显示哪一数组的数据)
 *结构体第二行是   显示的数据
 *结构体第三行是   父指针用(函数自动配置）
 *结构体第四行是   子指针数组(位置对应行数)用函数配置
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

struct Menu *Pin=&Page[0];//灵活指针

//ADC采样参数	                                   			
unsigned int ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0,ADC_5 = 0, ADC_6 = 0, ADC_8 = 0;  			//ADC采样值