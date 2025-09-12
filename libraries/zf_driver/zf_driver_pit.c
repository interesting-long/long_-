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

#include "zf_common_clock.h"
#include "zf_driver_pit.h"

#pragma warning disable = 183
#pragma warning disable = 177

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ�������ж�
//  @param      pit_n      ��ʱ��ͨ����
//  @param      time_ms    ʱ��(ms)
//  @return     void
//  Sample usage:          pit_timer_ms(TIM_0, 10)
//						   ʹ�ö�ʱ��0�������жϣ�ʱ��10msһ�Ρ�
//-------------------------------------------------------------------------------------------------------------------
void pit_init(pit_index_enum pit_n, uint32 period)
{
	uint8 freq_div = 0;                
    uint16 period_temp = 0;               
    uint16 temp = 0;


	if(period > (255*65535))
	{
		// ���ö�ʱ��Ϊ12Tģʽ��ֹ���
		period = period / 12;
		
		if(TIM0_PIT == pit_n)
		{
			AUXR &= ~0x80;		
		}
		else if(TIM1_PIT == pit_n)
		{
			AUXR &= ~0x40;		
		}
		else if(TIM2_PIT == pit_n)
		{
			AUXR &= ~0x04;		
		}
		else if(TIM3_PIT == pit_n)
		{
			T4T3M &= ~0x02;	
		}
		else if(TIM4_PIT == pit_n)
		{
			T4T3M &= ~0x20;		
		}
		else if(TIM11_PIT == pit_n)
		{
			T11CR &= ~0x10;		
		}

	}
	else
	{
		// ����Ϊ1Tģʽ
		if(TIM0_PIT == pit_n)
		{
			AUXR |= 0x80;		
		}
		else if(TIM1_PIT == pit_n)
		{
			AUXR |= 0x40;		
		}
		else if(TIM2_PIT == pit_n)
		{
			AUXR |= 0x04;		
		}
		else if(TIM3_PIT == pit_n)
		{
			T4T3M |= 0x02;	
		}
		else if(TIM4_PIT == pit_n)
		{
			T4T3M |= 0x20;		
		}
		else if(TIM11_PIT == pit_n)
		{
			T11CR |= 0x10;		
		}
	}
		
	
	freq_div = ((period) >> 15);                   // ����Ԥ��Ƶ
	period_temp = ((period) / (freq_div+1));       // �����Զ���װ��ֵ

	temp = (uint16)65536 - period_temp;

    if(TIM0_PIT == pit_n)
    {
		TM0PS = freq_div;	// ���÷�Ƶֵ
        TMOD |= 0x00; 		// ģʽ 0
        TL0 = temp;
        TH0 = temp >> 8;
        TR0 = 1; 			// ������ʱ��
        ET0 = 1; 			// ʹ�ܶ�ʱ���ж�
    }
    else if(TIM1_PIT == pit_n)
    {
		TM1PS = freq_div;	// ���÷�Ƶֵ
        TMOD |= 0x00; // ģʽ 0
        TL1 = temp;
        TH1 = temp >> 8;
        TR1 = 1; // ������ʱ��
        ET1 = 1; // ʹ�ܶ�ʱ���ж�
    }
    else if(TIM2_PIT == pit_n)
    {
		TM2PS = freq_div;	// ���÷�Ƶֵ
        T2L = temp;
        T2H = temp >> 8;
        AUXR |= 0x10; // ������ʱ��
        IE2 |= 0x04; // ʹ�ܶ�ʱ���ж�
    }
    else if(TIM3_PIT == pit_n)
    {
		TM3PS = freq_div;	// ���÷�Ƶֵ
        T3L = temp;
        T3H = temp >> 8;
        T4T3M |= 0x08; // ������ʱ��
        IE2 |= 0x20; // ʹ�ܶ�ʱ���ж�
    }
    else if(TIM4_PIT == pit_n)
    {
		TM4PS = freq_div;	// ���÷�Ƶֵ
        T4L = temp;
        T4H = temp >> 8;
        T4T3M |= 0x80; // ������ʱ��
        IE2 |= 0x40; // ʹ�ܶ�ʱ���ж�
    }
	else if(TIM11_PIT == pit_n)
	{
		T11PS = freq_div;	// ���÷�Ƶֵ
		T11L = temp;
        T11H = temp >> 8;
		T11CR = 0x82;	// ������ʱ����ʹ�ܶ�ʱ���ж�
		
	}
}

