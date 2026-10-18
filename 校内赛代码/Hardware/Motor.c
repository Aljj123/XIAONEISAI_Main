#include "stm32f10x.h"                  // Device header
#include "PWM.h"




void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11|GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void Motor_SetSpeed( uint8_t motor,float Speed)
{

    if (Speed > 100) Speed = 100;
    if (Speed < -100) Speed = -100;
	
	switch(motor)
	{
		case 1: // 左前轮
			if (Speed >= 0)
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_4);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5);
				PWM_Motor_SetCompare1(Speed*8);
			}else
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_4);
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
				PWM_Motor_SetCompare1(-Speed*8);
			} // 转换为0~1000的PWM占空比
            break;
        case 2: // 右前轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				PWM_Motor_SetCompare2(Speed*8);
			}else
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				PWM_Motor_SetCompare2(-Speed*8);
			} 
            break;
        case 3: // 右后轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				GPIO_ResetBits(GPIOB, GPIO_Pin_11);
				PWM_Motor_SetCompare3(Speed*8);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_10);
				GPIO_SetBits(GPIOB, GPIO_Pin_11);
				PWM_Motor_SetCompare3(-Speed*8);
			} 
            break;
        case 4: // 左后轮
            if (Speed >= 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_12);
				GPIO_ResetBits(GPIOB, GPIO_Pin_13);
				PWM_Motor_SetCompare4(Speed*8);
			}else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				GPIO_SetBits(GPIOB, GPIO_Pin_13);
				PWM_Motor_SetCompare4(-Speed*8);
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

