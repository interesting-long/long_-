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

#ifndef __ZF_DRIVER_SPI_H
#define __ZF_DRIVER_SPI_H
#include "zf_common_typedef.h"
#include "zf_driver_gpio.h"


// ��ö�����ֹ�û��޸�
typedef enum
{
    SPI_0 = 0,
    SPI_1,			// ��UART1������һ��Ĵ�����ʹ��ʱ��ֻ�ܶ�ѡһ
    SPI_2,			// ��UART2������һ��Ĵ�����ʹ��ʱ��ֻ�ܶ�ѡһ
    //����SS�������������
} spi_index_enum;


// ��ö�����ֹ�û��޸�
typedef enum
{
    // SPI_0 ֻ��ʹ��ͬһ�����ţ��������������
    SPI0_CH1_SCLK_P17 = 0x0000 | IO_P17,
    SPI0_CH1_MOSI_P15 = 0x0000 | IO_P15,
    SPI0_CH1_MISO_P16 = 0x0000 | IO_P16,
    
    // SPI_0 ֻ��ʹ��ͬһ�����ţ��������������
    SPI0_CH2_SCLK_P27 = 0x0100 | IO_P27,
    SPI0_CH2_MOSI_P25 = 0x0100 | IO_P25,
    SPI0_CH2_MISO_P26 = 0x0100 | IO_P26,
    
    // SPI_0 ֻ��ʹ��ͬһ�����ţ��������������
    SPI0_CH3_SCLK_P43 = 0x0200 | IO_P43,
    SPI0_CH3_MOSI_P41 = 0x0200 | IO_P41,
    SPI0_CH3_MISO_P42 = 0x0200 | IO_P42,
    
    // SPI_0 ֻ��ʹ��ͬһ�����ţ��������������
    SPI0_CH4_SCLK_P32 = 0x0300 | IO_P32,
    SPI0_CH4_MOSI_P34 = 0x0300 | IO_P34,
    SPI0_CH4_MISO_P33 = 0x0300 | IO_P33,
    
	
	// SPI1�봮��1���ã�Ҫôʹ�ô���1��Ҫôʹ��SPI1
	
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI1_CH1_SCLK_P17 = 0x1000 | IO_P17,
    SPI1_CH1_MOSI_P15 = 0x1000 | IO_P15,
    SPI1_CH1_MISO_P16 = 0x1000 | IO_P16,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI1_CH2_SCLK_P27 = 0x1100 | IO_P27,
    SPI1_CH2_MOSI_P25 = 0x1100 | IO_P25,
    SPI1_CH2_MISO_P26 = 0x1100 | IO_P26,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI1_CH3_SCLK_P43 = 0x1200 | IO_P43,
    SPI1_CH3_MOSI_P41 = 0x1200 | IO_P41,
    SPI1_CH3_MISO_P42 = 0x1200 | IO_P42,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI1_CH4_SCLK_P32 = 0x1300 | IO_P32,
    SPI1_CH4_MOSI_P34 = 0x1300 | IO_P34,
    SPI1_CH4_MISO_P33 = 0x1300 | IO_P33,
	
	
	// SPI2�봮��2���ã�Ҫôʹ�ô���2��Ҫôʹ��SPI2
	
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI2_CH1_SCLK_P17 = 0x2000 | IO_P17,
    SPI2_CH1_MOSI_P15 = 0x2000 | IO_P15,
    SPI2_CH1_MISO_P16 = 0x2000 | IO_P16,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI2_CH2_SCLK_P27 = 0x2100 | IO_P27,
    SPI2_CH2_MOSI_P25 = 0x2100 | IO_P25,
    SPI2_CH2_MISO_P26 = 0x2100 | IO_P26,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI2_CH3_SCLK_P43 = 0x2200 | IO_P43,
    SPI2_CH3_MOSI_P41 = 0x2200 | IO_P41,
    SPI2_CH3_MISO_P42 = 0x2200 | IO_P42,
    
    // SPI_1 ֻ��ʹ��ͬһ�����ţ��������������
    SPI2_CH4_SCLK_P32 = 0x2300 | IO_P32,
    SPI2_CH4_MOSI_P34 = 0x2300 | IO_P34,
    SPI2_CH4_MISO_P33 = 0x2300 | IO_P33,

	
    SPI_NULL_PIN = 0xFFFF,
	SPI_MISO_NULL = 0xFFFF,
	SPI_CS_NULL = 0xFFFF,
    //����CS�������������
} spi_pin_enum;


//��ö�����ֹ�û��޸�
typedef enum
{
    MASTER = 0,	 //����
    SLAVE, //�ӻ�
} SPI_MSTR_enum;

//��ö�����ֹ�û��޸�
typedef enum
{
    SPI_SYSclk_DIV_4 = 0,
    SPI_SYSclk_DIV_8,
    SPI_SYSclk_DIV_16,
    SPI_SYSclk_DIV_2,
} SPI_BAUD_enum;

typedef enum                                                                    // ö�� SPI ģʽ ��ö�ٶ��岻�����û��޸�
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;
//void spi_init(SPIN_enum spi_n,
//              SPI_PIN_enum sck_pin,
//              SPI_PIN_enum mosi_pin,
//              SPI_PIN_enum miso_pin,
//              uint8 mode,
//              SPI_MSTR_enum mstr,
//              SPI_BAUD_enum baud);

//void spi_change_pin(SPIN_enum spi_n,
//                    SPI_PIN_enum sck_pin,
//                    SPI_PIN_enum mosi_pin,
//                    SPI_PIN_enum miso_pin);

//void spi_change_mode(uint8 mode);

//uint8 spi_mosi(uint8 dat);

void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 dat);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *dat, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 dat);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *dat, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 dat);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *dat, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 dat);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *dat, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *dat, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *dat, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *dat, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *dat, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_pin_enum sck_pin, spi_pin_enum mosi_pin, spi_pin_enum miso_pin, gpio_pin_enum cs_pin);



#endif


