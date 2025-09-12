#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "zf_common_headfile.h"


// 在头文件中定义所有扇区起始地址
#define EEPROM_SECTOR_SIZE     512     // STC32G EEPROM扇区大小

// 扇区起始地址定义（根据您的芯片容量调整）
#define SECTOR_0_ADDR          0x0000  // 扇区0起始地址
#define SECTOR_1_ADDR          0x0200  // 扇区1起始地址  
#define SECTOR_2_ADDR          0x0400  // 扇区2起始地址
#define SECTOR_3_ADDR          0x0600  // 扇区3起始地址
#define SECTOR_4_ADDR          0x0800  // 扇区4起始地址
#define SECTOR_5_ADDR          0x0A00  // 扇区5起始地址
#define SECTOR_6_ADDR          0x0C00  // 扇区6起始地址
#define SECTOR_7_ADDR          0x0E00  // 扇区7起始地址
#define SECTOR_8_ADDR          0x1000  // 扇区8起始地址

void eeprom_save_float(uint32 addr, float value);
float eeprom_read_float(uint32 addr);
void eeprom_read_Num(void);
void eeprom_save_Num(void);
#endif