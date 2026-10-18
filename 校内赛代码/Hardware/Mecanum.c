#include "stm32f10x.h"                  // Device header
#include "Mecanum.h"
#include <math.h>


void Mecanum_Calc(float vx_set,float vy_set,float wz_set,float wheel_speed[4])
{
	float w1 , w2 , w3 , w4 ;
	w1=   vx_set - vy_set - MOTOR_DISTANCE_TO_CENTER * wz_set;
	w2= - vx_set - vy_set - MOTOR_DISTANCE_TO_CENTER * wz_set;
	w3= - vx_set + vy_set - MOTOR_DISTANCE_TO_CENTER * wz_set;
	w4=   vx_set + vy_set - MOTOR_DISTANCE_TO_CENTER * wz_set;
	

	wheel_speed[0]=w1;
	wheel_speed[1]=w2;
    wheel_speed[2]=w3;
    wheel_speed[3]=w4;
	
	//====矢量归一缩放，保持比例不变，最大值限制±100====
    float max_abs = 0;
    for(uint8_t i=0;i<4;i++)
    {
        float temp = fabs(wheel_speed[i]);
        if(temp>max_abs) max_abs = temp;
    }
    if(max_abs > 100.0f)
    {
        float scale = 100.0f / max_abs;
        for(uint8_t i=0;i<4;i++)
        {
            wheel_speed[i] *= scale;
        }
    }
}  
