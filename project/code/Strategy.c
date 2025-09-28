#include "Strategy.h"
float uni=0;
float last_uni=0;
int loss_Time=0;
void LineLossProtection()
{
    uni = unification();
//    if(100 * abs(uni - last_uni) > Lose  && last_uni!=0)
//    {
//		loss_Time++;
//		if(loss_Time>=3)
//		{
//            Servo_turn_pid(last_uni, -90, 90);
//		}
//		else
//		{
			Servo_turn_pid(uni);
//		}
//    }
//    else
//    {
//		loss_Time=0;
//        Servo_turn_pid(uni, -90, 90);
//        last_uni = uni;
//    }
}