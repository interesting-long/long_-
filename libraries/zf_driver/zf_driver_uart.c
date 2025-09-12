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

#include "stdlib.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"

#include "zf_driver_uart.h"
#include "zf_driver_timer.h"
#include "zf_driver_gpio.h"

uint8 xdata uart_rx_buff[UART_RESERVE][1] = {0};

#define DMA_URXT_CFG(uart_n)		(*(unsigned char volatile far *)(0x7efa30 + uart_n*0x10))
#define DMA_URXT_CR(uart_n)     	(*(unsigned char volatile far *)(0x7efa31 + uart_n*0x10))
#define DMA_URXT_STA(uart_n)    	(*(unsigned char volatile far *)(0x7efa32 + uart_n*0x10))
#define DMA_URXT_AMT(uart_n)    	(*(unsigned char volatile far *)(0x7efa33 + uart_n*0x10))
#define DMA_URXT_DONE(uart_n)   	(*(unsigned char volatile far *)(0x7efa34 + uart_n*0x10))
#define DMA_URXT_TXAH(uart_n)   	(*(unsigned char volatile far *)(0x7efa35 + uart_n*0x10))
#define DMA_URXT_TXAL(uart_n)   	(*(unsigned char volatile far *)(0x7efa36 + uart_n*0x10))
#define DMA_URXR_CFG(uart_n)    	(*(unsigned char volatile far *)(0x7efa38 + uart_n*0x10))
#define DMA_URXR_CR(uart_n)     	(*(unsigned char volatile far *)(0x7efa39 + uart_n*0x10))
#define DMA_URXR_STA(uart_n)    	(*(unsigned char volatile far *)(0x7efa3a + uart_n*0x10))
#define DMA_URXR_AMT(uart_n)    	(*(unsigned char volatile far *)(0x7efa3b + uart_n*0x10))
#define DMA_URXR_DONE(uart_n)   	(*(unsigned char volatile far *)(0x7efa3c + uart_n*0x10))
#define DMA_URXR_RXAH(uart_n)   	(*(unsigned char volatile far *)(0x7efa3d + uart_n*0x10))
#define DMA_URXR_RXAL(uart_n)   	(*(unsigned char volatile far *)(0x7efa3e + uart_n*0x10))

#define DMA_URXT_AMTH(uart_n)   	(*(unsigned char volatile far *)(0x7efa88 + uart_n*0x04))
#define DMA_URXT_DONEH(uart_n)  	(*(unsigned char volatile far *)(0x7efa89 + uart_n*0x04))
#define DMA_URXR_AMTH(uart_n)   	(*(unsigned char volatile far *)(0x7efa8a + uart_n*0x04))
#define DMA_URXR_DONEH(uart_n)  	(*(unsigned char volatile far *)(0x7efa8b + uart_n*0x04))


// �������ֹ�޸ģ��ڲ�ʹ��,�û��������
static uart_function_enum uart_function_state[4] =
{
    UART_FUNCTION_INIT,
    UART_FUNCTION_INIT,
    UART_FUNCTION_INIT,
    UART_FUNCTION_INIT,
};

//-------------------------------------------------------------------------------------------------------------------
// �������     UART ����ȷ�Ϲ���״̬ ���ڲ�����
// ����˵��     index           UART ����ģ���
// ����˵��     mode            ��Ҫȷ�Ĺ���ģ��
// ���ز���     uint8           1-����ʹ�� 0-������ʹ��
// ʹ��ʾ��     zf_assert(uart_funciton_check(UART_2, UART_FUNCTION_UART));
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_funciton_check (uart_index_enum index, uart_function_enum mode)
{
    uint8 return_state = 1;
    if(UART_FUNCTION_INIT == uart_function_state[index])
    {
        uart_function_state[index] = mode;
    }
    else if(uart_function_state[index] == mode)
    {
        return_state = 1;
    }
    else
    {
        return_state = 0;
    }
    return return_state;
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ�������
// ����˵��     uart_n       ����ͨ��
// ����˵��     buff        Ҫ���͵������ַ
// ����˵��     len         ���ݳ���
// ���ز���     void
// ʹ��ʾ��     uart_write_buffer(UART_1, buff, 10);     //����1����10��buff���顣
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer(uart_index_enum uart_n, const uint8 *buff, uint16 len)
{

//	DMA_URXT_CFG(uart_n)  = 0x00; 			// DMA���ȼ���
	DMA_URXT_STA(uart_n) = 0;				// ��ձ�־λ
	len = len - 1;
	DMA_URXT_AMT(uart_n)  = len & 0xff;		// ���ô������ֽ���(��8λ)��n+1
	DMA_URXT_AMTH(uart_n) = len >> 8;		// ���ô������ֽ���(��8λ)��n+1
	DMA_URXT_TXAH(uart_n) = (uint8)((uint16)buff >> 8);
	DMA_URXT_TXAL(uart_n) = (uint8)((uint16)buff);
	DMA_URXT_CR(uart_n) = 0xC0; 			// ʹ��DMA TX����

	while(!(DMA_URXT_STA(uart_n) & 0x01));	// �ȴ��������

	DMA_URXT_CR(uart_n) = 0x00;				// �ر�DMA TX

}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ַ���
// ����˵��     uart_n       ����ͨ��
// ����˵��     str         �ַ����׵�ַ
// ���ز���     void
// ʹ��ʾ��     uart_putstr(UART_1, (uint8 *)"12345")   //����1����12345����ַ���
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string(uart_index_enum uart_n, const char *str)
{
	#define BUFF_LEN 256
	
    uint16 len = strlen(str);
	// ��UART_DMAֻ�ܲ���xdata��������ݣ����ԣ������½�һ�����飬���ơ�
	uint8 buff[BUFF_LEN];

	if(len <= BUFF_LEN)
	{
		memcpy(buff, str, len);
		uart_write_buffer(uart_n, buff, len);
	}
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ���һ���ֽ�
// ����˵��     uart_n       ����ͨ��
// ����˵��     dat         ��������
// ���ز���     void
// ʹ��ʾ��     uart_write_byte(UART_1, 0x43);        //����1����0x43��
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte(uart_index_enum uart_n, const uint8 dat)
{
    uart_write_buffer(uart_n, &dat, 1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڿ�ʼ��������
// ����˵��     uart_n       ����ͨ��
// ���ز���     void
// ʹ��ʾ��     uart_rx_start_buff(UART_1);
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_start_buff(uart_index_enum uart_n)
{
    DMA_URXR_AMT(uart_n) = (1 - 1);										// ���ý��յ��ֽ���
    DMA_URXR_AMTH(uart_n) = (1 - 1) >> 8;								// ���ý��յ��ֽ���
    DMA_URXR_RXAL(uart_n) = (uint8)((uint16)uart_rx_buff[uart_n]);		// ���ý��ջ����ַ
    DMA_URXR_RXAH(uart_n) = (uint8)((uint16)uart_rx_buff[uart_n] >> 8);	// ���ý��ջ����ַ
    DMA_URXR_CR(uart_n) = 0xA1;											// ����DMA RX�����жϣ�����DMA RX���գ����FIFO
}



//-------------------------------------------------------------------------------------------------------------------
// �������     �򿪴��ڽ����ж�
// ����˵��     uart_n       ����ͨ��
// ����˵��     status      ʹ�ܻ���ʧ��
// ���ز���     void
// ʹ��ʾ��     uart_rx_irq(UART_1, ENABLE);        //�򿪴���1�����ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt (uart_index_enum uart_n, uint8 status)
{
	if(status)
	{
		DMA_URXR_CFG(uart_n) |= 0x80;
	}
	else
	{
		DMA_URXR_CFG(uart_n) &= ~0x80;
	} 
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
// ����˵��     uart_n           ����ģ���(UART_1 - UART_4)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     void
// ʹ��ʾ��     dat = uart_read_byte(USART_1);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte(uart_index_enum uart_n)
{
	uint8 dat;
	
	// �ȴ�����������
	while(!(DMA_URXR_STA(uart_n)&0x03));

	// ��ȡ����
	dat = uart_rx_buff[uart_n][0];
		
	// ��ձ�־λ
	DMA_URXR_STA(uart_n) = 0x00;
	
	// ��ʼ��һ�ν���
	uart_rx_start_buff(uart_n);
	return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ���ѯ���գ�
// ����˵��     uart_n           ����ģ���(UART_1 - UART_8)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     uint8           1�����ճɹ�   0��δ���յ�����
// ʹ��ʾ��     uint8 dat; uart_query_byte(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte(uart_index_enum uart_n, uint8 *dat)
{
	uint8 ret = 0; 

	// ��ȡ����
	*dat = uart_rx_buff[uart_n][0];
	
	if(DMA_URXR_STA(uart_n) & 0x03)
	{
		ret = 1;
		
		DMA_URXR_STA(uart_n) &= ~0x03;
	}
	else
	{
		ret = 0;
	}
	
	// ��ʼ��һ�ν���
	uart_rx_start_buff(uart_n);

	return ret;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����DMA��ʼ��
// ����˵��     uart_n       ����ͨ��
// ���ز���     void
// ʹ��ʾ��     uart_dma_init(UART_1);
//-------------------------------------------------------------------------------------------------------------------
void uart_dma_init(uart_index_enum uart_n)
{
	DMA_URXT_CFG(uart_n)  = 0x00;	// DMA TX���ݷ������ȼ���ͣ��ر�DMA�����жϣ�
	DMA_URXT_STA(uart_n)  = 0x00;	// ���DMA TX״̬
	DMA_URXT_CR(uart_n)   = 0x00;	// �ر�DMA TX
		
	DMA_URXR_CFG(uart_n)  = 0x00;	// �ر�DMA�����ж�
	DMA_URXR_STA(uart_n)  = 0x00;	// ���DMA RX״̬
	DMA_URXR_CR(uart_n)   = 0x00;	// �ر�DMA RX

	DMA_URXR_AMT(uart_n)  = (1 - 1);									// ���ý��յ��ֽ���
	DMA_URXR_AMTH(uart_n) = (1 - 1)>>8;									// ���ý��յ��ֽ���
	DMA_URXR_RXAL(uart_n) = (uint8)((uint16)uart_rx_buff[uart_n]);		// ���ý��ջ����ַ
	DMA_URXR_RXAH(uart_n) = (uint8)((uint16)uart_rx_buff[uart_n] >> 8);	// ���ý��ջ����ַ
	DMA_URXR_CFG(uart_n)  = 0x0F;										// �ж����ȼ���ߣ�DMA���ȼ����
	DMA_URXR_CR(uart_n)   = 0xA1;										// ����DMA RX�����FIFO
 
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڳ�ʼ��
// ����˵��     uart_n       ����ͨ��
// ����˵��     baud        ������
// ����˵��     tx_pin      ���ڷ������ź�
// ����˵��     rx_pin      ���ڽ������ź�
// ���ز���     void
// ʹ��ʾ��     uart_init(UART_2, 115200, UART2_TX_P11, UART2_RX_P10); //����2��ʼ�����ź�,TXΪP11,RXΪP10
// ��ע��Ϣ     ���еĴ��ڣ���ֻ��ʹ�ö�ʱ��2 �������ʷ����������еĴ���ֻ����ͬһ�������ʡ�
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin)
{
    uint16 brt;
    
	// �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ��UART1 �� UART2����
    // �����ʼ���� UART1 Ȼ���ֳ�ʼ���� SPI1 �����÷��ǲ������
	// UART1��SPI1ʹ��ͬһ���Ĵ�����Ҫô��UART1Ҫôʹ��SPI1,ֻ���Ƕ�ѡһ��
	// UART2��SPI2ʹ��ͬһ���Ĵ�����Ҫô��UART2Ҫôʹ��SPI2,ֻ���Ƕ�ѡһ��
    zf_assert(uart_funciton_check(uart_n, UART_FUNCTION_UART));
	
	    
	// �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
	// TIM2�Ѿ����������������ʷ������ˡ������ٳ�ʼ��Ϊ�����ġ�
	zf_assert(timer_funciton_check(TIM_2, TIMER_FUNCTION_UART));
	
	
	// ���ڵ�RX��TX������һ���л��������������б���
	// ��˵����ѡ������ͬһ���������
	zf_assert(((tx_pin >> 8) & 0x0f) == ((rx_pin >> 8) & 0x0f));
	
	// ��ʼ��GPIO
	gpio_init(tx_pin&0xFF, GPO, 1, GPO_PUSH_PULL);
	gpio_init(rx_pin&0xFF, GPI, 1, GPI_FLOATING_IN);
	
    brt = (uint16)(65536 - (system_clock / (baud + 2) / 4));
    
    switch(uart_n)
    {
        case UART_1:
        {
            //            if(TIM_1 == tim_n)
            //            {
            //                SCON |= 0x50;
            //                TMOD |= 0x00;
            //                TL1 = brt;
            //                TH1 = brt >> 8;
            //                AUXR |= 0x40;
            //                TR1 = 0;	//�رշ����ж�
            //
            //            }
            //            else if(TIM_2 == tim_n)
            {
                SCON |= 0x50;
                T2L = brt;
                T2H = brt >> 8;
                AUXR |= 0x15;
                TR1 = 0;	//�رշ����ж�
            }
            
            P_SW1 &= ~(0x03 << 6);
            
            if((UART1_RX_P30 == rx_pin) && (UART1_TX_P31 == tx_pin))
            {
                P_SW1 |= 0x00;
            }
            else if((UART1_RX_P36 == rx_pin) && (UART1_TX_P37 == tx_pin))
            {
                P_SW1 |= 0x40;
            }
            else if((UART1_RX_P16 == rx_pin) && (UART1_TX_P17 == tx_pin))
            {
                P_SW1 |= 0x80;
            }
            else if((UART1_RX_P43 == rx_pin) && (UART1_TX_P44 == tx_pin))
            {
                P_SW1 |= 0xc0;
            }
            
            //            ES = 1;	//�����п�1�ж�
            break;
        }
        
        case UART_2:
        {
            //            if(TIM_2 == tim_n)
            {
                S2CON |= 0x50;
                T2L = brt;
                T2H = brt >> 8;
                AUXR |= 0x14;
            }
            
            P_SW2 &= ~(0x01 << 0);
            
            if((UART2_RX_P12 == rx_pin) && (UART2_TX_P13 == tx_pin))
            {
                P_SW2 |= 0x00;
            }
            else if((UART2_RX_P42 == rx_pin) && (UART2_TX_P43 == tx_pin))
            {
                P_SW2 |= 0x01;
            }
            
            //            IE2 |= 0x01 << 0;	//�����п�2�ж�
            
            break;
        }
        
        case UART_3:
        {
            //            if(TIM_2 == tim_n)
            {
                S3CON |= 0x10;
                T2L = brt;
                T2H = brt >> 8;
                AUXR |= 0x14;
            }
            //            else if(TIM_3 == tim_n)
            //            {
            //                S3CON |= 0x50;
            //                T3L = brt;
            //                T3H = brt >> 8;
            //                T4T3M |= 0x0a;
            //            }
            
            P_SW2 &= ~(0x01 << 1);
            
            if((UART3_RX_P00 == rx_pin) && (UART3_TX_P01 == tx_pin))
            {
                P_SW2 |= 0x00;
            }
            else if((UART3_RX_P50 == rx_pin) && (UART3_TX_P51 == tx_pin))
            {
                P_SW2 |= 0x02;
            }
            
            //            IE2 |= 0x01 << 3;	//�����п�3�ж�
            
            break;
        }
        
        case UART_4:
        {
            //            if(TIM_2 == tim_n)
            {
                S4CON |= 0x10;
                T2L = brt;
                T2H = brt >> 8;
                AUXR |= 0x14;
            }
            //            else if(TIM_4 == tim_n)
            //            {
            //                S4CON |= 0x50;
            //                T4L = brt;
            //                T4H = brt >> 8;
            //                T4T3M |= 0xa0;
            //            }
            
            P_SW2 &= ~(0x01 << 2);
            
            if((UART4_RX_P02 == rx_pin) && (UART4_TX_P03 == tx_pin))
            {
                P_SW2 |= 0x00;
            }
            else if((UART4_RX_P52 == rx_pin) && (UART4_TX_P53 == tx_pin))
            {
//                P5M0 = 0x00;
//                P5M1 = 0x01 << 2; //P5.2 ��Ҫ����Ϊ����
                P_SW2 |= 0x04;
            }
            
            //            IE2 |= 0x01 << 4;	//�����п�4�ж�
            
            break;
        }
        
    }
    
	// uart dma ��ʼ��
    uart_dma_init(uart_n);
    
}
