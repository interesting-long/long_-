#include "test.h"

void Serve_Test(void)
{
	unsigned char i;
	unsigned char j;
	for(j=0;j<3;j++)
	{
		for(i=0;i<200;i++)
		{
			Ser_Servo_Duty(Servo_Mide+Servo_min+(Servo_max-Servo_min)/200*i);
			system_delay_ms(5);
		}
		for(i=200;i>0;i--)
		{
			Ser_Servo_Duty(Servo_Mide+Servo_min+(Servo_max-Servo_min)/200*i);
			system_delay_ms(5);
		}
	}
}