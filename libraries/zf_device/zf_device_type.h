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
#ifndef _zf_device_type_h_
#define _zf_device_type_h_

#include "zf_common_typedef.h"
#include "zf_driver_uart.h"

typedef enum
{
    NO_WIRELESS = 0,                                                            // ���豸
    WIRELESS_UART,                                                              // ���ߴ���
    BLE6A20,																	// ����BLE6A20
	LORA3A22_UART																// LORA
} wireless_type_enum;

typedef enum
{
    NO_TOF = 0,                                                                 // ���豸
    TOF_DL1A,                                                                   // DL1A
    TOF_DL1B,                                                                   // DL1B
} tof_type_enum;

typedef enum
{
    NO_GPS = 0,                                                                 // ���豸
    GPS_TAU1201,                                                                   // DL1A

} gps_type_enum;


#define	SOFT_IIC 		(0)
#define SOFT_SPI 		(1)                                                              // ���豸
#define	HARDWARE_IIC 	(2)
#define	HARDWARE_SPI 	(3)


extern gps_type_enum 		gps_type;
extern tof_type_enum 		tof_type;
extern wireless_type_enum  	wireless_type;

extern void (*wireless_module_uart_handler)	(uint8 dat);
extern void (*tof_module_exti_handler)		(uint8 dat);


extern void set_wireless_type (wireless_type_enum type_set, uart_index_enum uartx, void *uart_callback);
extern void set_tof_type (tof_type_enum type_set, void *exti_callback);
extern void set_gps_type (gps_type_enum type_set, uart_index_enum uartx, void *uart_callback);

#endif
