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
#include "zf_driver_gpio.h"






// �ڲ�ʹ�ã��û�������ġ�
static void gpio_set_mode(gpio_pin_enum pin, gpio_mode_enum mode)
{
	#define PXPU(pin)  (*(unsigned char volatile far *)(0x7efe10 + (pin >> 4 - 1)))
	#define PXPD(pin)  (*(unsigned char volatile far *)(0x7efe40 + (pin >> 4 - 1)))

	
    if(GPI_FLOATING_IN == mode || GPIO_NO_PULL == mode)
    {
        PXPU(pin) &= ~(1 << (pin & 0x0F));
        PXPD(pin) &= ~(1 << (pin & 0x0F));
    }
    else if(GPI_PULL_DOWN == mode)
    {
        PXPD(pin) |= (1 << (pin & 0x0F));
    }
    else if(GPI_PULL_UP == mode || GPO_PUSH_PULL == mode)
    {
        PXPU(pin) |= (1 << (pin & 0x0F));
    }
	else if(GPO_OPEN_DTAIN == mode)
	{
		switch(pin & 0xF0)
		{
			case IO_P00:
			{
                P0M1 |= (1 << (pin & 0xF));
                P0M0 |= (1 << (pin & 0xF));
			}
			break;

			case IO_P10:
			{
				P1M1 |= (1 << (pin & 0xF));
                P1M0 |= (1 << (pin & 0xF));
			}
			break;
			
			case IO_P20:
			{
				P2M1 |= (1 << (pin & 0xF));
                P2M0 |= (1 << (pin & 0xF));
			}
			break;
			
			case IO_P30:
			{
				P3M1 |= (1 << (pin & 0xF));
                P3M0 |= (1 << (pin & 0xF));
			}
			break;
			
			case IO_P40:
			{
				P4M1 |= (1 << (pin & 0xF));
                P4M0 |= (1 << (pin & 0xF));
			}
			break;
			
			case IO_P50:
			{
				P5M1 |= (1 << (pin & 0xF));
                P5M0 |= (1 << (pin & 0xF));
			}
			break;
			default:
			{
			}	
			break;
		}
	}
	else
	{
		zf_assert(0);
		// ������ƥ��
	}
}

// �ڲ�ʹ�ã��û�������ġ�
void gpio_set_level_speed(gpio_pin_enum pin, gpio_speed_enum speed)
{
    switch(pin & 0xF0)
    {
        case IO_P00:
        {
            if(GPIO_SPEED_FAST == speed)
            {
				P0SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P0SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        case IO_P10:
        {
            if(GPIO_SPEED_FAST == speed)
            {
				P1SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P1SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        case IO_P20:
        {
            if(GPIO_SPEED_FAST == speed)
            {
				P2SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P2SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        case IO_P30:
        {
            if(GPIO_SPEED_FAST == speed)
            {
				P3SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P3SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        case IO_P40:
        {
			if(GPIO_SPEED_FAST == speed)
            {
				P4SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P4SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        case IO_P50:
        {
            if(GPIO_SPEED_FAST == speed)
            {
				P5SR &= ~(1<<(pin & 0x0F));
            }
            else if(GPIO_SPEED_LOW == speed)
            {
				P5SR |= (1<<(pin & 0x0F));
            }
			else
			{
				zf_assert(0);
				// û���������
			}
        }
        break;
        
        default:
        {
			zf_assert(0);
			// û���������
        } break;
    }
}


// �ڲ�ʹ�ã��û�������ġ�
static void gpio_set_dir(gpio_pin_enum pin, gpio_dir_enum dir)
{
    switch(pin & 0xF0)
    {
        case IO_P00:
        {
            if(GPIO == dir)
            {
                P0M1 &= ~(1 << (pin & 0xF));
                P0M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P0M1 |= (1 << (pin & 0xF));
//                P0M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P0M1 &= ~(1 << (pin & 0xF));
                P0M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P0M1 |= (1 << (pin & 0xF));
                P0M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        case IO_P10:
        {
            if(GPIO == dir)
            {
                P1M1 &= ~(1 << (pin & 0xF));
                P1M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P1M1 |= (1 << (pin & 0xF));
//                P1M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P1M1 &= ~(1 << (pin & 0xF));
                P1M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P1M1 |= (1 << (pin & 0xF));
                P1M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        case IO_P20:
        {
            if(GPIO == dir)
            {
                P2M1 &= ~(1 << (pin & 0xF));
                P2M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P2M1 |= (1 << (pin & 0xF));
//                P2M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P2M1 &= ~(1 << (pin & 0xF));
                P2M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P2M1 |= (1 << (pin & 0xF));
                P2M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        case IO_P30:
        {
            if(GPIO == dir)
            {
                P3M1 &= ~(1 << (pin & 0xF));
                P3M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P3M1 |= (1 << (pin & 0xF));
//                P3M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P3M1 &= ~(1 << (pin & 0xF));
                P3M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P3M1 |= (1 << (pin & 0xF));
                P3M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        case IO_P40:
        {
            if(GPIO == dir)
            {
                P4M1 &= ~(1 << (pin & 0xF));
                P4M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P4M1 |= (1 << (pin & 0xF));
//                P4M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P4M1 &= ~(1 << (pin & 0xF));
                P4M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P4M1 |= (1 << (pin & 0xF));
                P4M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        case IO_P50:
        {
            if(GPIO == dir)
            {
                P5M1 &= ~(1 << (pin & 0xF));
                P5M0 &= ~(1 << (pin & 0xF));
            }
//            else if(GPO_OPEN_DTAIN == dir)
//            {
//                P5M1 |= (1 << (pin & 0xF));
//                P5M0 |= (1 << (pin & 0xF));
//            }
            else if(GPO == dir)
            {
                P5M1 &= ~(1 << (pin & 0xF));
                P5M0 |= (1 << (pin & 0xF));
            }
            else if(GPI == dir)
            {
                P5M1 |= (1 << (pin & 0xF));
                P5M0 &= ~(1 << (pin & 0xF));
            }
        }
        break;
        
        default:
        {
			zf_assert(0);
			// û���������
        } break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO״̬��ȡ
// ����˵��     pin         ѡ������� (��ѡ��Χ�� zf_driver_gpio.h ��gpio_pin_enumö��ֵȷ��)
// ���ز���     uint8       0���͵�ƽ 1���ߵ�ƽ
// ʹ��ʾ��     uint8 status = gpio_get_level(IO_P00);//��ȡP00���ŵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_pin_enum pin)
{
    uint8 status = 0;
    
    switch(pin & 0xF0)
    {
        case IO_P00:
        {
            status = P0 & (1 << (pin & 0x0F));
        }
        break;
        
        case IO_P10:
        {
            status = P1 & (1 << (pin & 0x0F));
        }
        break;
        
        case IO_P20:
        {
            status = P2 & (1 << (pin & 0x0F));
        }
        break;
        
        case IO_P30:
        {
            status = P3 & (1 << (pin & 0x0F));
        }
        break;
        
        case IO_P40:
        {
            status = P4 & (1 << (pin & 0x0F));
        }
        break;
        
        case IO_P50:
        {
            status = P5 & (1 << (pin & 0x0F));
        }
        break;
        
        default:
        {
			zf_assert(0);
			// û���������
        } break;
    }
    
    return status ? 1 : 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO�������
// ����˵��     pin         ���ź�ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ����˵��     dat         ���ŵĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// ���ز���     void
// ʹ��ʾ��     gpio_set_level(D0, 0);//D0����͵�ƽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_pin_enum pin, uint8 dat)
{
    switch(pin & 0xF0)
    {
        case IO_P00:
        {
			if(dat)
			{
				P0 |= (1 << (pin & 0x0F));
			}
			else
			{
				P0 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        case IO_P10:
        {
			if(dat)
			{
				P1 |= (1 << (pin & 0x0F));
			}
			else
			{
				P1 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        case IO_P20:
        {
			if(dat)
			{
				P2 |= (1 << (pin & 0x0F));
			}
			else
			{
				P2 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        case IO_P30:
        {
			if(dat)
			{
				P3 |= (1 << (pin & 0x0F));
			}
			else
			{
				P3 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        case IO_P40:
        {
			if(dat)
			{
				P4 |= (1 << (pin & 0x0F));
			}
			else
			{
				P4 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        case IO_P50:
        {
			if(dat)
			{
				P5 |= (1 << (pin & 0x0F));
			}
			else
			{
				P5 &= ~(1 << (pin & 0x0F));
			}
        }
        break;
        
        default:
        {
			zf_assert(0);
			// û���������
        } break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO�������
// ����˵��     pin         ���ź�ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ����˵��     dat         ���ŵĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// ���ز���     void
// ʹ��ʾ��     gpio_set_level(D0, 0);//D0����͵�ƽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_pin_enum pin)
{
	if(gpio_get_level(pin))
	{
		gpio_low(pin);
	}
	else
	{
		gpio_high(pin);
	}
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO���ø�������
// ����˵��     pin         ���ź�ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_impedance(gpio_pin_enum pin)
{
    switch(pin & 0xF0)
    {
        case IO_P00:
        {
			P0M1 |=  (1 << (pin & 0xF));
			P0M0 &= ~(1 << (pin & 0xF));
        }
        break;
        
        case IO_P10:
        {
			P1M1 |=  (1 << (pin & 0xF));
			P1M0 &= ~(1 << (pin & 0xF));
        }
        break;
        
        case IO_P20:
        {
			P2M1 |=  (1 << (pin & 0xF));
			P2M0 &= ~(1 << (pin & 0xF));;
        }
        break;
        
        case IO_P30:
        {
			P3M1 |=  (1 << (pin & 0xF));
			P3M0 &= ~(1 << (pin & 0xF));
        }
        break;
        
        case IO_P40:
        {
			P4M1 |=  (1 << (pin & 0xF));
			P4M0 &= ~(1 << (pin & 0xF));
        }
        break;
        
        case IO_P50:
        {
			P5M1 |=  (1 << (pin & 0xF));
			P5M0 &= ~(1 << (pin & 0xF));
        }
        break;
        
        default:
        {
			zf_assert(0);
			// û���������
        } break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO��ʼ��
// ����˵��     pin         ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ����˵��     dir         ���ŵķ���   �����GPO   ���룺GPI
// ����˵��     dat         ���ų�ʼ��ʱ���õĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// ����˵��     pinconf     �������ã������ò�����zf_gpio.h�ļ���GPIOSPEED_enum��GPIOMODE_enumö��ֵȷ�����������ʹ�� | ���
// ���ز���     void
// ʹ��ʾ��     gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);//D0��ʼ��ΪGPIO���ܡ����ģʽ������ߵ�ƽ���ٶ�100MHZ �������
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode)
{
	zf_assert(dir == (mode >> 4));

	if(dir == GPIO)
	{
		gpio_set_dir(pin, GPIO);
		gpio_set_mode(pin, mode);
	}
	else if(dir == GPI)
	{
		if(mode == GPI_IMPEDANCE)
		{
			gpio_set_impedance(pin);
		}
		else
		{
			gpio_set_dir(pin, GPI);
			gpio_set_mode(pin, mode);
		}
	}
	else if(dir == GPO)
	{
		if(GPO_PUSH_PULL == mode)
		{
			gpio_set_dir(pin, GPO);
			gpio_set_mode(pin, GPI_PULL_UP);
		}
		else if(GPO_OPEN_DTAIN == mode)
		{
			gpio_set_mode(pin, GPO_OPEN_DTAIN);
		}
	}
	gpio_set_level(pin, dat);
}

