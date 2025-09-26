#include "eeprom.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      保存浮点数数组到EEPROM
//  @param      void
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_save_Num(void)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = SECTOR_1_ADDR;
    bit flag;
    
    // 验证数组大小
    uint32 array_size = sizeof(Num);
    if (array_size > 512) {
        return;  // 数组太大，无法存入一个扇区
    }
    
    // 保存中断状态并关闭中断
    flag = EA;
    EA = 0;
    
    // 1. 读取整个扇区到临时缓冲区
    iap_read_buff(sector_start, temp, 512);
    
    // 2. 直接将整个数组复制到缓冲区
    memcpy(temp, Num, sizeof(Num));
    
    // 3. 擦除整个扇区
    iap_erase_page(sector_start);
    system_delay_ms(10);
    
    // 4. 将修改后的数据写回扇区
    iap_write_buff(sector_start, temp, 512);
    
    // 恢复中断状态
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从EEPROM读取浮点数数组
//  @param      void
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_read_Num(void)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = SECTOR_1_ADDR;
    bit flag;
    
    // 保存中断状态并关闭中断
    flag = EA;
    EA = 0;
    
    // 1. 读取整个扇区数据
    iap_read_buff(sector_start, temp, 512);
    
    // 2. 直接从缓冲区复制到数组
    memcpy(Num, temp, sizeof(Num));
    
    // 恢复中断状态
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      保存浮点数到EEPROM(自动擦除)
//  @param      addr        EEPROM起始地址
//  @param      value       要保存的浮点数
//  @return     void
//-------------------------------------------------------------------------------------------------------------------
void eeprom_save_float(uint32 addr, float value)
{
    unsigned char temp[512] = {0};
    uint32 sector_start = addr & 0xFFFFFE00;  // 获取扇区起始地址
    uint16 offset = addr & 0x1FF;             // 获取在扇区内的偏移量
    unsigned char *float_ptr = (unsigned char *)&value;
    unsigned char i;
    bit flag;
    
    // 保存中断状态并关闭中断
    flag = EA;
    EA = 0;
    
    // 1. 读取整个扇区到临时缓冲区
    iap_read_buff(sector_start, temp, 512);
    
    // 2. 修改缓冲区中的浮点数数据
    for(i = 0; i < sizeof(float); i++)
    {
        temp[offset + i] = float_ptr[i];
    }
    
    // 3. 擦除整个扇区
    iap_erase_page(sector_start);
    system_delay_ms(10);  // 等待擦除完成
    
    // 4. 将修改后的数据写回扇区
    iap_write_buff(sector_start, temp, 512);
    
    // 恢复中断状态
    EA = flag;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从EEPROM读取浮点数
//  @param      addr        EEPROM起始地址
//  @return     float       读取到的浮点数
//-------------------------------------------------------------------------------------------------------------------
float eeprom_read_float(uint32 addr)
{
    float value;
    unsigned char *float_ptr = (unsigned char *)&value;
    bit flag;
    
    // 保存中断状态并关闭中断
    flag = EA;
    EA = 0;
    
    // 从EEPROM按字节读取数据到浮点数变量
    iap_read_buff(addr, float_ptr, sizeof(float));
    
    // 恢复中断状态
    EA = flag;
    
    return value;
}