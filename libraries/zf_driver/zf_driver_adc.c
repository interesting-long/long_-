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

#include "zf_common_debug.h"
#include "zf_driver_adc.h"


static uint8 adc_resolution = {ADC_12BIT};


//-------------------------------------------------------------------------------------------------------------------
// �������     ADCת��N�Σ�ƽ��ֵ�˲�
// ����˵��     ch              ѡ��ADCͨ��
// ����˵��     resolution      �ֱ���(8λ 10λ 12λ)
// ����˵��     count           ת������
// ���ز���     void
// ʹ��ʾ��     adc_mean_filter(ADC_IN0_A0, ADC_8BIT,5);  //�ɼ�A0�˿ڷ���8λ�ֱ��ʵ�ADֵ���ɼ����ȡƽ��ֵ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i;
    uint32 sum;

	zf_assert(count);//���Դ�������Ϊ0
	
    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(ch);
    }

    sum = sum/count;
    return sum;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCת��һ��
//  @param      adcn            ѡ��ADCͨ��
//  @param      resolution      �ֱ���
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert(adc_channel_enum ch)
{
    uint16 adc_value;
    
    ADC_CONTR &= (0xF0);			//���ADC_CHS[3:0] �� ADC ģ��ͨ��ѡ��λ
    ADC_CONTR |= ch;
    
    ADC_CONTR |= 0x40;  			// ���� AD ת��
    
    while (!(ADC_CONTR & 0x20));  	// ��ѯ ADC ��ɱ�־
    
    ADC_CONTR &= ~0x20;  			// ����ɱ�־
    
    adc_value = ADC_RES;  			//�洢 ADC �� 12 λ����ĸ� 4 λ
    adc_value <<= 8;
    adc_value |= ADC_RESL;  		//�洢 ADC �� 12 λ����ĵ� 8 λ
    
    ADC_RES = 0;
    ADC_RESL = 0;
    
    adc_value >>= adc_resolution;	//ȡ����λ
    
    
    return adc_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ADC��ʼ��
// ����˵��     ch      			ch(��ѡ��Χ��zf_adc.h��adc_channel_enumö��ֵȷ��)
// ����˵��     resolution       resolution(��ѡ��Χ��zf_adc.h��adc_resolution_enumö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     adc_init(ADC_P10, ADC_12BIT);//��ʼ��P10����ΪADC���ܣ�12λ�ֱ���
//-------------------------------------------------------------------------------------------------------------------
void adc_init(adc_channel_enum ch, adc_resolution_enum resolution)
{
    ADC_CONTR |= 1 << 7;				//1 ���� ADC ��Դ
    
    ADC_CONTR &= (0xF0);			//���ADC_CHS[3:0] �� ADC ģ��ͨ��ѡ��λ
    ADC_CONTR |= ch;
    
    if((ch >> 3) == 1) //P0.0
    {
        //IO����Ҫ����Ϊ��������
        P0M0 &= ~(1 << (ch & 0x07));
        P0M1 |= (1 << (ch & 0x07));
    }
    else if((ch >> 3) == 0) //P1.0
    {
        //IO����Ҫ����Ϊ��������
        P1M0 &= ~(1 << (ch & 0x07));
        P1M1 |= (1 << (ch & 0x07));
    }
    
    ADCCFG |= ADC_SYSclk_DIV_4 & 0x0F;			//ADCʱ��Ƶ��SYSclk/16&0x0F;
    
    ADCCFG |= 1 << 5;							//ת������Ҷ��롣 ADC_RES �������ĸ� 2 λ�� ADC_RESL �������ĵ� 8 λ��
	
	adc_resolution = resolution;           // ��¼ADC���� ���ڲɼ�ʱʹ��
}