#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo1_SetAngle(float Angle){Servo_Set1(Angle / 180 * 2000 + 500);}
void Servo2_SetAngle(float Angle){Servo_Set2(Angle / 180 * 2000 + 500);}
void Servo3_SetAngle(float Angle){Servo_Set3(Angle / 180 * 2000 + 500);}
void Servo4_SetAngle(float Angle){Servo_Set4(Angle / 180 * 2000 + 500);}
void Servo5_SetAngle(float Angle){Servo_Set5(Angle / 180 * 2000 + 500);}


