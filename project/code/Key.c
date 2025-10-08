#include "Key.h"

int Press_time=0;
int Trigg_time=0;
unsigned char keynumber=0;
unsigned char last_keynumber=0;
unsigned char State=0;
unsigned char Key_count=0;
unsigned Time_dou=0;
unsigned char Init_Flag=0;

struct PageModeMap
{
    unsigned char page_index;
	unsigned char item_index;
	MODE Mod;
};

const struct PageModeMap mode_map[] = {
    {0, 2, GO}, {0, 3, GO_Pararm1}, {0, 4, GO_Pararm2}, {0, 5, GO_Pararm3}, {0, 8, ADC_Show},
    {5, 3, TEST_SERVO}, {5, 4, Seta_Servo},
    {6, ANY_ITEM, TEST_PWM},  // 第6页任意项都切换到TEST_PWM
    {1, ANY_ITEM, GO}, {2, ANY_ITEM, GO_Pararm1}, {3, ANY_ITEM, GO_Pararm2}, {4, ANY_ITEM, GO_Pararm3}
};

unsigned char Key_Number(void)
{
    unsigned char KeyNumber=0;

//    if(gpio_get_level(IO_P26)==0){KeyNumber=1;}//下
//    if(gpio_get_level(IO_P07)==0){KeyNumber=2;}//右
//    if(gpio_get_level(IO_P45)==0){KeyNumber=3;}//左
//    if(gpio_get_level(IO_P46)==0){KeyNumber=4;}//上
	
//	if(gpio_get_level(IO_P45)==0){KeyNumber=1;}//下
//    if(gpio_get_level(IO_P26)==0){KeyNumber=2;}//右
//    if(gpio_get_level(IO_P46)==0){KeyNumber=3;}//左
//    if(gpio_get_level(IO_P07)==0){KeyNumber=4;}//上
//	if(gpio_get_level(IO_P52)==0){KeyNumber=5;}//中46,45,07
	
	
	if(gpio_get_level(IO_P26)==0){KeyNumber=1;}//下
    if(gpio_get_level(IO_P33)==0){KeyNumber=2;}//右
    if(gpio_get_level(IO_P53)==0){KeyNumber=3;}//左
    if(gpio_get_level(IO_P46)==0){KeyNumber=4;}//上
	if(gpio_get_level(IO_P07)==0){KeyNumber=5;}//中46,45,07
    return KeyNumber;
}
void Turn_mode(void)
{
	int i;
    for(i = 0; i < sizeof(mode_map)/sizeof(mode_map[0]); i++) {
        // 检查页面匹配
        if((void *)Pin == (void *)&Page[mode_map[i].page_index]) {
            // 如果是任意项匹配 或 具体项匹配
            if(mode_map[i].item_index == ANY_ITEM || Flag == mode_map[i].item_index) {
                CAR_Mode = (CAR_Mode == mode_map[i].Mod) ? STOP : mode_map[i].Mod;
                Init_Flag = 1;
                return;
            }
        }
    }
}
void Key_scaner(void)
{
	keynumber=Key_Number();
	switch(State)
	{
		case State_Release:
		{
			if(keynumber!=0)
			{
				State=State_Press_dou;
				Key_count=0;
			}
			break;
		}
		case State_Press_dou:
		{
			if(keynumber==0)
			{
				State=State_Release;
			}
			else
			{
				Key_count++;
				if(Key_count>=Time_dou)
				{
					State=State_Press;
					last_keynumber=keynumber;
//					Key=keynumber;
				}
			}
			break;
		}
		case State_Press:
		{
			if(keynumber==0)
			{
//				Key=last_keynumber;
				State=State_Release_dou;
				Key_count=0;
				Press_time=0;
			}
			else
			{
				Press_time++;
				if(Press_time>Flag_press_time)
				{
					Trigg_time++;
					if(keynumber==5)//长按触发的操作
					{
						Turn_mode();
						Init_Flag=1;
						Press_time=0;
						last_keynumber=0;
					}
					else if(Trigg_time>Flag_trigg_time)
					{
						Trigg_time=0;
						Key=keynumber;
						//多次触发的操作
					}
				}
			}
			break;
		}
		case State_Release_dou:
		{
			if(keynumber==0)
			{
				Key_count++;
				if(Key_count>=Time_dou)
				{
					State=State_Release;
					Key=last_keynumber;  // 松开时清零
				}
			}
			else
			{
				State=State_Press;
			}
			break;
		}
	}
}
