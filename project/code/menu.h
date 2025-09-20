#ifndef __MENU_H__
#define __MENU_H__

#include "zf_common_headfile.h"
extern char Flag;            //行数标志位
extern unsigned char Key;
extern unsigned char Show_image_mode;
/******外部部调用函数*********/
void menu_handle_key(unsigned char Flag_Key);
void menu_Init();
/******内部调用函数*********/
void Menu_SetChildren(struct Menu *parent, unsigned char child_indices[]);
void Refesh_arrow();
void menu_display_content();
void handle_key1();
void handle_key2();
void handle_key3();
void handle_key4();
void Key3_handle1();
void Key3_handle2();
#endif