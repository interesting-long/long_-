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
*                   RX                  �鿴 zf_device_wireless_ble6a20.h �� BLE6A20_RX_PIN  �궨��
*                   TX                  �鿴 zf_device_wireless_ble6a20.h �� BLE6A20_TX_PIN  �궨��
*                   RTS                 �鿴 zf_device_wireless_ble6a20.h �� BLE6A20_RTS_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/


#ifndef _zf_device_ble6a20_h_
#define _zf_device_ble6a20_h_

#include "zf_common_typedef.h"

#define BLE6A20_INDEX        		( UART_4 )                 		// �������ڶ�Ӧʹ�õĴ��ں�
#define BLE6A20_BUAD_RATE    		( 115200 )                    	// �������ڶ�Ӧʹ�õĴ��ڲ�����,
#define BLE6A20_TX_PIN       		( UART4_RX_P02 )      			// �������ڶ�Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define BLE6A20_RX_PIN       		( UART4_TX_P03 )           		// �������ڶ�Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX
#define BLE6A20_RTS_PIN      		( IO_P11 )                   	// �������ڶ�Ӧģ��� RTS ����

#define BLE6A20_BUFFER_SIZE        	( 64 )
#define BLE6A20_TIMEOUT_COUNT      	( 100 )

uint32      ble6a20_send_byte         (const uint8 dat);
uint32      ble6a20_send_buffer       (const uint8 *buff, uint32 len);
uint32      ble6a20_send_string       (const char *str);
void        ble6a20_send_image        (const uint8 *image_addr, uint32 image_size);

uint32      ble6a20_read_buffer       (uint8 *buff, uint32 len);

void 		ble6a20_callback 		  (uint8 uart_dat);

uint8       ble6a20_init              (void);

#endif
