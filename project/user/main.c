#include "zf_common_headfile.h"
int T;
float test=1.00;
void pit_handler (void);
void main()
{
    clock_init(SYSTEM_CLOCK_40M);				// ��ر���
	debug_init();								// ��ر���
	/****************************************************/
	tim0_irq_handler = pit_handler;// ���ö�ʱ��1�жϻص�����
	init_all();
    while(1)
	{
		if(Key)
		{
			EA=0;
			menu_handle_key(Key);
			Key=0;
			EA=1;
		}
    }
}
void pit_handler(void)
{
	tft180_show_int16(40,0*16,ADC_1);
	tft180_show_int16(40,1*16,ADC_2);
	tft180_show_int16(40,2*16,ADC_3);
	tft180_show_int16(40,3*16,ADC_4);
	ADC_SampleAndFilter();
	Key_scaner();
}

