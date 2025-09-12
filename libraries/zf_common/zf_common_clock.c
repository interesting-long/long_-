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

#include "zf_common_typedef.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"

#include "zf_driver_delay.h"

//�ں�Ƶ��
int32 system_clock = SYSTEM_CLOCK_40M;


void clock_init (uint32 clock)                                              // ����ʱ�ӳ�ʼ��
{
	P_SW2 = 0x80;           // ���������ַ����
    CKCON = 0x00;           // �����ⲿ��������Ϊ���
    WTST = 0;               // ���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���

	// �ⲿ����
    XOSCCR = 0xc0;          // �����ⲿ����
    while (!(XOSCCR & 1));  // �ȴ�ʱ���ȶ�
    CLKDIV = 0x00;          // ʱ�Ӳ���Ƶ
    CLKSEL = 0x01;          // ѡ���ⲿ����
	CLKDIV = 0x00;          // 40MHz��Ƶ����Ƶ����
	
	system_delay_init();    // ��ʱ������ʼ��


	system_clock = clock;
	
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
	

    ADCCFG = 0x00;
    AUXR = 0x00;
    SCON = 0x00;
    S2CON = 0x00;
    S3CON = 0x00;
    S4CON = 0x00;
	P_SW1 = 0x00;
	P_SW3 = 0x00;
    IE2 = 0x00;
    TMOD = 0x00;
	PWMA_ENO = 0x00;
	PWMB_ENO = 0x00;
	
	HSCLKDIV = 0x00;
	SPI_CLKDIV = 0x00;
	
	
	interrupt_global_enable();
}


