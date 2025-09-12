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

#include "zf_driver_soft_iic.h"

#pragma warning disable = 183
#pragma warning disable = 177


#define SOFT_IIC_SDA_IO_SWITCH          (0)                                     // �Ƿ���Ҫ SDA ���� I/O �л� 0-����Ҫ 1-��Ҫ

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ��ʱ
// ����˵��     delay           ��ʱ����
// ���ز���     void
// ʹ��ʾ��     soft_iic_delay(1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_delay (vuint32 delay)
{
    volatile uint32 count = delay;
    while(count --);
}
//#define soft_iic_delay(x)  for(uint32 i = x; i--; )

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC START �ź�
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     void
// ʹ��ʾ��     soft_iic_start(soft_iic_obj);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_start (soft_iic_info_struct *soft_iic_obj)
{
    zf_assert(soft_iic_obj != NULL);
    gpio_high(soft_iic_obj->scl_pin);                                           // SCL �ߵ�ƽ
    gpio_high(soft_iic_obj->sda_pin);                                           // SDA �ߵ�ƽ

    soft_iic_delay(soft_iic_obj->delay);
    gpio_low(soft_iic_obj->sda_pin);                                            // SDA ������
    soft_iic_delay(soft_iic_obj->delay);
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL ������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC STOP �ź�
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     void
// ʹ��ʾ��     soft_iic_stop(soft_iic_obj);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_stop (soft_iic_info_struct *soft_iic_obj)
{
    zf_assert(soft_iic_obj != NULL);
    gpio_low(soft_iic_obj->sda_pin);                                            // SDA �͵�ƽ
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ

    soft_iic_delay(soft_iic_obj->delay);
    gpio_high(soft_iic_obj->scl_pin);                                           // SCL ������
    soft_iic_delay(soft_iic_obj->delay);
    gpio_high(soft_iic_obj->sda_pin);                                           // SDA ������
    soft_iic_delay(soft_iic_obj->delay);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ���� ACK/NAKC �ź� �ڲ�����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     ack             ACK ��ƽ
// ���ز���     void
// ʹ��ʾ��     soft_iic_send_ack(soft_iic_obj, 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_send_ack (soft_iic_info_struct *soft_iic_obj, uint8 ack)
{
    zf_assert(soft_iic_obj != NULL);
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ

    if(ack)
    {
        gpio_high(soft_iic_obj->sda_pin);                                       // SDA ����
    }
    else
    {
        gpio_low(soft_iic_obj->sda_pin);                                        // SDA ����
    }

    soft_iic_delay(soft_iic_obj->delay);
    gpio_high(soft_iic_obj->scl_pin);                                           // SCL ����
    soft_iic_delay(soft_iic_obj->delay);
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL ����
    gpio_high(soft_iic_obj->sda_pin);                                           // SDA ����
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ��ȡ ACK/NAKC �ź�
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     uint8           ACK ״̬
// ʹ��ʾ��     soft_iic_wait_ack(soft_iic_obj);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_wait_ack (soft_iic_info_struct *soft_iic_obj)
{
	uint8 temp = 0;
    zf_assert(soft_iic_obj != NULL);
  
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ
    gpio_high(soft_iic_obj->sda_pin);                                           // SDA �ߵ�ƽ �ͷ� SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(soft_iic_obj->sda_pin, GPI, GPI_FLOATING_IN);
#endif
    soft_iic_delay(soft_iic_obj->delay);

    gpio_high(soft_iic_obj->scl_pin);                                           // SCL �ߵ�ƽ
    soft_iic_delay(soft_iic_obj->delay);

    if(gpio_get_level((gpio_pin_enum)soft_iic_obj->sda_pin))
    {
        temp = 1;
    }
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(soft_iic_obj->sda_pin, GPO, GPO_OPEN_DTAIN);
#endif
    soft_iic_delay(soft_iic_obj->delay);

    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ���� 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     dat            ����
// ���ز���     uint8           ACK ״̬
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_send_data (soft_iic_info_struct *soft_iic_obj, const uint8 dat)
{
	uint8 temp = 0x80;
	
    zf_assert(soft_iic_obj != NULL);

    while(temp)
    {
//        gpio_set_level(soft_iic_obj->sda_pin, dat & temp);
        ((dat & temp) ? (gpio_high(soft_iic_obj->sda_pin)) : (gpio_low(soft_iic_obj->sda_pin)));
        temp >>= 1;

        soft_iic_delay(soft_iic_obj->delay);
        gpio_high(soft_iic_obj->scl_pin);                                       // SCL ����
        soft_iic_delay(soft_iic_obj->delay);
        gpio_low(soft_iic_obj->scl_pin);                                        // SCL ����
    }
    return ((soft_iic_wait_ack(soft_iic_obj) == 1) ? 0 : 1 );
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ��ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     ack             ACK �� NACK
// ���ز���     uint8           ����
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_read_data (soft_iic_info_struct *soft_iic_obj, uint8 ack)
{
    uint8 dat = 0x00;
    uint8 temp = 8;
	zf_assert(soft_iic_obj != NULL);
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ
    soft_iic_delay(soft_iic_obj->delay);
    gpio_high(soft_iic_obj->sda_pin);                                           // SDA �ߵ�ƽ �ͷ� SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(soft_iic_obj->sda_pin, GPI, GPI_FLOATING_IN);
#endif

    while(temp --)
    {
        gpio_low(soft_iic_obj->scl_pin);                                        // SCL ����
        soft_iic_delay(soft_iic_obj->delay);
        gpio_high(soft_iic_obj->scl_pin);                                       // SCL ����
        soft_iic_delay(soft_iic_obj->delay);
        dat = ((dat << 1) | gpio_get_level((gpio_pin_enum)soft_iic_obj->sda_pin));
    }
    gpio_low(soft_iic_obj->scl_pin);                                            // SCL �͵�ƽ
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(soft_iic_obj->sda_pin, GPO, GPO_OPEN_DTAIN);
#endif
    soft_iic_delay(soft_iic_obj->delay);
    soft_iic_send_ack(soft_iic_obj, ack);
    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ�д 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     dat            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_8bit_register(soft_iic_obj, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_8bit (soft_iic_info_struct *soft_iic_obj, const uint8 dat)
{
    zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, dat);
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ�д 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *dat           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_8bit_array(soft_iic_obj, dat, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_8bit_array (soft_iic_info_struct *soft_iic_obj, const uint8 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    while(len --)
    {
        soft_iic_send_data(soft_iic_obj, *dat ++);
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ���д 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     dat            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_16bit(soft_iic_obj, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_16bit (soft_iic_info_struct *soft_iic_obj, const uint16 dat)
{
    zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, (uint8)((dat & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(dat & 0x00FF));
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ�д 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *dat           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_16bit_array(soft_iic_obj, dat, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_16bit_array (soft_iic_info_struct *soft_iic_obj, const uint16 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    while(len --)
    {
        soft_iic_send_data(soft_iic_obj, (uint8)((*dat & 0xFF00) >> 8));
        soft_iic_send_data(soft_iic_obj, (uint8)(*dat ++ & 0x00FF));
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     dat            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_8bit_register(soft_iic_obj, 0x01, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_8bit_register (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, const uint8 dat)
{
    zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    soft_iic_send_data(soft_iic_obj, dat);
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *dat           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_8bit_registers(soft_iic_obj, 0x01, dat, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_8bit_registers (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, const uint8 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    while(len --)
    {
        soft_iic_send_data(soft_iic_obj, *dat ++);
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     dat            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_16bit_register(soft_iic_obj, 0x0101, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_16bit_register (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, const uint16 dat)
{
    zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, (uint8)((register_name & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(register_name & 0x00FF));
    soft_iic_send_data(soft_iic_obj, (uint8)((dat & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(dat & 0x00FF));
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *dat           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_write_16bit_registers(soft_iic_obj, 0x0101, dat, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_write_16bit_registers (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, const uint16 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, (uint8)((register_name & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(register_name & 0x00FF));
    while(len--)
    {
        soft_iic_send_data(soft_iic_obj, (uint8)((*dat & 0xFF00) >> 8));
        soft_iic_send_data(soft_iic_obj, (uint8)(*dat ++ & 0x00FF));
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڶ�ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     soft_iic_read_8bit(soft_iic_obj);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_read_8bit (soft_iic_info_struct *soft_iic_obj)
{
    uint8 temp = 0;
	zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    temp = soft_iic_read_data(soft_iic_obj, 1);
    soft_iic_stop(soft_iic_obj);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *dat           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     soft_iic_read_8bit_array(soft_iic_obj, dat, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_read_8bit_array (soft_iic_info_struct *soft_iic_obj, uint8 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    while(len --)
    {
        *dat ++ = soft_iic_read_data(soft_iic_obj, len == 0);
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڶ�ȡ 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint16          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     soft_iic_read_16bit(soft_iic_obj);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 soft_iic_read_16bit (soft_iic_info_struct *soft_iic_obj)
{
    uint16 temp = 0;
	zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    temp = soft_iic_read_data(soft_iic_obj, 0);
    temp = ((temp << 8)| soft_iic_read_data(soft_iic_obj, 1));
    soft_iic_stop(soft_iic_obj);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڶ�ȡ 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *dat           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     soft_iic_read_16bit_array(soft_iic_obj, dat, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_read_16bit_array (soft_iic_info_struct *soft_iic_obj, uint16 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    while(len --)
    {
        *dat = soft_iic_read_data(soft_iic_obj, 0);
        *dat = ((*dat << 8)| soft_iic_read_data(soft_iic_obj, len == 0));
        dat ++;
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     soft_iic_read_8bit_register(soft_iic_obj, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_read_8bit_register (soft_iic_info_struct *soft_iic_obj, const uint8 register_name)
{
    uint8 temp = 0;
	zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    temp = soft_iic_read_data(soft_iic_obj, 1);
    soft_iic_stop(soft_iic_obj);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *dat           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     soft_iic_read_8bit_registers(soft_iic_obj, 0x01, dat, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_read_8bit_registers (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, uint8 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    while(len --)
    {
        *dat ++ = soft_iic_read_data(soft_iic_obj, len == 0);
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint16          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     soft_iic_read_16bit_register(soft_iic_obj, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 soft_iic_read_16bit_register (soft_iic_info_struct *soft_iic_obj, const uint16 register_name)
{
    uint16 temp = 0;
	zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, (uint8)((register_name & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(register_name & 0x00FF));
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    temp = soft_iic_read_data(soft_iic_obj, 0);
    temp = ((temp << 8)| soft_iic_read_data(soft_iic_obj, 1));
    soft_iic_stop(soft_iic_obj);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *dat           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     soft_iic_read_16bit_registers(soft_iic_obj, 0x0101, dat, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_read_16bit_registers (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, uint16 *dat, uint32 len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(dat != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, (uint8)((register_name & 0xFF00) >> 8));
    soft_iic_send_data(soft_iic_obj, (uint8)(register_name & 0x00FF));
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    while(len --)
    {
        *dat = soft_iic_read_data(soft_iic_obj, 0);
        *dat = ((*dat << 8)| soft_iic_read_data(soft_iic_obj, len == 0));
        dat ++;
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴ��� 8bit ���� ��д���ȡ
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *write_data     �������ݴ�Ż�����
// ����˵��     write_len       ���ͻ���������
// ����˵��     *read_data      ��ȡ���ݴ�Ż�����
// ����˵��     read_len        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_8bit_array(IIC_1, addr, dat, 64, dat, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_transfer_8bit_array (soft_iic_info_struct *soft_iic_obj, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(write_data != NULL);
    zf_assert(read_data != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    while(write_len --)
    {
        soft_iic_send_data(soft_iic_obj, *write_data ++);
    }

    if(read_len)
    {
        soft_iic_start(soft_iic_obj);
        soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
        while(read_len --)
        {
            *read_data ++ = soft_iic_read_data(soft_iic_obj, read_len == 0);
        }
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڴ��� 16bit ���� ��д���ȡ
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *write_data     �������ݴ�Ż�����
// ����˵��     write_len       ���ͻ���������
// ����˵��     *read_data      ��ȡ���ݴ�Ż�����
// ����˵��     read_len        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_16bit_array(IIC_1, addr, dat, 64, dat, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_transfer_16bit_array (soft_iic_info_struct *soft_iic_obj, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(write_data != NULL);
    zf_assert(read_data != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    while(write_len--)
    {
        soft_iic_send_data(soft_iic_obj, (uint8)((*write_data & 0xFF00) >> 8));
        soft_iic_send_data(soft_iic_obj, (uint8)(*write_data ++ & 0x00FF));
    }
    if(read_len)
    {
        soft_iic_start(soft_iic_obj);
        soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
        while(read_len --)
        {
            *read_data = soft_iic_read_data(soft_iic_obj, 0);
            *read_data = ((*read_data << 8)| soft_iic_read_data(soft_iic_obj, read_len == 0));
            read_data ++;
        }
    }
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ� SCCB ģʽ�򴫸����Ĵ���д 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     dat            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     soft_iic_sccb_write_register(soft_iic_obj, 0x01, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_sccb_write_register (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, uint8 dat)
{
    zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    soft_iic_send_data(soft_iic_obj, dat);
    soft_iic_stop(soft_iic_obj);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ� SCCB ģʽ�Ӵ������Ĵ�����ȡ 8bit ����
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     soft_iic_sccb_read_register(soft_iic_obj, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 soft_iic_sccb_read_register (soft_iic_info_struct *soft_iic_obj, const uint8 register_name)
{
    uint8 temp = 0;
	zf_assert(soft_iic_obj != NULL);
    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1);
    soft_iic_send_data(soft_iic_obj, register_name);
    soft_iic_stop(soft_iic_obj);

    soft_iic_start(soft_iic_obj);
    soft_iic_send_data(soft_iic_obj, soft_iic_obj->addr << 1 | 0x01);
    temp = soft_iic_read_data(soft_iic_obj, 1);
    soft_iic_stop(soft_iic_obj);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿڳ�ʼ�� Ĭ�� MASTER ģʽ ���ṩ SLAVE ģʽ
// ����˵��     *soft_iic_obj   ��� IIC ָ����Ϣ��Žṹ���ָ��
// ����˵��     addr            ��� IIC ��ַ ������Ҫע�� ��׼��λ��ַ ���λ���� д��ʱ�����ȷ������
// ����˵��     delay           ��� IIC ��ʱ ����ʱ�Ӹߵ�ƽʱ�� Խ�� IIC ����Խ��
// ����˵��     scl_pin         ��� IIC ʱ������ ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ����˵��     sda_pin         ��� IIC �������� ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ���ز���     void            
// ʹ��ʾ��     soft_iic_init(&soft_iic_obj, addr, 100, B6, B7);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void soft_iic_init (soft_iic_info_struct *soft_iic_obj, uint8 addr, uint32 delay, gpio_pin_enum scl_pin, gpio_pin_enum sda_pin)
{
    zf_assert(soft_iic_obj != NULL);
    zf_assert(scl_pin != sda_pin);                                 // ���ѣ� scl_pin �� sda_pin ��ô����ͬһ�����ţ�
    soft_iic_obj->scl_pin = scl_pin;
    soft_iic_obj->sda_pin = sda_pin;
    soft_iic_obj->addr = addr;
    soft_iic_obj->delay = delay;
    gpio_init(scl_pin, GPO, 1, GPO_OPEN_DTAIN);                          	// ��ȡ��ӦIO���� AF���ܱ���
    gpio_init(sda_pin, GPO, 1, GPO_OPEN_DTAIN);                         	// ��ȡ��ӦIO���� AF���ܱ���
}
