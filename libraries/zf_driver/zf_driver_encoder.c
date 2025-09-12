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

#include "zf_driver_gpio.h"
#include "zf_driver_encoder.h"

static volatile uint8 encoder_dir_pin[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ������������ȡֵ
// ����˵��     encoder_n      ��ʱ��ö����
// ���ز���     void
// ��ע��Ϣ
// ʹ��ʾ��    encoder_get_count(TIM2_ENCOEDER)  // ��ȡ��ʱ��2�Ĳɼ����ı���������
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count(encoder_index_enum encoder_n)
{
    int16 dat = 0;
    
    switch(encoder_n)
    {
        case TIM0_ENCOEDER:
        {
            dat = (uint16)TH0 << 8;
            dat = ((uint8)TL0) | dat;
            break;
        }
        
        case TIM1_ENCOEDER:
        {
            dat = (uint16)TH1 << 8;
            dat = ((uint8)TL1) | dat;
            break;
        }
        
        case TIM2_ENCOEDER:
        {
            dat = (uint16)T2H << 8;
            dat = ((uint8)T2L) | dat;
            break;
        }
        
        case TIM3_ENCOEDER:
        {
            dat = (uint16)T3H << 8;
            dat = ((uint8)T3L) | dat;
            break;
        }
        
        case TIM4_ENCOEDER:
        {
            dat = (uint16)T4H << 8;
            dat = ((uint8)T4L) | dat;
            break;
        }
        
        case TIM11_ENCOEDER:
        {
            dat = (uint16)T11H << 8;
            dat = ((uint8)T11L) | dat;
            break;
        }
        
    }
    
    if(gpio_get_level(encoder_dir_pin[encoder_n]))
    {
        return (-dat);
    }
    
    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ���ļ��������
// ����˵��     encoder_n      ��ʱ��ö����
// ���ز���     void
// ��ע��Ϣ
// ʹ��ʾ��    encoder_clear_count(TIM1_ENCOEDER)  //�����ʱ��1�ɼ����ı���������
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count(encoder_index_enum encoder_n)
{
    switch(encoder_n)
    {
        case TIM0_ENCOEDER:
        {
            TR0 = 0;
            TH0 = 0;
            TL0 = 0;
            TR0 = 1;
            break;
        }
        
        case TIM1_ENCOEDER:
        {
            TR1 = 0;
            TH1 = 0;
            TL1 = 0;
            TR1 = 1;
            break;
        }
        
        case TIM2_ENCOEDER:
        {
            AUXR &= ~(1 << 4);
            T2H = 0;
            T2L = 0;
            AUXR |= 1 << 4;
            break;
        }
        
        case TIM3_ENCOEDER:
        {
            T4T3M &= ~(1 << 3);
            T3H = 0;
            T3L = 0;
            T4T3M |= (1 << 3);
            break;
        }
        
        case TIM4_ENCOEDER:
        {
            T4T3M &= ~(1 << 7);
            T4H = 0;
            T4L = 0;
            T4T3M |= (1 << 7);
            break;
        }
        
        case TIM11_ENCOEDER:
        {
            T11CR &= ~(1 << 7);
            T11H = 0;
            T11L = 0;
            T11CR |= (1 << 7);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �����������ʼ��
// ����˵��     timer_ch        ��ʱ��ö����
// ����˵��     lsb_pin         ��������������
// ����˵��     dir_pin         ��������������
// ���ز���     void
//          �Ƽ�ʹ�ô���������������
// ʹ��ʾ��      encoder_init_dir(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11)
//                              // ʹ�ö�ʱ��1 ��������ı��������룬 ͨ��1�����ź�����E9��ͨ��2�����ź�����E11
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init(encoder_index_enum encoder_n, gpio_pin_enum dir_pin, encoder_channel_enum lsb_pin)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PWM Ȼ���ֳ�ʼ���� TIM1_ENCODER �����÷��ǲ������
    zf_assert(timer_funciton_check(encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((dir_pin >> 8) == 0x00);
    zf_assert((lsb_pin >> 8) == encoder_n);
    
    // ��ʼ����������
    gpio_init(dir_pin, GPI, 0, GPI_PULL_UP);
	
    gpio_init(lsb_pin&0xFF, GPI, 0, GPI_PULL_UP);
	
    encoder_dir_pin[encoder_n] = dir_pin;                               // ���������źŴ���������
    
    switch(encoder_n)
    {
        case TIM0_ENCOEDER:
        {
            TL0 = 0;
            TH0 = 0;
            TMOD |= 0x04; //�ⲿ����ģʽ
            TR0 = 1; //������ʱ��
            break;
        }
        
        case TIM1_ENCOEDER:
        {
            TL1 = 0x00;
            TH1 = 0x00;
            TMOD |= 0x40; // �ⲿ����ģʽ
            TR1 = 1; // ������ʱ��
            break;
        }
        
        case TIM2_ENCOEDER:
        {
            T2L = 0x00;
            T2H = 0x00;
            AUXR |= 0x18; // �����ⲿ����ģʽ��������ʱ��
            break;
        }
        
        case TIM3_ENCOEDER:
        {
            T3L = 0;
            T3H = 0;
            T4T3M |= 0x0c; // �����ⲿ����ģʽ��������ʱ��
            break;
        }
        
        case TIM4_ENCOEDER:
        {
            T4L = 0;
            T4H = 0;
            T4T3M |= 0xc0; // �����ⲿ����ģʽ��������ʱ��
            break;
        }
        
        case TIM11_ENCOEDER:
        {
            T11L = 0;
            T11H = 0;
            T11CR |= 0xc0; // �����ⲿ����ģʽ��������ʱ��
            break;
        }
    }
}


