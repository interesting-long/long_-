#include "Device_Test.h"

void Serve_Test(void)
{
	unsigned char a;
	unsigned char j;

	for(j=0;j<3;j++)
	{
		for(a=0;a<180;a++)
		{
			Ser_Servo_Duty(754+a);
			system_delay_ms(20);
			if(CAR_Mode!=TEST_SERVO){return;}
		}
		for(a=0;a<180;a++)
		{
			Ser_Servo_Duty(934-a);
			system_delay_ms(20);
			if(CAR_Mode!=TEST_SERVO){return;}
		}
	}
}

void PWM_Test(void)
{
	MotorL_SetSpeed(Test_LPWM*100);
	MotorR_SetSpeed(Test_RPWM*100);
}

void Set_Sevo(void)
{
	Ser_Servo_Duty(S_Value);
}