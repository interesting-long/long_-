#include "ADC_Get.h"

unsigned int raw_adc_data[4][5]={0};        // ԭʼ��������
unsigned int filtered_adc[4]={0};           // �˲����ADCֵ����

//���ADCͨ���Ͷ�ʱ����ʼ��
void ADC_GetInit(void)
{   
    adc_init(ADC_CH0_P10,ADC_10BIT);
    adc_init(ADC_CH9_P01,ADC_10BIT);
    adc_init(ADC_CH13_P05,ADC_10BIT);
    adc_init(ADC_CH14_P06,ADC_10BIT);
}

//ADC����+�˲�
unsigned int adc_filter(unsigned int *samples, unsigned char count)
{
    unsigned int temp[5];
    unsigned char i,j;
    unsigned int swap;
    unsigned long sum = 0;
    
    if (count < 3) 
    {
        sum = 0;
        for (i = 0; i < count; i++) 
        {
            sum += samples[i];
        }
        return (unsigned int)(sum / count);
    }
    
    for (i = 0; i < count; i++) 
    {
        temp[i] = samples[i];
    }

    for (i = 0; i < count - 1; i++) 
    {
        for (j = 0; j < count - i - 1; j++) 
        {
            if (temp[j] > temp[j + 1]) 
            {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    sum = 0;
    for (i = 1; i < count - 1; i++) 
    {
        sum += temp[i];
    }
    
    return (unsigned int)(sum / (count - 2));
}

// ADC���� �� �˲����� ����
void ADC_SampleAndFilter(void)
{
    unsigned char sample_index=0;          // ����ѭ��������
    unsigned char channel_index=0;         // ͨ��ѭ��������
    
    // �ɼ�5������
    for (sample_index = 0; sample_index < 5; sample_index++) 
    {
        raw_adc_data[0][sample_index] = adc_convert(ADC_CH14_P06);
        raw_adc_data[1][sample_index] = adc_convert(ADC_CH13_P05);
        raw_adc_data[2][sample_index] = adc_convert(ADC_CH9_P01);
        raw_adc_data[3][sample_index] = adc_convert(ADC_CH0_P10);
    }
    
    // �˲�����
    for (channel_index = 0; channel_index < 4; channel_index++) 
    {
        filtered_adc[channel_index] = adc_filter(raw_adc_data[channel_index], 5);
    }
	/*���ݲ���*/
	ADC_1 = (float)(filtered_adc[0]*1.0f);
	ADC_2 = (float)(filtered_adc[1]*1.0f);
	ADC_3 = (float)(filtered_adc[2]*1.0f);
	ADC_4 = (float)(filtered_adc[3]*1.0f);
}


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