#include "menu_font.h"
float Num[Num_Col][Page_Row_Number]={
        {-1  ,1   ,2   ,3  ,4 ,-1 ,5 ,-1 ,-1,85,220},
        {-1  ,28  ,5,27,27 ,12,310,45 ,0  ,65 },
        {-1  ,30  ,5,0 ,0  ,6 ,320,40 ,0  ,60},
        {-1  ,31  ,5,21,21 ,6 ,280,35 ,0  ,60},
        {-1  ,32.5,5,27,27 ,6 ,270,30 ,0  ,60 },
        {-1  ,-1  ,-1  ,840,-1 ,-1,-1 ,-1 ,-1,-1 },
		{-1  ,20  ,20  ,3  ,-1 ,-1,-1 ,-1 ,-1,-1 },
        {-1  ,3   ,10  ,5  ,20 ,0 ,10 ,15 ,40, },
		
		{-1  ,33  ,330 ,5  ,1,5 ,1 ,-1 ,-1,-1 },
		{-1  ,30  ,300 ,0.5,0.5,0.5,0.5,-1 ,-1,-1 },
		{-1  ,310 ,310 ,0.5,0.5,0.5,0.5,-1 ,-1,-1 },
		{-1  ,34,3400 ,5,1,5,1,-1 ,-1,-1 }};//数据存储的数组

unsigned char Page0_children[Page_Row_Number+1]={0,1,2,3,4,7,0,0,5};//子字节菜单,第二三四五行转到Page[1],Page[2]，Page[3]，Page[4]，
unsigned char Page5_children[Page_Row_Number+1]={0, 6};//子字节菜单,第二三行转到Page[5],Page[6]
unsigned char Page1_children[Page_Row_Number+1]={0, 8};
unsigned char Page2_children[Page_Row_Number+1]={0, 9};
unsigned char Page3_children[Page_Row_Number+1]={0, 10};
unsigned char Page4_children[Page_Row_Number+1]={0, 11};

/*结构体第一行是   序列号————用于控制显示数据的逻辑(序列号是多少，就显示哪一数组的数据)
 *结构体第二行是   显示的数据
 *结构体第三行是   父指针用(函数自动配置）
 *结构体第四行是   子指针数组(位置对应行数)用函数配置
 */
struct Menu Page[Struct_Number]={
    {   0,
            {"back","GOP","GOP1","GOP2","GOP3","Time","Pro","ADC","Test","Value","ADC_F"}},
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
            {"back","S_add","S_J_Ti","L_add","L_J_Ti","B_slow","Not_T","S_Vue","B_Vue"}},
	{   8,
            {"back","S_KP","S_KD","ML_KP","ML_KI","MR_KP","MR_KI","",""}},
	{   9,
            {"back","S_KP1","S_KD1","ML_KP1","ML_KI1","MR_KP1","MR_KI1","",""}},
	{   10,
            {"back","S_KP2","S_KD2","ML_KP2","ML_KI2","MR_KP2","MR_KI2","",""}},
	{   11,
            {"back","S_KP3","S_KD3","ML_KP3","ML_KI3","MR_KP3","MR_KI3","",""}},
};

struct Menu *Pin=&Page[0];//灵活指针

//ADC采样参数	                                   			
unsigned int ADC_1 = 0, ADC_2 = 0, ADC_3 = 0, ADC_4 = 0,ADC_5 = 0, ADC_6 = 0, ADC_8 = 0;  			//ADC采样值