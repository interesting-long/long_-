/*********************************************************************************************************************
* STC32G Opensourec Library ����STC32G ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���STC ��Դ���һ����
*
* STC32G ��Դ�� ��������
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

#include "seekfree_assistant.h"

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ַ��ͺ���
// ����˵��     *buff           ��Ҫ���͵����ݵ�ַ
// ����˵��     length          ��Ҫ���͵ĳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
uint32 (*seekfree_assistant_transfer_callback)   (const uint8 *buff, uint32 length);


//-------------------------------------------------------------------------------------------------------------------
// �������     ������ֽ������ݺ���
// ����˵��     *buff           ��Ҫ���յ����ݵ�ַ
// ����˵��     length          Ҫ���յ�������󳤶�
// ���ز���     uint32          ���յ������ݳ���
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
uint32 (*seekfree_assistant_receive_callback)    (uint8 *buff, uint32 length);


//-------------------------------------------------------------------------------------------------------------------
// �������     ������ֽӿ� ��ʼ��
// ����˵��
// ���ز���     void
// ʹ��ʾ��     seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI); ʹ�ø���WIFI SPIģ����������շ�
// ��ע         ��Ҫ���е����豸�ĳ�ʼ��������ʹ������ת���ڽ������ݵ��շ�������Ҫ���е�������ת���ڵĳ�ʼ����Ȼ���ٵ���seekfree_assistant_interface_init���������ֵĽӿڳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
void seekfree_assistant_interface_init (seekfree_assistant_transfer_device_enum transfer_device)
{
    switch(transfer_device)
    {
        case SEEKFREE_ASSISTANT_DEBUG_UART:
        {
            seekfree_assistant_transfer_callback = debug_send_buffer;
            seekfree_assistant_receive_callback = debug_read_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_WIRELESS_UART:
        {
            seekfree_assistant_transfer_callback = wireless_uart_send_buffer;
            seekfree_assistant_receive_callback = wireless_uart_read_buffer;
        }break;
        

        case SEEKFREE_ASSISTANT_BLE6A20:
        {
            seekfree_assistant_transfer_callback = ble6a20_send_buffer;
            seekfree_assistant_receive_callback = ble6a20_read_buffer;
        }break;

        case SEEKFREE_ASSISTANT_CUSTOM:
        {         
            // �����Լ������� ����ʵ��seekfree_assistant_transfer��seekfree_assistant_receive������������ݵ��շ�
            
        }break;
    }
}


