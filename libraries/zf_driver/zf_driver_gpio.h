
#ifndef __ZF_DRIVER_GPIO_H
#define __ZF_DRIVER_GPIO_H

#include "zf_common_typedef.h"


typedef enum
{
    IO_P00 = 0x10, IO_P01, IO_P02, IO_P03, IO_P04, IO_P05, IO_P06, IO_P07,
    IO_P10 = 0x20, IO_P11, IO_P12, IO_P13, IO_P14, IO_P15, IO_P16, IO_P17,
    IO_P20 = 0x30, IO_P21, IO_P22, IO_P23, IO_P24, IO_P25, IO_P26, IO_P27,
    IO_P30 = 0x40, IO_P31, IO_P32, IO_P33, IO_P34, IO_P35, IO_P36, IO_P37,
    IO_P40 = 0x50, IO_P41, IO_P42, IO_P43, IO_P44, IO_P45, IO_P46, IO_P47,
    IO_P50 = 0x60, IO_P51, IO_P52, IO_P53, IO_P54, IO_P55, IO_P56, IO_P57,
//    IO_P60 = 0x70, IO_P61, IO_P62, IO_P63, IO_P64, IO_P65, IO_P66, IO_P67,
//    IO_P70 = 0x80, IO_P71, IO_P72, IO_P73, IO_P74, IO_P75, IO_P76, IO_P77,
	IO_NULL = 0xFF,
} gpio_pin_enum;


typedef enum
{
    // ����
	GPI_IMPEDANCE       = 0x00,			// ��������
    GPI_FLOATING_IN     = 0x01,         // ��������ģʽ
    GPI_PULL_DOWN       = 0x02,         // ��������
    GPI_PULL_UP         = 0x03,         // ��������
	
	
    // ���
    GPO_PUSH_PULL       = 0x10,         // ͨ���������ģʽ
    GPO_OPEN_DTAIN      = 0x11,         // ͨ�ÿ�©���ģʽ
	
	// ˫��GPIO���ȿ�������Ҳ�������
	GPIO_NO_PULL   		= 0x20,			// GPIO����������
}gpio_mode_enum;

typedef enum
{
    //pnm1 pnm0

	GPI  = 0,				// ���룬����������
	GPO  = 1,				// �����������������߿�©
	GPIO = 2,				// ׼˫���(������)
}gpio_dir_enum;


typedef enum
{
    GPIO_LOW  = 0,  		//  �͵�ƽ
    GPIO_HIGH = 1,  		//  �ߵ�ƽ
}gpio_level_enum;


typedef enum
{
    GPIO_SPEED_LOW  = 1,  	// ��ƽת���ٶȿ죬��Ӧ�����³�Ƚϴ�
    GPIO_SPEED_FAST = 0,  	// ��ƽת���ٶ�������Ӧ�����³�Ƚ�С
}gpio_speed_enum;


//-------------------------------------------------------------------------------------------------------------------
// �������     ��Ӧ IO ��λΪ�͵�ƽ
// ����˵��     x           ѡ������� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     gpio_low(D5);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define gpio_low(x)            	gpio_set_level(x, 0)

//-------------------------------------------------------------------------------------------------------------------
// �������     ��Ӧ IO ��λΪ�ߵ�ƽ
// ����˵��     x           ѡ������� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     gpio_high(D5);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define gpio_high(x)            gpio_set_level(x, 1)

void 	gpio_set_level_speed	(gpio_pin_enum pin, gpio_speed_enum speed);

void    gpio_set_level          (gpio_pin_enum pin, uint8 dat);
uint8   gpio_get_level          (gpio_pin_enum pin);
void    gpio_toggle_level       (gpio_pin_enum pin);
void    gpio_init               (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode);


#endif
