#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include <math.h>




void Motor_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11|GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void Motor_SetSpeed( uint8_t motor,float Speed)
{
	//限幅保护
    if(Speed > 120) Speed = 120;
    if(Speed < -120) Speed = -120;
    uint16_t pwm_val = (uint16_t)(fabs(Speed)*8);
	
	switch(motor)
	{
		case 1: // 左前轮
			if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				Motor_SetPWM1(pwm_val);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_10);
				Motor_SetPWM1(-Speed*8);
			} // 转换为0~1000的PWM占空比
            break;
        case 2: // 右前轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_11);
				Motor_SetPWM2(pwm_val);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_11);
				Motor_SetPWM2(pwm_val);
			} 
            break;
        case 3: // 右后轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_12);
				Motor_SetPWM3(pwm_val);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				Motor_SetPWM3(pwm_val);
			} 
            break;
        case 4: // 左后轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_13);
				Motor_SetPWM4(pwm_val);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_13);
				Motor_SetPWM4(pwm_val);
			} 
            break;
    }

}
void Motor_Set(float w1,float w2,float w3,float w4)
{
	Motor_SetSpeed(1,w1);
	Motor_SetSpeed(2,w2);
	Motor_SetSpeed(3,w3);
	Motor_SetSpeed(4,w4);

}

void Motor_AllStop(void)
{
    //DIR全部清0
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    //PWM全部置0，切断驱动输出
    Motor_SetPWM1(0);
    Motor_SetPWM2(0);
    Motor_SetPWM3(0);
    Motor_SetPWM4(0);
}

