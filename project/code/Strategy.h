#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "zf_common_headfile.h"

#define abs(a) ((a) < 0 ? -(a) : (a))

extern float uni;
extern float last_uni;
void LineLossProtection();
#endif