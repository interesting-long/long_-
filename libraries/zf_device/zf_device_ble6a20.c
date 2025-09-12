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

#include "zf_device_ble6a20.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_device_type.h"

#pragma warning disable = 183
#pragma warning disable = 177

static  fifo_struct                                     ble6a20_fifo;
static  uint8                                           ble6a20_buffer[BLE6A20_BUFFER_SIZE];

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��������
// ����˵��     data            8bit ����
// ���ز���     uint32          ʣ�෢�ͳ��� 0-������� 1-δ�������
// ʹ��ʾ��     ble6a20_send_byte(data);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_send_byte (const uint8 dat)
{
    uint16 time_cnt = BLE6A20_TIMEOUT_COUNT;
    
    while (time_cnt && gpio_get_level(BLE6A20_RTS_PIN)) 
	{
        system_delay_ms(1);
        time_cnt--;
    }
    
    if (time_cnt) 
	{
        uart_write_byte(BLE6A20_INDEX, dat);
    }
    
    return time_cnt == 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �������ݿ�
// ����˵��     *buff           ���ͻ�����
// ����˵��     len             �������ݳ���
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     ble6a20_send_buffer(buff, 64);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_send_buffer (const uint8 *buff, uint32 len)
{
    #define PKT_SIZE 64
    #define DELAY_MS 1
    
    uint16 time_cnt = 0;
	uint16 send_len = 0;
    zf_assert(NULL != buff);  // ȷ���������ǿ�
    
    while(len && time_cnt < BLE6A20_TIMEOUT_COUNT)
    {
        if(!gpio_get_level(BLE6A20_RTS_PIN))	// RTS�͵�ƽ���ɷ���
        {
            send_len = len < PKT_SIZE ? len : PKT_SIZE;
            uart_write_buffer(BLE6A20_INDEX, buff, send_len);
            buff += send_len;
            len -= send_len;
            time_cnt = 0;	 // ���ó�ʱ����
        }
		else	// RTS�ߵ�ƽ��ģ��æ
		{
			system_delay_ms(DELAY_MS);
			time_cnt++;
		}
    }
    
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����ַ���
// ����˵��     *str            Ҫ���͵��ַ�����ַ
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     ble6a20_send_string("Believe in yourself.");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_send_string (const char *str)
{
    uint32 len = strlen(str);
    zf_assert(NULL != str);
	
    return  ble6a20_send_buffer(str, len);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ȡ����
// ����˵��     *buff           ���ջ�����
// ����˵��     len             ��ȡ���ݳ���
// ���ز���     uint32          ʵ�ʶ�ȡ���ݳ���
// ʹ��ʾ��     ble6a20_read_buffer(buff, 32);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_read_buffer (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    zf_assert(NULL != buff);
    fifo_read_buffer(&ble6a20_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����жϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ble6a20_callback();
// ��ע��Ϣ     �ú����� ISR �ļ� �����жϳ��򱻵���
//              �ɴ����жϷ��������� wireless_module_uart_handler() ����
//              ���� wireless_module_uart_handler() �������ñ�����
//-------------------------------------------------------------------------------------------------------------------
void ble6a20_callback (uint8 uart_dat)
{
//    uart_query_byte(BLE6A20_INDEX, &ble6a20_data);
    fifo_write_buffer(&ble6a20_fifo, &uart_dat, 1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ble6a20_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 ble6a20_init (void)
{
    uint8 return_state = 0;
    
    // �ȴ�ģ���ʼ��
    system_delay_ms(50);
    
    set_wireless_type(BLE6A20, BLE6A20_INDEX, ble6a20_callback);
    
    fifo_init(&ble6a20_fifo, FIFO_DATA_8BIT, ble6a20_buffer, BLE6A20_BUFFER_SIZE);
    gpio_init(BLE6A20_RTS_PIN, GPIO, GPIO_HIGH, GPIO_NO_PULL);
    
    // ������ʹ�õĲ�����Ϊ115200 Ϊ����ת����ģ���Ĭ�ϲ����� ������������������������ģ�鲢�޸Ĵ��ڵĲ�����
    uart_init (BLE6A20_INDEX, BLE6A20_BUAD_RATE, BLE6A20_RX_PIN, BLE6A20_TX_PIN);   // ��ʼ������
    uart_rx_interrupt(BLE6A20_INDEX, 1);
    
    return return_state;
}
