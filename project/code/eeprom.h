#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "zf_common_headfile.h"


// ��ͷ�ļ��ж�������������ʼ��ַ
#define EEPROM_SECTOR_SIZE     512     // STC32G EEPROM������С

// ������ʼ��ַ���壨��������оƬ����������
#define SECTOR_0_ADDR          0x0000  // ����0��ʼ��ַ
#define SECTOR_1_ADDR          0x0200  // ����1��ʼ��ַ  
#define SECTOR_2_ADDR          0x0400  // ����2��ʼ��ַ
#define SECTOR_3_ADDR          0x0600  // ����3��ʼ��ַ
#define SECTOR_4_ADDR          0x0800  // ����4��ʼ��ַ
#define SECTOR_5_ADDR          0x0A00  // ����5��ʼ��ַ
#define SECTOR_6_ADDR          0x0C00  // ����6��ʼ��ַ
#define SECTOR_7_ADDR          0x0E00  // ����7��ʼ��ַ
#define SECTOR_8_ADDR          0x1000  // ����8��ʼ��ַ

void eeprom_save_float(uint32 addr, float value);
float eeprom_read_float(uint32 addr);
void eeprom_read_Num(void);
void eeprom_save_Num(void);
#endif