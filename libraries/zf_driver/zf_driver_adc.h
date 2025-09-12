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

#ifndef __ZF_DRIVER_ADC_H
#define __ZF_DRIVER_ADC_H

#include "zf_common_typedef.h"

//��ö�ٶ��岻�����û��޸�
typedef enum
{
    ADC_CH0_P10 = 0,
    ADC_CH1_P11,
    ADC_CH2_P12,
    ADC_CH3_P13,
    ADC_CH4_P14,
    ADC_CH5_P15,
    ADC_CH6_P16,
    ADC_CH7_P17,
    
    ADC_CH8_P00,
    ADC_CH9_P01,
    ADC_CH10_P02        	,
    ADC_CH11_P03        	,
    ADC_CH12_P04        	,
    ADC_CH13_P05        	,
    ADC_CH14_P06        	,
    ADC_CH15_POWR = 0x0f	, //�ڲ�AD 1.19V
} adc_channel_enum;

//��ö�ٶ��岻�����û��޸�
typedef enum
{
    ADC_SYSclk_DIV_2 = 0,
    ADC_SYSclk_DIV_4,
    ADC_SYSclk_DIV_6,
    ADC_SYSclk_DIV_8,
    ADC_SYSclk_DIV_10,
    ADC_SYSclk_DIV_12,
    ADC_SYSclk_DIV_14,
    ADC_SYSclk_DIV_16,
    ADC_SYSclk_DIV_18,
    ADC_SYSclk_DIV_20,
    ADC_SYSclk_DIV_22,
    ADC_SYSclk_DIV_24,
    ADC_SYSclk_DIV_26,
    ADC_SYSclk_DIV_28,
    ADC_SYSclk_DIV_30,
    ADC_SYSclk_DIV_32,
} adc_speed_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{

    ADC_12BIT = 0,  //12λ�ֱ���
    ADC_11BIT,		//11λ�ֱ���
    ADC_10BIT,		//10λ�ֱ���
    ADC_9BIT,    	//9λ�ֱ���
    ADC_8BIT,     	//8λ�ֱ���
    
} adc_resolution_enum;


uint16  adc_convert             (adc_channel_enum ch);
uint16  adc_mean_filter_convert (adc_channel_enum ch, const uint8 count);
void    adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);



#endif