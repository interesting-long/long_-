#ifndef __ADC_GET_H__
#define __ADC_GET_H__

#include "zf_common_headfile.h"

#define VREFH_ARR CHIPID7
#define VREFL_ARR CHIPID8

extern unsigned int raw_adc_data[4][5];    //原始数据数组
extern unsigned int filtered_adc[4];       // 滤波后的ADC值数组

/*外部调用函数*/
void ADC_GetInit(void);
unsigned int battery_get(void);
void ADC_SampleAndFilter(void);

/*内部调用函数*/
unsigned int adc_filter(unsigned int *samples, unsigned char count);


#endif