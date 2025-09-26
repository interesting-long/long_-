#ifndef __ADC_GET_H__
#define __ADC_GET_H__

#include "zf_common_headfile.h"

#define VREFH_ARR CHIPID7
#define VREFL_ARR CHIPID8

//#define ADC1_PIN ADC_CH8_P00
//#define ADC2_PIN ADC_CH0_P10
//#define ADC3_PIN ADC_CH2_P12
//#define ADC4_PIN ADC_CH4_P14

#define ADC1_PIN ADC_CH7_P17
#define ADC2_PIN ADC_CH6_P16
#define ADC3_PIN ADC_CH4_P14
#define ADC4_PIN ADC_CH2_P12
//#define ADC5_PIN ADC_CH2_P12
//#define ADC6_PIN ADC_CH1_P11
//#define ADC7_PIN ADC_CH2_P12
//#define ADC8_PIN ADC_CH8_P00
extern unsigned int raw_adc_data[4][5];    //原始数据数组
extern unsigned int filtered_adc[4];       // 滤波后的ADC值数组

/*外部调用函数*/
void ADC_GetInit(void);
unsigned int battery_get(void);
void ADC_SampleAndFilter(void);
/*内部调用函数*/
unsigned int adc_filter(unsigned int *samples, unsigned char count);
//void ADC_ALL_GET();

#endif