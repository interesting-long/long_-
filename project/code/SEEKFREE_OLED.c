/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		OLED
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					���߶��壺
					------------------------------------ 
					OLEDҺ��    ��Ƭ��                        
					D0          �鿴SEEKFREE_OLED.h�ļ��ڵ�OLED_SCL_PIN   �궨��
					D1          �鿴SEEKFREE_OLED.h�ļ��ڵ�OLED_SDA_PIN   �궨��            
					RES         �鿴SEEKFREE_OLED.h�ļ��ڵ�OLED_RST_PIN   �궨��    
					DC          �鿴SEEKFREE_OLED.h�ļ��ڵ�OLED_DC_PIN    �궨��
					CS          �鿴SEEKFREE_OLED.h�ļ��ڵ�OLED_CS_PIN    �궨��
					------------------------------------ 
 ********************************************************************************************************************/

#include "zf_spi.h"
#include "zf_delay.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_PRINTF.h"
#include "SEEKFREE_OLED.h"

//-------------------------------------------------------------------------------------------------------------------
//  ���º�����ʹ�����SPIͨ�ţ���Ƚ�Ӳ��SPI�����SPI���Ÿ���������ʹ��������ͨIO
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_wrdat(uint8 dat)
{
	uint8 edata i=8;
	
//    OLED_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
	OLED_DC(1);
	OLED_SCL(0);
	while(i--)
	{
	  	if(dat&0x80){OLED_SDA(1);}
	  	else{OLED_SDA(0);}
	  	OLED_SCL(1);
		
	  	OLED_SCL(0);
	  	dat<<=1;
	}
    //OLED_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
//void oled_wr6dat(uint8 dat)
//{
//	uint8 edata i=6;
//    
//	OLED_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
//	OLED_DC(1);
//	OLED_SCL(0);
//	while(i--)
//	{
//	 	if(dat&0x80){OLED_SDA(1);}
//	 	else{OLED_SDA(0);}
//	 	OLED_SCL(1);
//	 	OLED_SCL(0);
//	 	dat<<=1;
//	}
//    OLED_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_wrcmd(uint8 cmd)
{
	uint8 edata i=8;
    
	//OLED_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
	OLED_DC(0);
	OLED_SCL(0);;
	
	while(i--)
	{
		if(cmd&0x80){OLED_SDA(1);}
		else{OLED_SDA(0);}
		OLED_SCL(1);
		
		OLED_SCL(0);
		cmd<<=1;
	}
    //OLED_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_hexascii(uint16 hex,int8 * Print)
{
	uint8 edata hexcheck ;
	uint8 edata TEMP ;
	TEMP = 6 ;
	Print[TEMP ]='\0';
	while(TEMP)
	{
	  	TEMP -- ;
	  	hexcheck  =  hex%10 ;
	  	hex   /=10 ;
	  	Print[TEMP ]  = hexcheck + 0x30 ;
	}
  
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʼ������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_init(void)
{
	
//    OLED_CS(1);
	OLED_SCL(1);
	
	OLED_RST(0);
	delay_ms(50);
	OLED_RST(1);
	
	oled_wrcmd(0xae);//--turn off oled panel
	oled_wrcmd(0x00);//---set low column address
	oled_wrcmd(0x10);//---set high column address
	oled_wrcmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	oled_wrcmd(0x81);//--set contrast control register
	oled_wrcmd(Brightness); // Set SEG Output Current Brightness
    
#if (0 == OLED_DISPLAY_DIR)
	oled_wrcmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	oled_wrcmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
#else
    oled_wrcmd(0xa0);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	oled_wrcmd(0xc0);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
#endif
    
	oled_wrcmd(0xa6);//--set normal display
	oled_wrcmd(0xa8);//--set multiplex ratio(1 to 64)
	oled_wrcmd(0x3f);//--1/64 duty
	oled_wrcmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	oled_wrcmd(0x00);//-not offset
	oled_wrcmd(0xd5);//--set display clock divide ratio/oscillator frequency
	oled_wrcmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	oled_wrcmd(0xd9);//--set pre-charge period
	oled_wrcmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_wrcmd(0xda);//--set com pins hardware configuration
	oled_wrcmd(0x12);
	oled_wrcmd(0xdb);//--set vcomh
	oled_wrcmd(0x40);//Set VCOM Deselect Level
	oled_wrcmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	oled_wrcmd(0x02);//
	oled_wrcmd(0x8d);//--set Charge Pump enable/disable
	oled_wrcmd(0x14);//--set(0x10) disable
	oled_wrcmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	oled_wrcmd(0xa6);// Disable Inverse Display On (0xa6/a7)
	oled_wrcmd(0xaf);//--turn on oled panel
	oled_fill(0x00);  //��ʼ����
	oled_set_pos(0,0);
	
}

// ������SPI�Ļ�������������
void oled_clear_buffer_soft(void) {
    uint8 page, col;
    for(page = 0; page < 8; page++) {
        for(col = 0; col < 128; col++) {
            oled_buffer[page][col] = 0x00;
        }
    }
}

void oled_update_soft(void) {
    uint8 page, col;
    for(page = 0; page < 8; page++) {
        oled_set_pos(0, page);  // ʹ�����SPI������λ�ú���
        for(col = 0; col < 128; col++) {
            oled_wrdat(oled_buffer[page][col]);  // ʹ�����SPI��д���ݺ���
        }
    }
}

void oled_clear_buffer_line_soft(uint8 page) {
		uint8 col;
    if(page >= 8) return;
    for(col = 0; col < 128; col++) {
        oled_buffer[page][col] = 0x00;
    }
}

void oled_update_line_soft(uint8 page) {
		uint8 col;
    if(page >= 8) return;
    oled_set_pos(0, page);
    for(col = 0; col < 128; col++) {
        oled_wrdat(oled_buffer[page][col]);
    }
}

void oled_reverse_buffer_soft(void) {
    uint8 page, col;
    for(page = 0; page < 8; page++) {
        for(col = 0; col < 128; col++) {
            oled_buffer[page][col] ^= 0xFF;
        }
    }
}

void oled_reverse_buffer_line_soft(uint8 page) {
		uint8 col;
    if(page >= 8) return;
    for(col = 0; col < 128; col++) {
        oled_buffer[page][col] ^= 0xFF;
    }
}

void oled_reverse_line_immediate_soft(uint8 page) {
		uint8 col;
    if(page >= 8) return;
    
    // ���Ի�����
    for(col = 0; col < 128; col++) {
        oled_buffer[page][col] ^= 0xFF;
    }
    
    // ����ˢ�¸���
    oled_set_pos(0, page);
    for(col = 0; col < 128; col++) {
        oled_wrdat(oled_buffer[page][col]);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ��������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_set_pos(uint8 x, uint8 y)
{
    oled_wrcmd((uint8)(0xb0+y));
    oled_wrcmd((uint8)(((x&0xf0)>>4)|0x10));
    oled_wrcmd((uint8)((x&0x0f)|0x00));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��������
//  @param      bmp_data	�����ɫѡ��(0x00 or 0xff)
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
// �޸����SPI����亯����ʹ�����������
void oled_fill(uint8 bmp_data) {
    uint8 y, x;
    for(y = 0; y < 8; y++) {
        for(x = 0; x < 128; x++) {
            oled_buffer[y][x] = bmp_data;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED����һ��������8�����صĵ�����Ϩ��
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			oled_putpixel(0,0,0xff);//��0,0���� 8����ȫ������
//  Sample usage:			oled_putpixel(0,0,0x01);//��0,0���� ���λ��������7��Ϩ��
//  @note                   ͬ������������һ��������8�����صĵ�����Ϩ��
//-------------------------------------------------------------------------------------------------------------------
// �޸����SPI�����ز���������ʹ�����������
void oled_putpixel(uint8 x, uint8 y, uint8 data1) {
    if(y < 8 && x < 128) {
        oled_buffer[y][x] = data1;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED�ر�һ��������������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_clrpixel(uint8 x, uint8 y) {
    if(y < 8 && x < 128) {
        oled_buffer[y][x] = 0x00;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�ַ���(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      ch[]        �ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
// �޸����SPI����ʾ������ʹ�����������
void oled_p6x8str(uint8 x, uint8 y, const int8 ch[]) {
    uint8 c, i, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if(x > 126) {
            x = 0;
            y++;
        }
        // ֱ�Ӳ���������
        for(i = 0; i < 6; i++) {
            if(y < 8 && x < 128) {
                oled_buffer[y][x] = oled_6x8[c][i];
            }
            x++;
        }
        j++;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�޷�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �޷�����
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_uint16(uint8 x, uint8 y, uint16 num)
{
	int8 ch[7];
	
	oled_hexascii(num,ch);
    
    oled_p6x8str(x, y, &ch[1]);	    //��ʾ����  6*8����
    //oled_p8x16str(x, y, &ch[1]);	//��ʾ����  8*16����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�з�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �з�����
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_int16(uint8 x, uint8 y, int16 num)
{
	int8 ch[7];
	if(num<0)   {num = -num;oled_p6x8str(x, y, "-");}
	else         oled_p6x8str(x, y, " ");
	x+=6;       
    
	oled_hexascii(num,ch);
    oled_p6x8str(x, y, &ch[1]);	    //��ʾ����  6*8����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ32λ�з���(ȥ������������Ч��0)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      dat       	��Ҫ��ʾ�ı�������������uint32
//  @param      num       	��Ҫ��ʾ��λ�� ���10λ  ������������
//  @return     void
//  @since      v1.0
//  Sample usage:           oled_printf_int32(0,0,x,5);//x����Ϊint32 uint16 int16 uint8 int8����
//  Sample usage:           ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_int32(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//����
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';
    
    oled_p6x8str((uint8)x, (uint8)y, (int *)buff);	//��ʾ����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ������(ȥ������������Ч��0)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      dat       	��Ҫ��ʾ�ı�������������float��double
//  @param      num         ����λ��ʾ����   ���10λ  
//  @param      pointnum    С��λ��ʾ����   ���6λ
//  @return     void
//  @since      v1.0
//  Sample usage:           oled_printf_float(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
//  @note                   �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//                          ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//                          �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//                          ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_float(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
		char buffer[20] = {0};  // ��ʾ������
    int index = 0;          // ����������
		long integer_part;
		double decimal_part;
		unsigned long multiplier;
		int i,j;
		unsigned long decimal_int;
    char int_buf[12] = {0};
    int int_len = 0;
		long temp;
		int leading_spaces;
		unsigned int divisor,digit;
		
    // �����߽���
    if (pointnum > 6) pointnum = 6;
    if (num > 10) num = 10;
    
    // �����������datΪ0
    if (dat == 0) {
        dat = 0.0; // ȷ����ֵ����
    }
    
    // �������λ
    if (dat < 0) {
        buffer[index++] = '-';
        dat = -dat;  // ת��Ϊ��������
    } else {
        buffer[index++] = ' ';  // ������ʾ�ո�
    }
    
    // ����������С������
    integer_part = (long)dat;
    decimal_part = dat - integer_part;
    
    // ����С�����ֽ�λ
    multiplier = 1;
    for (i = 0; i < pointnum; i++) multiplier *= 10;
    
    decimal_int = (unsigned long)(decimal_part * multiplier + 0.5);
    
    // ����С����λ������
    if (decimal_int >= multiplier) {
        integer_part++;
        decimal_int = 0; // ��λ��С�����ֹ���
    }
    
    // ת����������

    temp = integer_part;
    
    // ������������Ϊ0�����
    if (temp == 0) {
        int_buf[int_len++] = '0';
    } else {
        // ��ȡ����λ���֣�����
        while (temp > 0) {
            int_buf[int_len++] = (temp % 10) + '0';
            temp /= 10;
        }
    }
    
    // === ��Ҫ�޸�1�������ո�������������� ===
    leading_spaces = num - int_len;
    if (leading_spaces > 0) {
        for (i = 0; i < leading_spaces; i++) {
            buffer[index++] = ' ';
        }
    }
    
    // ��ת���������ַ���������ת����
    for (i = int_len - 1; i >= 0; i--) {
        buffer[index++] = int_buf[i];
    }
    
    // ����С������
    if (pointnum > 0) {
        buffer[index++] = '.';  // С����
        
        // === ��Ҫ�޸�2������ʹ����������������ģ���� ===
        for (i = pointnum - 1; i >= 0; i--) {
            divisor = 1;
            for (j = 0; j < i; j++) divisor *= 10;
            digit = (decimal_int / divisor) % 10;
            buffer[index++] = digit + '0';
        }
    }
    
    buffer[index] = '\0';  // �ַ���������
    
    oled_p6x8str((uint8)x, (uint8)y, (int8 *)buffer);	//��ʾ����
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾͼ��
//  @param      high  		ͼ��߶�
//  @param      width 		ͼ����
//  @param      *p    		ͼ���ַ�����飩
//  @param      value 		��ֵ����ֵ
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       ʹ��Image2lcd V3.2���ȡģ   C��������   ˮƽɨ��   
//              ��ȸ߶���������   ��ɫ��ת  256ɫ
//-------------------------------------------------------------------------------------------------------------------
// ������SPI��λͼ��ʾ������������������
void oled_dis_bmp(uint16 high, uint16 width, uint8 *p, uint8 value) {
    uint16 i, j;
    uint16 temp, temp1;
    uint8 dat;
    
    temp1 = high % 8;
    if(temp1 == 0) temp = high / 8;
    else temp = high / 8 + 1;

    for(i = 0; i < temp; i++) {
        for(j = 0; j < width; j++) {
            dat = 0;
            if(i < (temp - 1) || !temp1 || temp1 >= 1) dat |= (p[i * 8 * width + j + width * 0] > value ? 1 : 0) << 0;
            if(i < (temp - 1) || !temp1 || temp1 >= 2) dat |= (p[i * 8 * width + j + width * 1] > value ? 1 : 0) << 1;
            if(i < (temp - 1) || !temp1 || temp1 >= 3) dat |= (p[i * 8 * width + j + width * 2] > value ? 1 : 0) << 2;
            if(i < (temp - 1) || !temp1 || temp1 >= 4) dat |= (p[i * 8 * width + j + width * 3] > value ? 1 : 0) << 3;
            if(i < (temp - 1) || !temp1 || temp1 >= 5) dat |= (p[i * 8 * width + j + width * 4] > value ? 1 : 0) << 4;
            if(i < (temp - 1) || !temp1 || temp1 >= 6) dat |= (p[i * 8 * width + j + width * 5] > value ? 1 : 0) << 5;
            if(i < (temp - 1) || !temp1 || temp1 >= 7) dat |= (p[i * 8 * width + j + width * 6] > value ? 1 : 0) << 6;
            if(i < (temp - 1) || !temp1 || temp1 >= 8) dat |= (p[i * 8 * width + j + width * 7] > value ? 1 : 0) << 7;
            
            if(i < 8 && j < 128) {
                oled_buffer[i][j] = dat;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʾ
//  @param      x       ������ 0-127
//  @param      y       ������ 0-7
//  @param      size    ȡģ��ʱ�����õĺ��������С��Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��㣬ȡģ��ʱ����Ҫ������һ���ġ�
//  @param      *p      ��Ҫ��ʾ�ĺ�������
//  @param      len     ��Ҫ��ʾ����λ
//  @return     void
//  @since      v1.0
//  Sample usage:		
//  @Note       ʹ��PCtoLCD2002���ȡģ		    ���롢����ʽ��˳��   16*16
//-------------------------------------------------------------------------------------------------------------------
void oled_print_chinese(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len)
{
    uint16 i,j,k;
    
    for(i=0; i<len; i++)
    {
        for(j=0; j<(size/8); j++)
        {
            oled_set_pos((uint8)(x+i*size), (uint8)(y+j));
            for(k=0; k<16; k++)
            {
                oled_wrdat(*p);
                p++;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  ���º�����ʹ��Ӳ��SPIͨ�ţ���Ƚ����IIC���ٶȱ����IIC�졣
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_wrdat_spi(uint8 dat)
{
    OLED_SPI_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
	OLED_SPI_DC(1);
	spi_mosi(dat);
    OLED_SPI_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��

	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
//void oled_wr6dat_spi(uint8 dat)
//{
//	uint8 edata i=6;
//    
//	OLED_SPI_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
//	OLED_SPI_DC(1);
//	OLED_SCL(0);
//	while(i--)
//	{
//	 	if(dat&0x80){OLED_SDA(1);}
//	 	else{OLED_SDA(0);}
//	 	OLED_SCL(1);
//	 	OLED_SCL(0);
//	 	dat<<=1;
//	}
//    OLED_SPI_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_wrcmd_spi(uint8 cmd)
{
	OLED_SPI_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
	OLED_SPI_DC(0);
	spi_mosi(cmd);
    OLED_SPI_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void oled_hexascii_spi(uint16 hex,int8 * Print)
{
	uint8 edata hexcheck ;
	uint8 edata TEMP ;
	TEMP = 6 ;
	Print[TEMP ]='\0';
	while(TEMP)
	{
	  	TEMP -- ;
	  	hexcheck  =  hex%10 ;
	  	hex   /=10 ;
	  	Print[TEMP ]  = hexcheck + 0x30 ;
	}
  
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʼ������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_init_spi(void)
{
	
    OLED_SPI_CS(1);
	
    spi_init(OLED_SPI_N, OLED_SPI_SCLK_PIN, OLED_SPI_MOSI_PIN, OLED_SPI_MISO_PIN, 0, MASTER, SPI_SYSclk_DIV_4);
	
	OLED_SPI_RST(0);
	delay_ms(50);
	OLED_SPI_RST(1);
	
	oled_wrcmd_spi(0xae);//--turn off oled panel
	oled_wrcmd_spi(0x00);//---set low column address
	oled_wrcmd_spi(0x10);//---set high column address
	oled_wrcmd_spi(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	oled_wrcmd_spi(0x81);//--set contrast control register
	oled_wrcmd_spi(Brightness); // Set SEG Output Current Brightness
    
#if (0 == OLED_DISPLAY_DIR)
	oled_wrcmd_spi(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	oled_wrcmd_spi(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
#else
    oled_wrcmd_spi(0xa0);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	oled_wrcmd_spi(0xc0);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
#endif
    
	oled_wrcmd_spi(0xa6);//--set normal display
	oled_wrcmd_spi(0xa8);//--set multiplex ratio(1 to 64)
	oled_wrcmd_spi(0x3f);//--1/64 duty
	oled_wrcmd_spi(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	oled_wrcmd_spi(0x00);//-not offset
	oled_wrcmd_spi(0xd5);//--set display clock divide ratio/oscillator frequency
	oled_wrcmd_spi(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	oled_wrcmd_spi(0xd9);//--set pre-charge period
	oled_wrcmd_spi(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_wrcmd_spi(0xda);//--set com pins hardware configuration
	oled_wrcmd_spi(0x12);
	oled_wrcmd_spi(0xdb);//--set vcomh
	oled_wrcmd_spi(0x40);//Set VCOM Deselect Level
	oled_wrcmd_spi(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	oled_wrcmd_spi(0x02);//
	oled_wrcmd_spi(0x8d);//--set Charge Pump enable/disable
	oled_wrcmd_spi(0x14);//--set(0x10) disable
	oled_wrcmd_spi(0xa4);// Disable Entire Display On (0xa4/0xa5)
	oled_wrcmd_spi(0xa6);// Disable Inverse Display On (0xa6/a7)
	oled_wrcmd_spi(0xaf);//--turn on oled panel
	oled_fill_spi(0x00);  //��ʼ����
	oled_set_pos_spi(0,0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ��������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_set_pos_spi(uint8 x, uint8 y)
{

    
    oled_wrcmd_spi((uint8)(0xb0+y));
    oled_wrcmd_spi(((x&0xf0)>>4)|0x10);
    oled_wrcmd_spi((x&0x0f)|0x00);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��������
//  @param      bmp_data	�����ɫѡ��(0x00 or 0xff)
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_fill_spi(uint8 bmp_data)
{
	uint8 edata y,x;
	
	for(y=0;y<8;y++)
	{
		oled_wrcmd_spi((uint8)(0xb0+y));
		oled_wrcmd_spi(0x01);
		oled_wrcmd_spi(0x10);
		for(x=0;x<X_WIDTH;x++)	oled_wrdat_spi(bmp_data); 
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED����һ��������8�����صĵ�����Ϩ��
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			oled_putpixel(0,0,0xff);//��0,0���� 8����ȫ������
//  Sample usage:			oled_putpixel(0,0,0x01);//��0,0���� ���λ��������7��Ϩ��
//  @note                   ͬ������������һ��������8�����صĵ�����Ϩ��
//-------------------------------------------------------------------------------------------------------------------
void oled_putpixel_spi(uint8 x,uint8 y,uint8 data1)
{
	oled_set_pos_spi(x,y);
    oled_wrcmd_spi((uint8)(0xb0+y));
	oled_wrcmd_spi(((x&0xf0)>>4)|0x10);
	oled_wrcmd_spi((x&0x0f)|0x00);
	oled_wrdat_spi(data1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED�ر�һ��������������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_clrpixel_spi(uint8 x,uint8 y)
{
	oled_set_pos_spi(x,y);
    oled_wrcmd_spi((uint8)(0xb0+y));
	oled_wrcmd_spi(((x&0xf0)>>4)|0x10);
	oled_wrcmd_spi((x&0x0f)|0x00);
	oled_wrdat_spi(0x00);
}

// ��SEEKFREE_OLED.c�ļ��������
uint8 oled_buffer[8][128] = {0};  // OLED��ʾ������ (8ҳ x 128��)

// �����ʾ������
void oled_clear_buffer(void) {
    uint8 page, col;
    for(page = 0; page < 8; page++) {
        for(col = 0; col < 128; col++) {
            oled_buffer[page][col] = 0x00;
        }
    }
}

// �����������ݸ��µ���Ļ
void oled_update_spi(void) {
    uint8 page, col;
    for(page = 0; page < 8; page++) {
        oled_set_pos_spi(0, page);
        for(col = 0; col < 128; col++) {
            oled_wrdat_spi(oled_buffer[page][col]);
        }
    }
}

// �����ʾ��������ָ���У�ҳ��
void oled_clear_buffer_line(uint8 page) {
		 uint8 col;
    if(page >= 8) return;  // ��ֹԽ�����
    
   
    for(col = 0; col < 128; col++) {
        oled_buffer[page][col] = 0x00;
    }
}

// ����������ָ���У�ҳ�����ݸ��µ���Ļ
void oled_update_line_spi(uint8 page) {
		uint8 col;
    if(page >= 8) return;  // ��ֹԽ�����
    
    oled_set_pos_spi(0, page);
    
    for(col = 0; col < 128; col++) {
        oled_wrdat_spi(oled_buffer[page][col]);
    }
}

/**
  * @brief      ������OLED����������ȡ�������ԣ�
  * @param      none
  * @return     none
  * @note       ���ô˺�������Ҫ����oled_update()��oled_update_line_spi()����������ʾ����Ļ��
  */
void oled_reverse_buffer(void)
{
    uint8 page, col;
    for(page = 0; page < 8; page++) {         // ��������ҳ���У�
        for(col = 0; col < 128; col++) {       // ����������
            oled_buffer[page][col] ^= 0xFF;   // ��λȡ�������ԣ�
        }
    }
}

/**
  * @brief      ��OLED������ָ��������ȡ�������ԣ�
  * @param      page  Ҫ���Ե���������0-7��
  * @return     none
  * @note       ���ô˺�������Ҫ����oled_update_line_spi(page)����������ʾ����Ļ��
  */
void oled_reverse_buffer_line(uint8 page)
{
		    uint8 col;
    if(page >= 8) return;  // ��ֹԽ�����
    

    for(col = 0; col < 128; col++) {           // ��������������
        oled_buffer[page][col] ^= 0xFF;       // ��λȡ�������ԣ�
    }
}

/**
  * @brief      ��OLED��Ļ��ָ��������ȡ�������ԣ�����������
  * @param      page  Ҫ���Ե���������0-7��
  * @return     none
  * @note       �˺���������������Ļ��ʾ������Ҫ������ø��º���
  */
void oled_reverse_line_immediate(uint8 page)
{
		uint8 col;
    if(page >= 8) return;  // ��ֹԽ�����
    

    // �ȸ��»�����
    for(col = 0; col < 128; col++) {
        oled_buffer[page][col] ^= 0xFF;   // ��λȡ�������ԣ�
    }
    
    // ����������Ļ
    oled_set_pos_spi(0, page);
    for(col = 0; col < 128; col++) {
        oled_wrdat_spi(oled_buffer[page][col]);
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�ַ���(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      ch[]        �ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
//////void oled_p6x8str_spi(uint8 x,uint8 y,const int8 ch[])
//////{
//////	uint8 edata c=0,i=0,j=0;
//////	while (ch[j]!='\0')
//////	{
//////	  	c =ch[j]-32;
//////	  	if(x>126){x=0;y++;}
//////	  	oled_set_pos_spi(x,y);
//////	  	for(i=0;i<6;i++)	oled_wrdat_spi(oled_6x8[c][i]);
//////	  	x+=6;
//////	  	j++;
//////	}
//////}

void oled_p6x8str_spi(uint8 x, uint8 y, const int8 ch[])
{
    uint8 c, i, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if(x > 126) {
            x = 0;
            y++;
        }
        // ֱ�Ӳ���������
        for(i = 0; i < 6; i++) {
            if(y < 8 && x < 128) {
                oled_buffer[y][x] = oled_6x8[c][i];
            }
            x++;
        }
        j++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�޷�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �޷�����
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_uint16_spi(uint8 x, uint8 y, uint16 num)
{
	int8 ch[7];
	
	oled_hexascii_spi(num,ch);
    
    oled_p6x8str_spi(x, y, &ch[1]);	    //��ʾ����  6*8����
    //oled_p8x16str(x, y, &ch[1]);	//��ʾ����  8*16����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�з�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �з�����
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_int16_spi(uint8 x, uint8 y, int16 num)
{
	int8 ch[7];
	if(num<0)   {num = -num;oled_p6x8str_spi(x, y, "-");}
	else         oled_p6x8str_spi(x, y, " ");
	x+=6;       
    
	oled_hexascii_spi(num,ch);
    oled_p6x8str_spi(x, y, &ch[1]);	    //��ʾ����  6*8����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ32λ�з���(ȥ������������Ч��0)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      dat       	��Ҫ��ʾ�ı�������������uint32
//  @param      num       	��Ҫ��ʾ��λ�� ���10λ  ������������
//  @return     void
//  @since      v1.0
//  Sample usage:           oled_printf_int32(0,0,x,5);//x����Ϊint32 uint16 int16 uint8 int8����
//  Sample usage:           ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_int32_spi(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//����
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';
    
    oled_p6x8str_spi((uint8)x, (uint8)y, (int* )buff);	//��ʾ����
}

////-------------------------------------------------------------------------------------------------------------------
////  @brief      OLED��ʾ������(ȥ������������Ч��0)
////  @param      x			x����������0-127
////  @param      y           y����������0-7
////  @param      dat       	��Ҫ��ʾ�ı�������������float��double
////  @param      num         ����λ��ʾ����   ���10λ  
////  @param      pointnum    С��λ��ʾ����   ���6λ
////  @return     void
////  @since      v1.0
////  Sample usage:           oled_printf_float(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
////  @note                   �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
////                          ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
////                          �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
////                          ��������ʾһ�� ��-����   ������ʾһ���ո�
////-------------------------------------------------------------------------------------------------------------------
//void oled_printf_float_spi(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
//{
//    uint8   length;
//	int8    buff[34];
//	int8    start,end,point;

//	if(6<pointnum)  pointnum = 6;
//    if(10<num)      num = 10;
//        
//    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//����
//    else
//    {
//        length = zf_sprintf( &buff[1],"%f",dat);
//        length++;
//    }
//    point = length - 7;         //����С����λ��
//    start = point - num - 1;    //������ʼλ
//    end = point + pointnum + 1; //�������λ
//    while(0>start)//����λ����  ĩβӦ�����ո�
//    {
//        buff[end] = ' ';
//        end++;
//        start++;
//    }
//    
//    if(0>dat)   buff[start] = '-';
//    else        buff[start] = ' ';
//    
//    buff[end] = '\0';
//    
//    oled_p6x8str_spi((uint8)x, (uint8)y, (int8 *)buff);	//��ʾ����
//}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ������(ȥ������������Ч��0) - �޸���
//  @param      x          x����������0-127
//  @param      y          y����������0-7
//  @param      dat        ��Ҫ��ʾ�ı�������������float��double
//  @param      num        ����λ��ʾ����   ���10λ  
//  @param      pointnum   С��λ��ʾ����   ���6λ
//  @return     void
//  @since      v1.1
//  Sample usage:         oled_printf_float_spi(0,0,123.456,3,2); // ��ʾ"123.45"
//  @note                 �޸��������������⣬֧���������ֶ�̬������ʾ
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_float_spi(uint16 x, uint16 y, double dat, uint8 num, uint8 pointnum)
{
		char buffer[20] = {0};  // ��ʾ������
    int index = 0;          // ����������
		long integer_part;
		double decimal_part;
		unsigned long multiplier;
		int i,j;
		unsigned long decimal_int;
    char int_buf[12] = {0};
    int int_len = 0;
		long temp;
		int leading_spaces;
		unsigned int divisor,digit;
		
    // �����߽���
    if (pointnum > 6) pointnum = 6;
    if (num > 10) num = 10;
    
    // �����������datΪ0
    if (dat == 0) {
        dat = 0.0; // ȷ����ֵ����
    }
    
    // �������λ
    if (dat < 0) {
        buffer[index++] = '-';
        dat = -dat;  // ת��Ϊ��������
    } else {
        buffer[index++] = ' ';  // ������ʾ�ո�
    }
    
    // ����������С������
    integer_part = (long)dat;
    decimal_part = dat - integer_part;
    
    // ����С�����ֽ�λ
    multiplier = 1;
    for (i = 0; i < pointnum; i++) multiplier *= 10;
    
    decimal_int = (unsigned long)(decimal_part * multiplier + 0.5);
    
    // ����С����λ������
    if (decimal_int >= multiplier) {
        integer_part++;
        decimal_int = 0; // ��λ��С�����ֹ���
    }
    
    // ת����������

    temp = integer_part;
    
    // ������������Ϊ0�����
    if (temp == 0) {
        int_buf[int_len++] = '0';
    } else {
        // ��ȡ����λ���֣�����
        while (temp > 0) {
            int_buf[int_len++] = (temp % 10) + '0';
            temp /= 10;
        }
    }
    
    // === ��Ҫ�޸�1�������ո�������������� ===
    leading_spaces = num - int_len;
    if (leading_spaces > 0) {
        for (i = 0; i < leading_spaces; i++) {
            buffer[index++] = ' ';
        }
    }
    
    // ��ת���������ַ���������ת����
    for (i = int_len - 1; i >= 0; i--) {
        buffer[index++] = int_buf[i];
    }
    
    // ����С������
    if (pointnum > 0) {
        buffer[index++] = '.';  // С����
        
        // === ��Ҫ�޸�2������ʹ����������������ģ���� ===
        for (i = pointnum - 1; i >= 0; i--) {
            divisor = 1;
            for (j = 0; j < i; j++) divisor *= 10;
            digit = (decimal_int / divisor) % 10;
            buffer[index++] = digit + '0';
        }
    }
    
    buffer[index] = '\0';  // �ַ���������
    
    // OLED��ʾ
    oled_p6x8str_spi((uint8)x, (uint8)y, (int8 *)buffer);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾͼ��
//  @param      high  		ͼ��߶�
//  @param      width 		ͼ����
//  @param      *p    		ͼ���ַ�����飩
//  @param      value 		��ֵ����ֵ
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       ʹ��Image2lcd V3.2���ȡģ   C��������   ˮƽɨ��   
//              ��ȸ߶���������   ��ɫ��ת  256ɫ
//-------------------------------------------------------------------------------------------------------------------
void oled_dis_bmp_spi(uint16 high, uint16 width, uint8 *p,uint8 value)
{
	uint16 edata i,j;
    uint16 temp,temp1;
    uint8 dat;
    
    
    temp1 = high%8;
    if(temp1 == 0) temp = high/8;
    else           temp = high/8+1;

    for(i=0; i<temp; i++)
    {
        oled_set_pos_spi((uint8)0,(uint8)i);
        for(j=0; j<width; j++)
        {
            dat = 0;
            if( i<(temp-1) || !temp1 || temp1>=1)dat |= (*(p+i*8*width+j+width*0) > value? 1: 0)<<0;
            if( i<(temp-1) || !temp1 || temp1>=2)dat |= (*(p+i*8*width+j+width*1) > value? 1: 0)<<1;
            if( i<(temp-1) || !temp1 || temp1>=3)dat |= (*(p+i*8*width+j+width*2) > value? 1: 0)<<2;
            if( i<(temp-1) || !temp1 || temp1>=4)dat |= (*(p+i*8*width+j+width*3) > value? 1: 0)<<3;
            if( i<(temp-1) || !temp1 || temp1>=5)dat |= (*(p+i*8*width+j+width*4) > value? 1: 0)<<4;
            if( i<(temp-1) || !temp1 || temp1>=6)dat |= (*(p+i*8*width+j+width*5) > value? 1: 0)<<5;
            if( i<(temp-1) || !temp1 || temp1>=7)dat |= (*(p+i*8*width+j+width*6) > value? 1: 0)<<6;
            if( i<(temp-1) || !temp1 || temp1>=8)dat |= (*(p+i*8*width+j+width*7) > value? 1: 0)<<7;
           
            oled_wrdat_spi(dat);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʾ
//  @param      x       ������ 0-127
//  @param      y       ������ 0-7
//  @param      size    ȡģ��ʱ�����õĺ��������С��Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��㣬ȡģ��ʱ����Ҫ������һ���ġ�
//  @param      *p      ��Ҫ��ʾ�ĺ�������
//  @param      len     ��Ҫ��ʾ����λ
//  @return     void
//  @since      v1.0
//  Sample usage:		
//  @Note       ʹ��PCtoLCD2002���ȡģ		    ���롢����ʽ��˳��   16*16
//-------------------------------------------------------------------------------------------------------------------
void oled_print_chinese_spi(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len)
{
    uint16 i,j,k;
    
    for(i=0; i<len; i++)
    {
        for(j=0; j<(size/8); j++)
        {
            oled_set_pos_spi((uint8)(x+i*size), (uint8)(y+j));
            for(k=0; k<16; k++)
            {
                oled_wrdat_spi(*p);
                p++;
            }
        }
    }
}
