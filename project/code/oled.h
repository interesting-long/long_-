#ifndef __OLED_H
#define __OLED_H 	 
#include "zf_common_headfile.h"
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define OLED_SCL IO_P27//SCL
#define OLED_SDA IO_P25//SDA
#define OLED_RES  IO_P20//RES
#define OLED_DC  IO_P21//DC
#define OLED_CS IO_P22 //CS

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() gpio_set_level(OLED_SCL,0)
#define OLED_SCL_Set() gpio_set_level(OLED_SCL,1)

#define OLED_SDA_Clr() gpio_set_level(OLED_SDA,0)
#define OLED_SDA_Set() gpio_set_level(OLED_SDA,1)

#define OLED_RES_Clr() gpio_set_level(OLED_RES,0)
#define OLED_RES_Set() gpio_set_level(OLED_RES,1)

#define OLED_DC_Clr() gpio_set_level(OLED_DC,0)
#define OLED_DC_Set() gpio_set_level(OLED_DC,1)

#define OLED_CS_Clr()  gpio_set_level(OLED_CS,0)
#define OLED_CS_Set()  gpio_set_level(OLED_CS,1)


//OLED控制用函数
void delay_ms(unsigned int ms);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
/*void OLED_Display_On(void);
void OLED_Display_Off(void);*/
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey,unsigned char facial);
/*u32 oled_pow(u8 m,u8 n);*/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey,unsigned char facial);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey,unsigned char facial);
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey,unsigned char facial);
void OLED_Init(void);

#endif  
	 



