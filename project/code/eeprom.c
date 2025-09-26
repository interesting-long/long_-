#include "eeprom.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���渡�������鵽EEPROM
//  @param      void
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_save_Num(void)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = SECTOR_1_ADDR;
    bit flag;
    
    // ��֤�����С
    uint32 array_size = sizeof(Num);
    if (array_size > 512) {
        return;  // ����̫���޷�����һ������
    }
    
    // �����ж�״̬���ر��ж�
    flag = EA;
    EA = 0;
    
    // 1. ��ȡ������������ʱ������
    iap_read_buff(sector_start, temp, 512);
    
    // 2. ֱ�ӽ��������鸴�Ƶ�������
    memcpy(temp, Num, sizeof(Num));
    
    // 3. ������������
    iap_erase_page(sector_start);
    system_delay_ms(10);
    
    // 4. ���޸ĺ������д������
    iap_write_buff(sector_start, temp, 512);
    
    // �ָ��ж�״̬
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��EEPROM��ȡ����������
//  @param      void
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_read_Num(void)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = SECTOR_1_ADDR;
    bit flag;
    
    // �����ж�״̬���ر��ж�
    flag = EA;
    EA = 0;
    
    // 1. ��ȡ������������
    iap_read_buff(sector_start, temp, 512);
    
    // 2. ֱ�Ӵӻ��������Ƶ�����
    memcpy(Num, temp, sizeof(Num));
    
    // �ָ��ж�״̬
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���渡������EEPROM(�Զ�����)
//  @param      addr        EEPROM��ʼ��ַ
//  @param      value       Ҫ����ĸ�����
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_save_float(uint32 addr, float value)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = addr & 0xFFFFFE00;  // ��ȡ������ʼ��ַ
    uint16 offset = addr & 0x1FF;             // ��ȡ�������ڵ�ƫ����
    unsigned char *float_ptr = (unsigned char *)&value;
    unsigned char i;
    bit flag;
    
    // �����ж�״̬���ر��ж�
    flag = EA;
    EA = 0;
    
    // 1. ��ȡ������������ʱ������
    iap_read_buff(sector_start, temp, 512);
    
    // 2. �޸Ļ������еĸ���������
    for(i = 0; i < sizeof(float); i++)
    {
        temp[offset + i] = float_ptr[i];
    }
    
    // 3. ������������
    iap_erase_page(sector_start);
    system_delay_ms(10);  // �ȴ��������
    
    // 4. ���޸ĺ������д������
    iap_write_buff(sector_start, temp, 512);
    
    // �ָ��ж�״̬
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��EEPROM��ȡ������
//  @param      addr        EEPROM��ʼ��ַ
//  @return     float       ��ȡ���ĸ�����
//-------------------------------------------------------------------------------------------------------------------
float eeprom_read_float(uint32 addr)
{
    float value;
    unsigned char *float_ptr = (unsigned char *)&value;
    bit flag;
    
    // �����ж�״̬���ر��ж�
    flag = EA;
    EA = 0;
    
    // ��EEPROM���ֽڶ�ȡ���ݵ�����������
    iap_read_buff(addr, float_ptr, sizeof(float));
    
    // �ָ��ж�״̬
    EA = flag;
    
    return value;
}