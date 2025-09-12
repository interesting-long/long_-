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
#include "zf_common_debug.h"

#include "zf_driver_pwm.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"




// ����Ƚ�ģʽ�Ĵ���
const uint32 PWM_CCMR_ADDR[] = {0x7efec8, 0x7efec9, 0x7efeca, 0x7efecb,
                                0x7efee8, 0x7efee9, 0x7efeea, 0x7efeeb
                               };

// ����Ƚ�ʹ�ܼĴ���
const uint32 PWM_CCER_ADDR[] = {0x7efecc, 0x7efecd,		// PWMA_CCERX
                                0x7efeec, 0x7efeed
                               };	// PWMB_CCERX

// ���ƼĴ���,��8λ��ַ  ��8λ��ַ + 1����
const uint32 PWM_CCR_ADDR[] = {0x7efed5, 0x7efed7, 0x7efed9, 0x7efedb,
                               0x7efef5, 0x7efef7, 0x7efef9, 0x7efefb
                              };

// ���ƼĴ���,��8λ��ַ  ��8λ��ַ + 1����
const uint32 PWM_ARR_ADDR[] = {0x7efed2, 0x7efef2};

// Ԥ��Ƶ�Ĵ���,��8λ��ַ  ��8λ��ַ + 1����
const uint32 PWM_PSCR_ADDR[] = {0x7efed0, 0x7efef0};


#define PWMX_CCERX(pin)		(*(unsigned char volatile far *)(PWM_CCER_ADDR[((pin >> 12 & 0x02) >> 1) + ((pin >> 15 & 0x1) * 2)]))

#define PWMX_CCRXH(pin)		(*(unsigned char volatile far *)(PWM_CCR_ADDR[((pin >> 15 & 0x1) * 4) + (pin >> 12 & 0x7)]))
#define PWMX_CCRXL(pin)		(*(unsigned char volatile far *)(PWM_CCR_ADDR[((pin >> 15 & 0x1) * 4) + (pin >> 12 & 0x7)] + 1))

#define PWMX_ARRH(pin)		(*(unsigned char volatile far *)(PWM_ARR_ADDR[(pin >> 15 & 0x1) * 1]))
#define PWMX_ARRL(pin)		(*(unsigned char volatile far *)(PWM_ARR_ADDR[(pin >> 15 & 0x1) * 1] + 1))

#define PWMX_PSCRH(pin)		(*(unsigned char volatile far *)(PWM_PSCR_ADDR[(pin >> 15 & 0x1) * 1]))
#define PWMX_PSCRL(pin)		(*(unsigned char volatile far *)(PWM_PSCR_ADDR[(pin >> 15 & 0x1) * 1] + 1))

#define PWMX_CCMRX(pin)		(*(unsigned char volatile far *)(PWM_CCMR_ADDR[((pin >> 15 & 0x1) * 4) + (pin >> 12 & 0x7)]))


//-------------------------------------------------------------------------------------------------------------------
// �������     PWMƵ�ʺ�ռ�ձ�����
// ����˵��     pin           	PWMͨ���ż�����
// ����˵��     freq           	PWMƵ��
// ����˵��     duty            	PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_set_freq(PWMB_CH1_P01, 50, 1000);   //PWMB ʹ������P01 Ƶ��50HZ ռ�ձ�Ϊ�ٷ�֮ 1000/PWM_DUTY_MAX*100
//                              						PWM_DUTY_MAX��zf_driver_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_freq(pwm_channel_enum pin, uint32 freq, uint32 duty)
{
    uint32 match_temp = 0;
    uint32 period_temp = 0;
    uint16 freq_div = 0;
	
	// �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);
	
    //��Ƶ���㣬���ڼ��㣬ռ�ձȼ���
    freq_div = (system_clock / freq) >> 16;								// ���ٷ�Ƶ
    period_temp = system_clock / freq;
    period_temp = period_temp / (freq_div + 1) - 1;					// ����

    if(duty != PWM_DUTY_MAX)
    {
        match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);	// ռ�ձ�
    }
    else
    {
        match_temp = period_temp + 1;								// dutyΪ100%
	}

	PWMX_PSCRH(pin) = (uint8)(freq_div >> 8);	    // ����Ԥ��Ƶֵ
	PWMX_PSCRL(pin) = (uint8)freq_div;
	
	PWMX_ARRH(pin) = (uint8)(period_temp >> 8);		// ����ֵ ��8λ
	PWMX_ARRL(pin) = (uint8)period_temp;			// ����ֵ ��8λ

    PWMX_CCRXH(pin) = match_temp >> 8;				// �Ƚ�ֵ ��8λ
    PWMX_CCRXL(pin) = (uint8)match_temp;			// �Ƚ�ֵ ��8λ
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PWMռ�ձ��趨
// ����˵��     pwmch           PWMͨ���ż�����
// ����˵��     duty            PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_set_duty(PWMB_CH1_P01, 5000);   //PWMB ʹ������P01 ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              					PWM_DUTY_MAX��zf_driver_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty(pwm_channel_enum pin, uint32 duty)
{
    uint32 match_temp;
    uint32 arr = (PWMX_ARRH(pin) << 8) | PWMX_ARRL(pin);
	
	// �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);
	
    if(duty != PWM_DUTY_MAX)
    {
        match_temp = arr * ((float)duty / PWM_DUTY_MAX);				//ռ�ձ�
    }
    else
    {
        match_temp = arr + 1;
    }

    //���ò���ֵ|�Ƚ�ֵ
    PWMX_CCRXH(pin) = match_temp >> 8;				// �Ƚ�ֵ ��8λ
    PWMX_CCRXL(pin) = (uint8)match_temp;			// �Ƚ�ֵ ��8λ
	
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PWM��ʼ��
// ����˵��     pin				PWMͨ���ż�����
// ����˵��     freq            PWMƵ��
// ����˵��     duty            PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_init(PWMB_CH1_P01, 50, 5000);   //��ʼ��PWMB ʹ������P01  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              					PWM_DUTY_MAX��zf_driver_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(pwm_channel_enum pin, uint32 freq, uint32 duty)
{

    uint16 match_temp = 0;                                              // ռ�ձ�ֵ
    uint32 period_temp = 0;                                             // ����ֵ
    uint16 freq_div = 0;                                                // ��Ƶֵ
    
	// �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);
	
    gpio_init(pin  & 0xFF, GPO, 1, GPO_PUSH_PULL);							// GPIO��Ҫ����Ϊ�������
    
    
    //��Ƶ���㣬���ڼ��㣬ռ�ձȼ���
    freq_div = (system_clock / freq) >> 16;								// ��Ƶֵ
    period_temp = system_clock / freq;
    period_temp = period_temp / (freq_div + 1) - 1;						// ����ֵ
	
    if(duty != PWM_DUTY_MAX)
    {		
        match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);		// ռ�ձ�
    }
    else
    {
        match_temp = period_temp + 1;									// dutyΪ100%
    }

	PWMX_PSCRH(pin) = (uint8)(freq_div >> 8);	    // ����Ԥ��Ƶֵ
	PWMX_PSCRL(pin) = (uint8)freq_div;
	
	PWMX_ARRH(pin) = (uint8)(period_temp >> 8);		// ����ֵ ��8λ
	PWMX_ARRL(pin) = (uint8)period_temp;			// ����ֵ ��8λ

    PWMX_CCRXH(pin) = (uint8)(match_temp >> 8);		// �Ƚ�ֵ ��8λ
    PWMX_CCRXL(pin) = (uint8)match_temp;			// �Ƚ�ֵ ��8λ
	
    if(((pin >> 15) & 0x01) == 0)					// PWMA
    {
        PWMA_ENO |= 1 << ((((pin >> 12) & 0x07) * 2) + ((pin >> 11) & 0x01));		// ʹ��ͨ��
        PWMA_PS  |= ((pin >> 9) & 0x03) << (((pin >> 12) & 0x07) * 2);				// ѡ������
        PWMX_CCERX(pin) |= 1 << ((pin >> 12 & 0x01) * 4 + (pin >> 11 & 0x01) * 2);	// �����������

        PWMA_BKR = 0x80; 							// �����ʹ�� �൱���ܿ���
        PWMA_CR1 = 0x01;							// PWM��ʼ����
    }
    else if(((pin >> 15) & 0x01) == 1)				// PWMB
    {
        PWMB_ENO |= 1 << ((((pin >> 12) & 0x07) * 2) + ((pin >> 11) & 0x01));		// ʹ��ͨ��
        PWMB_PS  |= ((pin >> 9) & 0x03) << (((pin >> 12) & 0x07) * 2);				// ѡ������
        PWMX_CCERX(pin) |= 1 << ((pin >> 12 & 0x01) * 4);							// �����������

        PWMB_BKR = 0x80; 							// �����ʹ�� �൱���ܿ���
        PWMB_CR1 = 0x01;							// PWM��ʼ����
    }

	PWMX_CCMRX(pin) |= 0x06 << 4;					// ����ΪPWMģʽ1
	PWMX_CCMRX(pin) |= 1 << 3;						// ����PWM�Ĵ�����Ԥװ�ع�
}
