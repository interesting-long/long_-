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

#ifndef _zf_common_debug_h_
#define _zf_common_debug_h_

#include "zf_common_typedef.h"
#include "zf_driver_uart.h"


#include "zf_common_typedef.h"
#define PRINTF_ENABLE               (1)                                          // ʹ��printf

// ����޸Ĵ��ڲ������� debug UART ���жϽ��� ��Ҫͬ������ debug_interrupr_handler ��������Ӧ���жϷ�����
// ����޸Ĵ��ڲ������� debug UART ���жϽ��� ��Ҫͬ������ debug_interrupr_handler ��������Ӧ���жϷ�����
// ����޸Ĵ��ڲ������� debug UART ���жϽ��� ��Ҫͬ������ debug_interrupr_handler ��������Ӧ���жϷ�����
#define DEBUG_UART_INDEX            (UART_1)                               	// ָ�� debug uart ��ʹ�õĵĴ���
#define DEBUG_UART_BAUDRATE         (115200)                				// ָ�� debug uart ��ʹ�õĵĴ��ڲ�����
#define DEBUG_UART_TX_PIN           (UART1_TX_P31 )                        	// ָ�� debug uart ��ʹ�õĵĴ�������
#define DEBUG_UART_RX_PIN           (UART1_RX_P30 )                        	// ָ�� debug uart ��ʹ�õĵĴ�������

#define DEBUG_UART_USE_INTERRUPT    (1)                                         // �Ƿ����� debug uart �����ж�

//-------------------------------------------------------------------------------------------------------------------
// �������     ����
// ����˵��     x           �ж��Ƿ񴥷����� 0-�������� 1-����������
// ���ز���     void
// ʹ��ʾ��     zf_assert(0);
// ��ע��Ϣ     һ�����ڲ����ж� zf_assert(0) �Ͷ��Ա���
//              Ĭ������»��� Debug UART ���
//              �����ʹ�ÿ�Դ������Ļ�ӿڳ�ʼ������Ļ �������Ļ����ʾ
//-------------------------------------------------------------------------------------------------------------------
#define zf_assert(x)                (debug_assert_handler((x), __FILE__, __LINE__))

//-------------------------------------------------------------------------------------------------------------------
// �������     Log ��Ϣ���
// ����˵��     x           �ж��Ƿ񴥷���� 0-������� 1-���������
// ����˵��     *str        ��Ҫ����� Log ��Ϣ
// ���ز���     void
// ʹ��ʾ��     printf( "Error");
// ��ע��Ϣ     ������Ϣ��� ������һЩ������߾���֮������
//              Ĭ������»��� Debug UART ���
//              �����ʹ�ÿ�Դ������Ļ�ӿڳ�ʼ������Ļ �������Ļ����ʾ
//-------------------------------------------------------------------------------------------------------------------
#define zf_log(x, str)              (debug_log_handler((x), (str), __FILE__, __LINE__))


//typedef struct
//{
//    uint16 type_index;

//    uint16 display_x_max;
//    uint16 display_y_max;

//    uint8 font_x_size;
//    uint8 font_y_size;

//    void (*output_uart)             (const char *str);
//    void (*output_screen)           (uint16 x, uint16 y, const char *str);
//    void (*output_screen_clear)     (void);
//}debug_output_struct;

uint32      debug_send_buffer(const uint8 *buff, uint32 len);
#if DEBUG_UART_USE_INTERRUPT                                                    // ������� debug uart �����ж�
#define     DEBUG_RING_BUFFER_LEN   (64)                                        // ���廷�λ�������С Ĭ�� 64byte
#endif

uint32      debug_read_buffer(uint8 *buff, uint32 len);
//void        debug_assert_enable         (void);
//void        debug_assert_disable        (void);
void        debug_assert_handler        (uint8 pass, char *file, int line);
void        debug_log_handler           (uint8 pass, char *str, char *file, int line);
//void        debug_output_struct_init    (debug_output_struct *info);
//void        debug_output_init           (debug_output_struct *info);
void        debug_init                  (void);

#endif