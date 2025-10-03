#include "Buzzer.h"
void Buzzer_Init()
{
	gpio_init(Buzzer_Pin,GPO,0,GPO_PUSH_PULL);
}
void Buzzer_ON()
{
	gpio_set_level(Buzzer_Pin,1);
}

void Buzzer_OFF()
{
	gpio_set_level(Buzzer_Pin,0);
}