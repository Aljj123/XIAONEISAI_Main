#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Motor.h"
#include "PWM.h"
#include "Servo.h"
#include "Exit.h"


int main(void)
{
	OLED_Init();
	Serial_Init();
	PWM_Init();
	Motor_Init();
	Motor_AllStop();
	EXTI_State_Init();
	
	
	
	while (1)
	{
		Bluetooth_DataProcess();
		
	}
}
