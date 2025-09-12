/*********************************************************************************************************************
* AI8051U Opensourec Library ����AI8051U ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���STC ��Դ���һ����
*
* AI8051U ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK FOR C251
* ����ƽ̨          AI8051U
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����           ��ע
* 2024-08-01        ��W            first version
********************************************************************************************************************/

#ifndef _zf_common_font_h_
#define _zf_common_font_h_

#include "zf_common_typedef.h"

//-------������ɫ----------
typedef enum
{
    RGB565_WHITE    = (0xFFFF),                                                     // ��ɫ
    RGB565_BLACK    = (0x0000),                                                     // ��ɫ
    RGB565_BLUE     = (0x001F),                                                     // ��ɫ
    RGB565_PURPLE   = (0xF81F),                                                     // ��ɫ
    RGB565_PINK     = (0xFE19),                                                     // ��ɫ
    RGB565_RED      = (0xF800),                                                     // ��ɫ
    RGB565_MAGENTA  = (0xF81F),                                                     // Ʒ��
    RGB565_GREEN    = (0x07E0),                                                     // ��ɫ
    RGB565_CYAN     = (0x07FF),                                                     // ��ɫ
    RGB565_YELLOW   = (0xFFE0),                                                     // ��ɫ
    RGB565_BROWN    = (0xBC40),                                                     // ��ɫ
    RGB565_GRAY     = (0x8430),                                                     // ��ɫ

    RGB565_39C5BB   = (0x3616),
    RGB565_66CCFF   = (0x665F),
}rgb565_color_enum;

extern const uint8 code ascii_font_8x16[][16];
//extern const uint8 code ascii_font_6x8[][6];



#endif
