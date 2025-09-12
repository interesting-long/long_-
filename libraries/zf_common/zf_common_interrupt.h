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


#ifndef __ZF_DRIVER_NVIC_H
#define __ZF_DRIVER_NVIC_H

#include "zf_common_typedef.h"

//��ö�����ֹ�û��޸�
//�ж����ȼ�����ö����
typedef enum
{
    INT0_IRQn = 0x00,
    TIMER0_IRQn,
    INT1_IRQn,
    TIMER1_IRQn,
    UART1_IRQn,
    ADC_IRQn,
    LVD_IRQn,			//��ѹ����ж�
    CCP_PCA_PWM_IRQn,	//CCP/PCA/PWM �ж�
    
    UART2_IRQn = 0x10,
    SPI_IRQn,
    PWMA_IRQn,
    PWMB_IRQn,
    INT4_IRQn,
    CMP_IRQn,
    IIC_IRQn,
    USB_IRQn,	
    
    UART3_IRQn = 0x20,
    UART4_IRQn,
	RTC_IRQ,
	IIS_IRQ,

	// ���಻�����õģ��ж����ȼ�ȫ��Ϊ������ȼ�0
    
} irqn_type_enum;


void interrupt_set_priority(irqn_type_enum irqn, uint8 priority);

void interrupt_global_disable(void);
void interrupt_global_enable(void);


#endif