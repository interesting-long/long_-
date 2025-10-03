#include "menu.h"
#include <stdio.h>
unsigned char Key;//���ڽ��ܼ���ֵ
char Key3_count=0;      //��¼����Key3�Ĵ���
char Start_Show_Row=0;  //�ӽṹ�����һ�п�ʼ��ʾ
float bujin=1;          //����ֵ
char Flag=1;            //������־λ
char mode=0;            //mode=1Ϊ����ģʽ
char i,j;                 //����ѭ��
unsigned char Show_image_mode=0;
unsigned char Save_Flag=0;
//struct Menu *Pin=&Page[0];//���ָ��
/*
 * ��������Ӳ˵��ĺ���
 * ����1:��Ҫ����Page[x]�ĵ�ַ;����2:��Ӧ������������(-1ֹͣ)
 * ����   Menu_SetChildren(&Page[0],Page0_children);  ����һҳ��2��3��4�е����ֽ�����ΪPage[1],Page[2],Page[3]
 * ��ע   ȷ������ĩβΪ-1Ϊ������־λ��0��������
*/
void Menu_SetChildren(struct Menu *parent, unsigned char child_indices[])
{
    // ���ԭ���ӽڵ�
    for(i = 0; i < Page_Row_Number; i++) {
        parent->children[i] = NULL;
    }

    // �����µ��ӽڵ�
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
	for(i=0;i<max_OLED_ROW;i++)                                  //**��ʾ�߼�**
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
	if(mode==0)                                                         //MODE=0ʱ���߼�
	{
		if(Flag<Page_Row_Number)
		{
			Flag++;                                                         //���¹����߼�(Key=1)
		}
		if(Flag<=max_OLED_ROW)
		{
			tft180_show_string(Show_arrow_x,(ROW_DISTANCE+1)*(Flag-2),"   ");
		}
		else
		{
			if(Flag>max_OLED_ROW ){Start_Show_Row++;}//��Flag����oled��ʾ��������������¹�����
			if(Start_Show_Row>Page_Row_Number-max_OLED_ROW){Start_Show_Row=Page_Row_Number-max_OLED_ROW;}
			if(Flag>Page_Row_Number){Flag=Page_Row_Number;}//��ֹԽ���������
			tft180_clear(RGB565_WHITE);
			menu_display_content(); 
		}
		Refesh_arrow();
	}
	else if(mode==1)                       //����״̬�£�Key1�������Ӳ���ֵ   MODE=1ʱ���߼�
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
	if(mode==1)                         //����״̬�£�Key4���ڼ�����ֵ      MODE=1ʱ���߼�
	{
		Num[Pin->index][Flag-1]+=bujin;
		Save_Flag=1;
		menu_display_content(); 
	}
	else if(mode==0)                                                 //MODE=0ʱ���߼�
	{
		if(Flag>1)
		{
			Flag--;
		}
		if(Flag<max_OLED_ROW)                                          //���Ϲ����߼�
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
    
    // ֱ���ڰ����������д���ģʽ�л�
    switch(Key3_count)
    {
		case 1:{Key3_handle1();break;}	//�����¼���ֵΪ 3 һ�ε�ģʽ�л�������ģʽ��
		case 2:{Key3_handle2();break;}	//�����¼���ֵΪ 3 ���ε�ģʽ�л�������ģʽ��
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
	if((Pin->children[Flag-1])!=NULL)//�������ֽڡ������������������
	{
		Pin=Pin->children[Flag-1];
		Flag=1;
		Start_Show_Row=0;
		Key3_count=0;mode=0;
		show_all_menu();
	}
	else if(Pin->father!=NULL && Flag==1)//��һ�н��븸�ֽڡ������������˳�����
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
/* �������������Ʋ˵�����
 * ����1������ֵ
 * ����ֵ����
 * ���ӣ�menu_handle_key��Key����
 */
void menu_handle_key(unsigned char Flag_Key)
{

	switch(Flag_Key)
	{
		case 1:{handle_key1();break;}  //���¼���ֵΪ 1 ��������Ϊ
		case 2:{handle_key2();break;}  //���¼���ֵΪ 2 ��������Ϊ
		case 3:{handle_key3();break;}  //���¼���ֵΪ 3 ��������Ϊ
		case 4:{handle_key4();break;}  //���¼���ֵΪ 4 ��������Ϊ
		case 5:{handle_key5();break;}  //���¼���ֵΪ 5 ��������Ϊ
	}
}
/*�˵���ʼ��
�����Ӳ˵�����
����һ��ʼ��ʾ�Ļ���
*/
void menu_Init()
{
	Menu_SetChildren(&Page[0],Page0_children);//�趨���ֽ�
	Menu_SetChildren(&Page[5],Page5_children);//�趨���ֽ�
	Refesh_arrow();
	menu_display_content();
	Show_bujin();
	
}