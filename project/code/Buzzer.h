#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "zf_common_headfile.h"
#define Buzzer_Pin IO_P50

void Buzzer_Init();
void Buzzer_ON();
void Buzzer_OFF();
#endif