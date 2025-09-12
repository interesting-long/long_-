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

#ifndef _zf_driver_encoder_h
#define _zf_driver_encoder_h


#include "zf_common_debug.h"
#include "zf_common_clock.h"

typedef enum
{
	
    TIM0_ENCOEDER_P34  = 0x0000 | IO_P34,
    TIM1_ENCOEDER_P35  = 0x0100 | IO_P35,
	TIM2_ENCOEDER_P12  = 0x0200 | IO_P12,
	TIM3_ENCOEDER_P04  = 0x0300 | IO_P04,
	TIM4_ENCOEDER_P06  = 0x0400 | IO_P06,
	TIM11_ENCOEDER_P14 = 0x0500 | IO_P14,
}encoder_channel_enum;


typedef enum
{
	TIM0_ENCOEDER = 0,
    TIM1_ENCOEDER,
    TIM2_ENCOEDER,
    TIM3_ENCOEDER,
    TIM4_ENCOEDER,
    TIM11_ENCOEDER,
}encoder_index_enum;


int16   encoder_get_count   (encoder_index_enum encoder_n);
void    encoder_clear_count (encoder_index_enum encoder_n);
void    encoder_dir_init    (encoder_index_enum encoder_n, gpio_pin_enum dir_pin, encoder_channel_enum lsb_pin);




#endif
