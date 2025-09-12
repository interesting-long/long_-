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
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   CLK                 �鿴 zf_device_tsl1401.h �� TSL1401_CLK_PIN �궨��
*                   SI                  �鿴 zf_device_tsl1401.h �� TSL1401_SI_PIN �궨��
*                   AO[x]               �鿴 zf_device_tsl1401.h �� TSL1401_AO_PINx �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_tsl1401_h_
#define _zf_device_tsl1401_h_

#include "zf_common_typedef.h"
#include "zf_driver_uart.h"

#define TSL1401_AO_PIN          (ADC_CH5_P15)                                   // ��Ӧ��һ�� TSL1401 �� AO ����
#define TSL1401_AO_PIN2         (ADC_CH7_P17)                                   // ��Ӧ�ڶ��� TSL1401 �� AO ����

// TSL1401 �Ŀ������Ŷ��� ��� TSL1401 ���齫��������ֱ�Ӳ���
#define TSL1401_CLK_PIN         (IO_P32)                                            // TSL1401 �� CLK ���Ŷ���
#define TSL1401_SI_PIN          (IO_P33)                                            // TSL1401 �� SI ���Ŷ���
#define TSL1401_CLK(x)          ((x) ? (gpio_high(TSL1401_CLK_PIN)) : (gpio_low(TSL1401_CLK_PIN)))
#define TSL1401_SI(x)           ((x) ? (gpio_high(TSL1401_SI_PIN)) : (gpio_low(TSL1401_SI_PIN)))

#define TSL1401_AD_RESOLUTION   (ADC_8BIT)                                      // ADC ���� 8bit
#define TSL1401_DATA_LEN        (128 )                                          // TSL1401 ���ݳ���

extern uint16 tsl1401_data[2][TSL1401_DATA_LEN];                                // TSL1401 ���ݴ������
extern uint8 tsl1401_finish_flag;                                               // TSL1401 ���ݲɼ���ɱ�־

void tsl1401_collect_pit_handler    (void);
void tsl1401_send_data              (uart_index_enum uart_n, uint8 index);
void tsl1401_init                   (void);

#endif
