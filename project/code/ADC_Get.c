#include "ADC_Get.h"

unsigned int raw_adc_data[4][5]={0};        // ԭʼ��������
unsigned int filtered_adc[4]={0};           // �˲����ADCֵ����
unsigned int ADC_Num[7]={0};
//���ADCͨ���Ͷ�ʱ����ʼ��//
void ADC_GetInit(void)
{   
    adc_init(ADC1_PIN,ADC_10BIT);
    adc_init(ADC2_PIN,ADC_10BIT);
    adc_init(ADC3_PIN,ADC_10BIT);
    adc_init(ADC4_PIN,ADC_10BIT);
	
//	adc_init(ADC5_PIN,ADC_10BIT);
//    adc_init(ADC6_PIN,ADC_10BIT);
//    adc_init(ADC8_PIN,ADC_10BIT);
}

//ADC����+�˲�
unsigned int adc_filter(unsigned int *samples, unsigned char count)
{
    unsigned char i;
    unsigned long sum = 0;
	unsigned int max=samples[0];
	unsigned int min=samples[0];
    
    if (count < 3) 
    {
        for (i = 0; i < count; i++) 
        {
            sum += samples[i];
        }
        return (unsigned int)(sum / count);
    }
    for (i = 0; i < count; i++) 
    {
		max=(samples[i] > max ) ? samples[i]:max;
		min=(samples[i] < min ) ? samples[i]:min;
		sum += samples[i];
	}
    return (unsigned int)((sum - max - min) / (count - 2));
}

// ADC���� �� �˲����� ����
void ADC_SampleAndFilter(void)
{
    unsigned char sample_index=0;          // ����ѭ��������
    unsigned char channel_index=0;         // ͨ��ѭ��������
    
    // �ɼ�5������
    for (sample_index = 0; sample_index < 3; sample_index++) 
    {
        raw_adc_data[0][sample_index] = adc_convert(ADC1_PIN);
        raw_adc_data[1][sample_index] = adc_convert(ADC2_PIN);
        raw_adc_data[2][sample_index] = adc_convert(ADC3_PIN);
        raw_adc_data[3][sample_index] = adc_convert(ADC4_PIN);
    }
    
    // �˲�����
    for (channel_index = 0; channel_index < 4; channel_index++) 
    {
        filtered_adc[channel_index] = adc_filter(raw_adc_data[channel_index], 3);
    }
}

//void ADC_ALL_GET()
//{
//	unsigned char i;
//	for(i= 0;i<7;i++)
//	{
//		ADC_1=adc_convert(ADC1_PIN);
//		ADC_2=adc_convert(ADC2_PIN);
//		ADC_3=adc_convert(ADC3_PIN);
//		ADC_4=adc_convert(ADC4_PIN);
//		ADC_5=adc_convert(ADC5_PIN);
//		ADC_6=adc_convert(ADC6_PIN);
//		ADC_8=adc_convert(ADC8_PIN);
//	}
//}
//��ص�ѹ���
bit Battery_Init=0;
unsigned int battery_get(void)
{
    unsigned int BGV = (VREFH_ARR << 8) + VREFL_ARR;
    unsigned int battery_adc = 0;
    unsigned int ref_adc;
    unsigned int battery_v;
    unsigned char i;
    
    //ͨ��ȫ�ֱ�����־λ�����ظ���ʼ��
    if(Battery_Init==0)
    {
        adc_init(ADC_CH15_POWR,ADC_10BIT);
        adc_init(ADC_CH5_P15,ADC_10BIT);
        Battery_Init=1;
    }
    //�ɼ�����ȡƽ��
    for (i = 0; i < 3; i++) 
    {
        battery_adc += adc_convert(ADC_CH5_P15);
    }
    battery_adc /= 3;                    
    
    ref_adc = adc_convert(ADC_CH15_POWR);
    
    battery_v = (unsigned int)((unsigned long)BGV * battery_adc / ref_adc);
    
    return battery_v*4;
}