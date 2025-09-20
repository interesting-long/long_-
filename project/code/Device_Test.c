#include "Device_Test.h"

void Serve_Test(void)
{
	unsigned char a;
	unsigned char j;

	for(j=0;j<3;j++)
	{
		for(a=0;a<160;a++)
		{
			Ser_Servo_Duty(725+a);
			system_delay_ms(20);
		}
		for(a=0;a<160;a++)
		{
			Ser_Servo_Duty(885-a);
			system_delay_ms(20);
		}
	}
}

void LM_Test(void)
{
	MotorL_SetSpeed(20);
	system_delay_ms(500);
	MotorL_SetSpeed(40);
	system_delay_ms(500);
	MotorL_SetSpeed(50);
	system_delay_ms(500);
}
void RM_Test(void)
{
	MotorR_SetSpeed(20);
	system_delay_ms(500);
	MotorR_SetSpeed(40);
	system_delay_ms(500);
	MotorR_SetSpeed(50);
	system_delay_ms(500);
}