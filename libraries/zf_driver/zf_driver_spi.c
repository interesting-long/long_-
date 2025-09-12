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
#pragma warning disable = 47

#include "zf_common_debug.h"
#include "zf_common_clock.h"
#include "zf_driver_gpio.h"
#include "zf_driver_spi.h"

#pragma warning disable = 183
#pragma warning disable = 177

/*
#define SPI0_WRITE_DAT(dat) 		\
		SPSTAT = 0xc0;              \
		SPDAT = dat;				\
		while (!(SPSTAT & 0x80));

#define SPI1_WRITE_DAT(dat) 		\
		TI = 0x0;              		\
		SBUF = dat;					\
		while (!TI)

#define SPI2_WRITE_DAT(dat) 		\
		S2TI = 0x0;              	\
		S2BUF = dat;				\
		while (!S2TI)
		
#define SPI_WRITE_DAT(spi_n, dat)	\
	switch (spi_n)					\
	{                               \
		case SPI_0:                 \
			SPI0_WRITE_DAT(dat);    \
			break;                  \
		case SPI_1:                 \
			SPI1_WRITE_DAT(dat);    \
			break;                  \
		case SPI_2:                 \
			SPI2_WRITE_DAT(dat);    \
			break;                  \
		default:                    \
			zf_assert(0);           \
			break;                  \
	}

*/

#define SPI_WRITE_DAT(spi_n, dat) spi_write_dat(spi_n, dat)
void spi_write_dat(spi_index_enum spi_n, const uint8 dat)
{
	switch (spi_n)					
	{                               
		case SPI_0:                 
			SPSTAT = 0xc0;              
			SPDAT = dat;				
			while (!(SPSTAT & 0x80));  
			break;
		case SPI_1:                 
			TI = 0x0;              		
			SBUF = dat;					
			while (!TI);
			break;                  
		case SPI_2:
			S2TI = 0x0;              	
			S2BUF = dat;				
			while (!S2TI);
			break;          
		default:                    
			zf_assert(0);           
			break;                  
	}
}
	
#define SPI_READ_DAT(spi_n, dat) spi_read_dat(spi_n, dat)
uint8 spi_read_dat(spi_index_enum spi_n, const uint8 dat)
{
	uint8 ret = 0xFF;
	switch (spi_n)					
	{                               
		case SPI_0:                 
			SPSTAT = 0xc0;              
			SPDAT = dat;				
			while (!(SPSTAT & 0x80));  
			ret = SPDAT;
			break;
		case SPI_1:                 
			TI = 0x0;              		
			SBUF = dat;					
			while (!TI);
			ret = SBUF;
			break;                  
		case SPI_2:
			S2TI = 0x0;              	
			S2BUF = dat;				
			while (!S2TI);
			ret = S2BUF;
			break;          
		default:                    
			zf_assert(0);           
			break;                  
	}
	
	return ret;
}



//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit(SPI_1,0x11);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit (spi_index_enum spi_n, const uint8 dat)
{
	SPI_WRITE_DAT(spi_n, dat);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_array (spi_index_enum spi_n, const uint8 *dat, uint32 len)
{
	while(len--)
	{
		SPI_WRITE_DAT(spi_n, *dat++);
	}
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit(SPI_1,0x1101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit (spi_index_enum spi_n, const uint16 dat)
{
	SPI_WRITE_DAT(spi_n, (uint8)((dat & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(dat & 0x00FF));
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_array (spi_index_enum spi_n, const uint16 *dat, uint32 len)
{
    while(len--)
    {
		SPI_WRITE_DAT(spi_n, (uint8)((*dat & 0xFF00) >> 8));
		SPI_WRITE_DAT(spi_n, (uint8)(*dat++ & 0x00FF));
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_register(SPI_1,0x11,0x01);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_register (spi_index_enum spi_n, const uint8 register_name, const uint8 dat)
{
	SPI_WRITE_DAT(spi_n, register_name);
	SPI_WRITE_DAT(spi_n, dat);
}


//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_registers (spi_index_enum spi_n, const uint8 register_name, const uint8 *dat, uint32 len)
{
	SPI_WRITE_DAT(spi_n, register_name);
    while(len--)
    {
		SPI_WRITE_DAT(spi_n, *dat++);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SPI �ӿ��򴫸����ļĴ���д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_register(SPI_1,0x1011,0x0101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_register (spi_index_enum spi_n, const uint16 register_name, const uint16 dat)
{
	SPI_WRITE_DAT(spi_n, (uint8)((register_name & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(register_name & 0x00FF));
	SPI_WRITE_DAT(spi_n, (uint8)((dat & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(dat & 0x00FF));
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_registers(SPI_1,0x1011,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_registers (spi_index_enum spi_n, const uint16 register_name, const uint16 *dat, uint32 len)
{
	SPI_WRITE_DAT(spi_n, (uint8)((register_name & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(register_name & 0x00FF));
	SPI_WRITE_DAT(spi_n, (uint8)((*dat & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(*dat++ & 0x00FF));
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint8         ����
// ʹ��ʾ��     spi_read_8bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit (spi_index_enum spi_n)
{
    return SPI_READ_DAT(spi_n, 0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_array (spi_index_enum spi_n, uint8 *dat, uint32 len)
{
    while(len--)
    {
        *dat++ = SPI_READ_DAT(spi_n, 0);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint16        ����
// ʹ��ʾ��     spi_read_16bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit (spi_index_enum spi_n)
{
    uint16 dat = 0;

    dat = SPI_READ_DAT(spi_n, 0);

    dat = ((dat << 8) | SPI_READ_DAT(spi_n, 0));
    
    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_array (spi_index_enum spi_n, uint16 *dat, uint32 len)
{
    while(len--)
    {
        *dat = SPI_READ_DAT(spi_n, 0);
        *dat = ((*dat << 8) | SPI_READ_DAT(spi_n, 0));
        dat++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint8         ����
// ʹ��ʾ��     spi_read_8bit_register(SPI_1,0x11);
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit_register (spi_index_enum spi_n, const uint8 register_name)
{
	SPI_WRITE_DAT(spi_n, register_name);
    return SPI_READ_DAT(spi_n, 0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_registers (spi_index_enum spi_n, const uint8 register_name, uint8 *dat, uint32 len)
{
	SPI_WRITE_DAT(spi_n, register_name);
    while(len--)
    {
        *dat++ = SPI_READ_DAT(spi_n, 0);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint16        ����
// ʹ��ʾ��     spi_read_16bit_register(SPI_1,0x1011);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit_register (spi_index_enum spi_n, const uint16 register_name)
{
    uint16 dat = 0;
    
	SPI_WRITE_DAT(spi_n, (uint8)((register_name & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(register_name & 0x00FF));
	
	dat = SPI_READ_DAT(spi_n, 0);
	dat = ((dat << 8) |  SPI_READ_DAT(spi_n, 0));

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *dat           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_16bit_registers(SPI_1,0x1101,dat,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_registers (spi_index_enum spi_n, const uint16 register_name, uint16 *dat, uint32 len)
{
	SPI_WRITE_DAT(spi_n, (uint8)((register_name & 0xFF00) >> 8));
	SPI_WRITE_DAT(spi_n, (uint8)(register_name & 0x00FF));
    
    while(len--)
    {
		*dat = SPI_READ_DAT(spi_n, 0);
		*dat = ((*dat << 8) |  SPI_READ_DAT(spi_n, 0));
        dat++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI 8bit ���ݴ��� ���������������ͬʱ���е�
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     write_buffer    ���͵����ݻ�������ַ
// ����˵��     read_buffer     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_transfer_8bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_8bit (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len)
{
    while(len--)
    {
        if(read_buffer != NULL)
        {
            *read_buffer++ = SPI_READ_DAT(spi_n, *(write_buffer++));
        }
		else
		{
			SPI_WRITE_DAT(spi_n, *(write_buffer++));
		}
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI 16bit ���ݴ��� ���������������ͬʱ���е�
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     write_buffer    ���͵����ݻ�������ַ
// ����˵��     read_buffer     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_transfer_16bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_16bit (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len)
{
    while(len--)
    {
		if(read_buffer != NULL)
        {
            *read_buffer = SPI_READ_DAT(spi_n, (uint8)((*write_buffer & 0xFF00) >> 8));
			*read_buffer = *read_buffer << 8 | (uint8)(SPI_READ_DAT(spi_n, (*write_buffer & 0x00FF)));
			read_buffer++;
        }
		else
		{
			SPI_WRITE_DAT(spi_n, (uint8)((*write_buffer & 0xFF00) >> 8));
			SPI_WRITE_DAT(spi_n, (uint8)(*write_buffer & 0x00FF));
		}
        write_buffer++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SPI �ӿڳ�ʼ��
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     mode            SPI ģʽ ���� zf_driver_spi.h �� spi_mode_enum ö���嶨��
// ����˵��     baud            ���� SPI �Ĳ����� ������ϵͳʱ�ӵ�һ�� �������ʻᱻ��������������
// ����˵��     sck_pin         ѡ�� SCK ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     mosi_pin        ѡ�� MOSI ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     miso_pin        ѡ�� MISO ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     cs_pin          ѡ�� CS ���� ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_A5, SPI1_MOSI_A7, SPI1_MISO_A6, A4);  //Ӳ��SPI��ʼ��  ģʽ0 ������Ϊ1Mhz
//-------------------------------------------------------------------------------------------------------------------
void spi_init(spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_pin_enum sck_pin, spi_pin_enum mosi_pin, spi_pin_enum miso_pin, gpio_pin_enum cs_pin)
{
    uint32 spi_psc = 0;
    
    if((sck_pin & 0xFF00) != (mosi_pin & 0xFF00))
    {
        zf_assert(0);
        // SPIֻ��ʹ��ͬһ�����ţ��������������
    }
    
    gpio_init(sck_pin  & 0xFF, GPO, 1, GPO_PUSH_PULL);
    gpio_init(mosi_pin & 0xFF, GPO, 1, GPO_PUSH_PULL);
    
    if(miso_pin != SPI_NULL_PIN)
    {
        gpio_init(miso_pin & 0xFF, GPIO, 1, GPIO_NO_PULL);
    }
    
    if(cs_pin != SPI_NULL_PIN)
    {
        gpio_init(cs_pin & 0xFF, GPO, 0, GPO_PUSH_PULL);
    }

	// �����ʴ��ڵ���10M����Ҫ����GPIO��ƽת���ٶ�
	if(baud >= (10*1000*1000U))
	{
		gpio_set_level_speed(sck_pin  & 0xFF, GPIO_SPEED_FAST);
		gpio_set_level_speed(mosi_pin  & 0xFF, GPIO_SPEED_FAST);
		if(miso_pin != SPI_NULL_PIN)
		{
			gpio_set_level_speed(miso_pin & 0xFF, GPIO_SPEED_FAST);
		}
		if(cs_pin != SPI_NULL_PIN)
		{
			gpio_set_level_speed(cs_pin & 0xFF, GPIO_SPEED_FAST);
		}
	}
    
    if(SPI_0 == spi_n)
    {
        P_SW1 &= ~(0x03 << 2); //���SPI���ܽ�ѡ��λ
        
        switch((sck_pin >> 8) & 0x03)
        {
            case 0:
                P_SW1 |= (0x00 << 2);
                break;
                
            case 1:
                P_SW1 |= (0x01 << 2);
                break;
                
            case 2:
                P_SW1 |= (0x02 << 2);
                break;
                
            case 3:
                P_SW1 |= (0x03 << 2);
                break;
        }
        
        SPCTL = 0;
        SPCTL |= 1 << 7;	//����SS���Ź��ܣ�ʹ��MSTRȷ���������������Ǵӻ�
        SPCTL |= 1 << 4;	//����ģʽ
        
        // ����SPI����
        spi_psc = system_clock / baud;
		
        SPCTL &= ~(0x03 << 0);
		
		if(spi_psc > 8)
        {
            SPCTL |= 0x02;	// SPI����ʱ��/16
        }
        else if(spi_psc > 4)
        {
            SPCTL |= 0x01;	// SPI����ʱ��/8
        }
        else if(spi_psc > 2)
        {
            SPCTL |= 0x00;	// SPI����ʱ��/4
        }
        else
        {
            SPCTL |= 0x03;	// SPI����ʱ��/2
        }
		
        // ����SPI���Ժ���λ
        switch(mode)
        {
            case SPI_MODE0:
                break;
                
            case SPI_MODE1:
                SPCTL |= 0x01 << 2;
                break;
                
            case SPI_MODE2:
                SPCTL |= 0x02 << 2;
                break;
                
            case SPI_MODE3:
                SPCTL |= 0x03 << 2;
                break;
        }
        
        SPCTL |= 1 << 6;	// ʹ��SPI����
    }
    else if(SPI_1 == spi_n)
    {
		
		// �������������˶�����Ϣ ������ʾ����λ��������
		// ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
		// �����Ǽ���Ƿ����ظ�ʹ��UART1 �� UART2����
		// �����ʼ���� UART1 Ȼ���ֳ�ʼ���� SPI1 �����÷��ǲ������
		// UART1��SPI1ʹ��ͬһ���Ĵ�����Ҫô��UART1Ҫôʹ��SPI1,ֻ���Ƕ�ѡһ��
		// UART2��SPI2ʹ��ͬһ���Ĵ�����Ҫô��UART2Ҫôʹ��SPI2,ֻ���Ƕ�ѡһ��
		zf_assert(uart_funciton_check(UART_1, UART_FUNCTION_SPI));
		
		
        P_SW3 &= ~(0x03 << 2); //���SPI���ܽ�ѡ��λ
        
        switch((sck_pin >> 8) & 0x03)
        {
            case 0:
                P_SW3 |= (0x00 << 2);
                break;
                
            case 1:
                P_SW3 |= (0x01 << 2);
                break;
                
            case 2:
                P_SW3 |= (0x02 << 2);
                break;
                
            case 3:
                P_SW3 |= (0x03 << 2);
                break;
        }
        
        SCON = 0x10;		// ����ʹ��
        USARTCR1 = 0x10; 	// ʹ��SPIģʽ����������
        
        
        // ����SPI����
        spi_psc = system_clock / baud;
        

		
        if(spi_psc > 8)
        {
            USARTCR4 |= 0x02;	// SPI����ʱ��/16
        }
        else if(spi_psc > 4)
        {
            USARTCR4 |= 0x01;	// SPI����ʱ��/8
        }
        else if(spi_psc > 2)
        {
            USARTCR4 |= 0x00;	// SPI����ʱ��/4
        }
        else
        {
            USARTCR4 |= 0x03;	// SPI����ʱ��/2
        }
        
        
        // ����SPI���Ժ���λ
        switch(mode)
        {
            case SPI_MODE0:
                USARTCR1 |= 0x00;
                break;
                
            case SPI_MODE1:
                USARTCR1 |= 0x01;
                break;
                
            case SPI_MODE2:
                USARTCR1 |= 0x02;
                break;
                
            case SPI_MODE3:
                USARTCR1 |= 0x03;
                break;
        }
        
        USARTCR1 |= 0x08; // ʹ��SPI����
    }
    else if(SPI_2 == spi_n)
    {
		
		// �������������˶�����Ϣ ������ʾ����λ��������
		// ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
		// �����Ǽ���Ƿ����ظ�ʹ��UART1 �� UART2����
		// �����ʼ���� UART1 Ȼ���ֳ�ʼ���� SPI1 �����÷��ǲ������
		// UART1��SPI1ʹ��ͬһ���Ĵ�����Ҫô��UART1Ҫôʹ��SPI1,ֻ���Ƕ�ѡһ��
		// UART2��SPI2ʹ��ͬһ���Ĵ�����Ҫô��UART2Ҫôʹ��SPI2,ֻ���Ƕ�ѡһ��
		zf_assert(uart_funciton_check(UART_2, UART_FUNCTION_SPI));

        P_SW3 &= ~(0x03 << 4); //���SPI���ܽ�ѡ��λ
        
        switch((sck_pin >> 8) & 0x03)
        {
            case 0:
                P_SW3 |= (0x00 << 4);
                break;
                
            case 1:
                P_SW3 |= (0x01 << 4);
                break;
                
            case 2:
                P_SW3 |= (0x02 << 4);
                break;
                
            case 3:
                P_SW3 |= (0x03 << 4);
                break;
        }
        
        S2CON = 0x10;		// ����ʹ��
        USART2CR1 = 0x10;	// ʹ��SPIģʽ����������
        
        
        // ����SPI����
        spi_psc = system_clock / baud;

        if(spi_psc > 8)
        {
            USART2CR4 |= 0x02;	// SPI����ʱ��/16
        }
        else if(spi_psc > 4)
        {
            USART2CR4 |= 0x01;	// SPI����ʱ��/8
        }
        else if(spi_psc > 2)
        {
            USART2CR4 |= 0x00;	// SPI����ʱ��/4
        }
        else
        {
            USART2CR4 |= 0x03;	// SPI����ʱ��/2
        }
        
        
        // ����SPI���Ժ���λ
        switch(mode)
        {
            case SPI_MODE0:
                USART2CR1 |= 0x00;
                break;
                
            case SPI_MODE1:
                USART2CR1 |= 0x01;
                break;
                
            case SPI_MODE2:
                USART2CR1 |= 0x02;
                break;
                
            case SPI_MODE3:
                USART2CR1 |= 0x03;
                break;
        }
        
        USART2CR1 |= 0x08; // ʹ��SPI����
    }
}



