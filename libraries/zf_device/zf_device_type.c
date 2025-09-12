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

#include "zf_device_type.h"

wireless_type_enum  wireless_type	= NO_WIRELESS;
tof_type_enum       tof_type 		= NO_TOF;
gps_type_enum       gps_type 		= NO_GPS;

void (*tof_module_exti_handler)(uint8 dat) = NULL;			// ToF ģ�� INT �����ж�

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ģ������
// ����˵��     type_set        ѡ��������ģ������
// ����˵��     uart_callback   �豸�Ĵ��ڻص�����
// ���ز���     void
// ʹ��ʾ��     set_wireless_type(WIRELESS_UART, uart_callback);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_wireless_type (wireless_type_enum type_set, uart_index_enum uartx, void *uart_callback)
{
    wireless_type = type_set;
    
    if(uartx == UART_1)
    {
        uart1_irq_handler = uart_callback;
    }
    else if(uartx == UART_2)
    {
        uart2_irq_handler = uart_callback;
    }
    else if(uartx == UART_3)
    {
        uart3_irq_handler = uart_callback;
    }
    else if(uartx == UART_4)
    {
        uart4_irq_handler = uart_callback;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ToF ģ������
// ����˵��     type_set        ѡ���� ToF ģ������
// ����˵��     exti_callback   �豸���ⲿ�жϻص�����
// ���ز���     void
// ʹ��ʾ��     set_tof_type(TOF_DL1A, dl1a_int_handler);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_tof_type (tof_type_enum type_set, void *exti_callback)
{
    tof_type = type_set;
    tof_module_exti_handler = exti_callback;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ToF ģ������
// ����˵��     type_set        ѡ���� ToF ģ������
// ����˵��     exti_callback   �豸���ⲿ�жϻص�����
// ���ز���     void
// ʹ��ʾ��     set_tof_type(TOF_DL1A, dl1a_int_handler);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_gps_type (gps_type_enum type_set, uart_index_enum uartx, void *uart_callback)
{
    gps_type = type_set;
    if(uartx == UART_1)
    {
        uart1_irq_handler = uart_callback;
    }
    else if(uartx == UART_2)
    {
        uart2_irq_handler = uart_callback;
    }
    else if(uartx == UART_3)
    {
        uart3_irq_handler = uart_callback;
    }
    else if(uartx == UART_4)
    {
        uart4_irq_handler = uart_callback;
    }
}

