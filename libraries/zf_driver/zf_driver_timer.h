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

#ifndef _zf_driver_timer_h
#define _zf_driver_timer_h


#include "zf_common_debug.h"
#include "zf_common_clock.h"

//��ö�ٶ��岻�����û��޸�
typedef enum
{
	TIM_0 = 0,
    TIM_1,
    TIM_2,
    TIM_3,
    TIM_4,
    TIM_11,
}timer_index_enum;


typedef enum
{
    TIMER_FUNCTION_INIT = 0,                  // ����δ��ʼ��    
    TIMER_FUNCTION_TIMER,                     // ���� TIMER ��ʱ 
    TIMER_FUNCTION_PIT,                       // ���� PIT ���ڶ�ʱ��
    TIMER_FUNCTION_ENCODER,                   // ���� ENCODER �����벶��  
    TIMER_FUNCTION_UART,                      // ���� UART �Ĳ����ʷ����� 
}timer_function_enum;


uint8 timer_funciton_check(timer_index_enum index, timer_function_enum mode);


#endif
