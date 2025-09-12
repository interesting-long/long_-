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

#ifndef __COMMON_H_
#define __COMMON_H_
#include "AI8051u_32bit.h"
#include <string.h>
#include <stdio.h>
#include "intrins.h"


#ifndef ENABLE
#define ENABLE 1
#endif

#ifndef DISABLE
#define DISABLE 0
#endif

//������������
typedef unsigned char   uint8  ;	//  8 bits
typedef unsigned int  	uint16 ;	// 16 bits
typedef unsigned long  	uint32 ;	// 32 bits


typedef signed char     int8   ;	//  8 bits
typedef signed int      int16  ;	// 16 bits
typedef signed long     int32  ;	// 32 bits


typedef volatile int8   vint8  ;	//  8 bits
typedef volatile int16  vint16 ;	// 16 bits
typedef volatile int32  vint32 ;	// 32 bits


typedef volatile uint8  vuint8 ;	//  8 bits
typedef volatile uint16 vuint16;	// 16 bits
typedef volatile uint32 vuint32;	// 32 bits



typedef enum //����ģ��
{
    NO_WIRELESS_MODE = 0,   // û������ģ��
    WIRELESS_SI24R1 = 1,    // ����ת����
    WIRELESS_CH9141 = 2,    // ����ת����
    WIRELESS_CH573 = 3,     // CH573ģ��
    WIRELESS_BLE6A20 = 4,   // BLE6A20����ģ��
    
} WIRELESS_TYPE_enum;


extern void (*uart1_irq_handler)(uint8 dat);
extern void (*uart2_irq_handler)(uint8 dat);
extern void (*uart3_irq_handler)(uint8 dat);
extern void (*uart4_irq_handler)(uint8 dat);

extern void (*tim0_irq_handler)(void);
extern void (*tim1_irq_handler)(void);
extern void (*tim2_irq_handler)(void);
extern void (*tim3_irq_handler)(void);
extern void (*tim4_irq_handler)(void);
extern void (*tim11_irq_handler)(void);

extern void (*int0_irq_handler)(void);
extern void (*int1_irq_handler)(void);
extern void (*int2_irq_handler)(void);
extern void (*int3_irq_handler)(void);
extern void (*int4_irq_handler)(void);

#define ZF_ENABLE           (1)
#define ZF_DISABLE          (0)

#define ZF_TRUE             (1)
#define ZF_FALSE            (0)

#endif
