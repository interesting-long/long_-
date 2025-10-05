#include "menu.h"
#include <stdio.h>
unsigned char Key;//用于接受键码值
char Key3_count=0;      //记录按下Key3的次数
char Start_Show_Row=0;  //从结构体的哪一行开始显示
float bujin=1;          //步进值
char Flag=1;            //行数标志位
char mode=0;            //mode=1为锁定模式
char i,j;                 //用于循环
unsigned char Show_image_mode=0;
unsigned char Save_Flag=0;
//struct Menu *Pin=&Page[0];//灵活指针
/*
 * 快捷设置子菜单的函数
 * 参数1:需要设置Page[x]的地址;参数2:对应的索引号数组(-1停止)
 * 例子   Menu_SetChildren(&Page[0],Page0_children);  将第一页的2，3，4行的子字节设置为Page[1],Page[2],Page[3]
 * 备注   确保数组末尾为-1为结束标志位，0跳过设置
*/
void Menu_SetChildren(struct Menu *parent, unsigned char child_indices[])
{
    // 清空原有子节点
    for(i = 0; i < Page_Row_Number; i++) {
        parent->children[i] = NULL;
    }

    // 设置新的子节点
    for(i = 0; child_indices[i] != -1 && i < Page_Row_Number; i++)
    {
        if(child_indices[i] > 0 && child_indices[i] < Struct_Number)
        {
            parent->children[i] = &Page[child_indices[i]];
            parent->children[i]->father = parent;
        }

    }
}

void Refesh_arrow()
{
	if(mode==0)
	{
		if (Flag <= max_OLED_ROW)
		{
			tft180_show_string(Show_arrow_x, (ROW_DISTANCE+1)*(Flag-1), "<--");
		}
		else
		{
			tft180_show_string(Show_arrow_x, (ROW_DISTANCE+1)*(max_OLED_ROW-1), "<--");
		}
	}
	else
	{
		if (Flag <= max_OLED_ROW)
		{
			tft180_show_string(Show_arrow_x, (ROW_DISTANCE+1)*(Flag-1), "-->");
		}
		else
		{
			tft180_show_string(Show_arrow_x, (ROW_DISTANCE+1)*(max_OLED_ROW-1), "-->");
		}
	}
}

void menu_display_content() 
{
	for(i=0;i<max_OLED_ROW;i++)                                  //**显示逻辑**
	{
		tft180_show_string(Show_String_x,(ROW_DISTANCE+1)*i,Pin->page[i+Start_Show_Row]);
		if(Num[Pin->index][i+Start_Show_Row]!=-1 && Pin->children[i+Start_Show_Row]==NULL && i+Start_Show_Row!=0)
		{
			tft180_show_float(Show_Num_x,(ROW_DISTANCE+1)*i,Num[Pin->index][i+Start_Show_Row],num_float_int,num_float_decimal);
		}
	}
}
void Show_bujin()
{
		switch((int)(bujin*100))
		{
		case 1000:tft180_show_string(Show_bujin_x,0,"<10>  ");break;
		case 100:tft180_show_string(Show_bujin_x,0,"<1.0> ");break;
		case 10:tft180_show_string(Show_bujin_x,0,"<0.1> ");break;
		case 1:tft180_show_string(Show_bujin_x,0,"<0.01>");break;
		}
}

void show_all_menu()
{
	tft180_clear(RGB565_WHITE);
	Refesh_arrow();
	menu_display_content();
	Show_bujin();
}
void handle_key1()
{
	if(mode==0)                                                         //MODE=0时的逻辑
	{
		if(Flag<Page_Row_Number)
		{
			Flag++;                                                         //向下滚动逻辑(Key=1)
		}
		if(Flag<=max_OLED_ROW)
		{
			tft180_show_string(Show_arrow_x,(ROW_DISTANCE+1)*(Flag-2),"   ");
		}
		else
		{
			if(Flag>max_OLED_ROW ){Start_Show_Row++;}//当Flag大于oled显示的最大行数，向下滚动；
			if(Start_Show_Row>Page_Row_Number-max_OLED_ROW){Start_Show_Row=Page_Row_Number-max_OLED_ROW;}
			if(Flag>Page_Row_Number){Flag=Page_Row_Number;}//防止越界产生乱码
			tft180_clear(RGB565_WHITE);
			menu_display_content(); 
		}
		Refesh_arrow();
	}
	else if(mode==1)                       //锁定状态下，Key1用于增加步进值   MODE=1时的逻辑
	{
		Num[Pin->index][Flag-1]-=bujin;
		Save_Flag=1;
		menu_display_content();
		Refesh_arrow();
	}
}

void handle_key2()
{
	bujin*=10.0;
	if(bujin>10)
	{
		bujin=10;
	}
	Show_bujin();
	
}

void handle_key3()
{
	bujin/=10.0;
	if(bujin<0.01)
	{
		bujin=0.01;
	}
	Show_bujin();
}
void handle_key4()
{
	if(mode==1)                         //锁定状态下，Key4用于减步进值      MODE=1时的逻辑
	{
		Num[Pin->index][Flag-1]+=bujin;
		Save_Flag=1;
		menu_display_content(); 
	}
	else if(mode==0)                                                 //MODE=0时的逻辑
	{
		if(Flag>1)
		{
			Flag--;
		}
		if(Flag<max_OLED_ROW)                                          //向上滚动逻辑
		{
			if(Flag<0)
			{Flag=0;}
			tft180_show_string(Show_arrow_x,(ROW_DISTANCE+1)*(Flag),"   ");
		}
		else
		{
			if(Start_Show_Row>0){Start_Show_Row--;}
			tft180_clear(RGB565_WHITE);
			menu_display_content(); 
		}
		Refesh_arrow();
	}
}
void handle_key5()
{
	Key3_count++;
    
    // 直接在按键处理函数中处理模式切换
    switch(Key3_count)
    {
		case 1:{Key3_handle1();break;}	//当按下键码值为 3 一次的模式切换（调参模式）
		case 2:{Key3_handle2();break;}	//当按下键码值为 3 两次的模式切换（翻动模式）
        default: break;
    }
}
void Key3_handle1()
{
	mode=1;
	Refesh_arrow();
}
void Key3_handle2()
{
	if(Save_Flag)
	{
//		eeprom_save_Num();
		Save_Flag=0;
	}
	if((Pin->children[Flag-1])!=NULL)//进入子字节——————进入操作
	{
		Pin=Pin->children[Flag-1];
		Flag=1;
		Start_Show_Row=0;
		Key3_count=0;mode=0;
		show_all_menu();
	}
	else if(Pin->father!=NULL && Flag==1)//第一行进入父字节——————退出操作
	{
		Pin=Pin->father;
		Flag=1;
		Start_Show_Row=0;
		Key3_count=0;mode=0;
		show_all_menu();
	}
	Key3_count=0;mode=0;
	Refesh_arrow();
}
/* 函数：按键控制菜单函数
 * 参数1：键码值
 * 返回值：无
 * 例子：menu_handle_key（Key）；
 */
void menu_handle_key(unsigned char Flag_Key)
{

	switch(Flag_Key)
	{
		case 1:{handle_key1();break;}  //按下键码值为 1 按键的行为
		case 2:{handle_key2();break;}  //按下键码值为 2 按键的行为
		case 3:{handle_key3();break;}  //按下键码值为 3 按键的行为
		case 4:{handle_key4();break;}  //按下键码值为 4 按键的行为
		case 5:{handle_key5();break;}  //按下键码值为 5 按键的行为
	}
}
/*菜单初始化
设置子菜单索引
设置一开始显示的画面
*/
void menu_Init()
{
	Menu_SetChildren(&Page[0],Page0_children);//设定子字节
	Menu_SetChildren(&Page[5],Page5_children);//设定子字节
	Refesh_arrow();
	menu_display_content();
	Show_bujin();
	
}