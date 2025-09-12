#ifndef __ADC_GET_H__
#define __ADC_GET_H__

#include "zf_common_headfile.h"

#define VREFH_ARR CHIPID7
#define VREFL_ARR CHIPID8

extern unsigned int raw_adc_data[4][5];    //ԭʼ��������
extern unsigned int filtered_adc[4];       // �˲����ADCֵ����

/*�ⲿ���ú���*/
void ADC_GetInit(void);
unsigned int battery_get(void);
void ADC_SampleAndFilter(void);

/*�ڲ����ú���*/
unsigned int adc_filter(unsigned int *samples, unsigned char count);


#endif