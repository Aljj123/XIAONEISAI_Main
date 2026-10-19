#include "stm32f10x.h"                  // Device header
#include "Track.h"
#include "Motor.h"
#include "Mecanum.h"
#include <math.h>

TrackSensor_t track_sensor;
float Track_Error;
float wheel_speed[4];
float last_error;       //保存丢线前一刻的偏差
uint8_t lose_line_flag = 0;
uint32_t lose_line_cnt = 0;


#define WHEEL_RADIUS 0.032f
#define L            0.08f
#define Kp_angle     0.25f    //角速度环P

#define V_MAX        40.0f    //直行最大速度
#define V_MIN        20.0f    //最低过弯速度
#define K_VEL        8.0f     //误差越大，速度衰减越强

#define BACK_SPEED   -16.0f   //后退速度，负数代表向后
#define BACK_COUNT    400      ////循环次数

void Track_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void Track_Read_IO(void)
{
	track_sensor.leftmost  = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	track_sensor.left      = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
	track_sensor.mid       = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
	track_sensor.right     = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
	track_sensor.rightmost = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
}


float Track_GetError_IO(void)
{
	int sum_w=0;
	int cnt=0;
	if(track_sensor.leftmost   == 0) {sum_w += -2;cnt++;}
	if(track_sensor.left       == 0) {sum_w += -1;cnt++;}
	if(track_sensor.mid        == 0) {sum_w +=  0;cnt++;}
	if(track_sensor.right      == 0) {sum_w += +1;cnt++;}
	if(track_sensor.rightmost  == 0) {sum_w += +2;cnt++;}
	
	if(cnt==0)
		return 0.0f;
	return (float)sum_w/cnt;
}

void Track_Run_IO(void)
{
    Track_Read_IO();
    Track_Error = Track_GetError_IO();

    //丢线保护
    uint8_t no_black = 1;
    if(track_sensor.leftmost  ==0) no_black =0;
    if(track_sensor.left      ==0) no_black =0;
    if(track_sensor.mid       ==0) no_black =0;
    if(track_sensor.right     ==0) no_black =0;
    if(track_sensor.rightmost ==0) no_black =0;

    //正常循迹状态，更新上一次有效偏差
    if(no_black == 0)
    {
        lose_line_flag = 0;
        last_error = Track_Error; //保存有效偏差
    }

    //丢线处理  后退
    if(no_black == 1)
    {
        if(lose_line_flag == 0)
        {
            lose_line_flag = 1;
            lose_line_cnt = 0;
        }

   
        if( lose_line_cnt < BACK_COUNT)//后退
        {
			lose_line_cnt ++;
			Mecanum_Calc(BACK_SPEED,0,0,wheel_speed);
			Motor_Set(wheel_speed[0],wheel_speed[1],wheel_speed[2],wheel_speed[3]);
            return;
        }
        else
        {
            Motor_AllStop();
            return;
        }
    }

    //偏差绝对值越大，前进速度越低
    float abs_err = fabs(Track_Error);
    float nowSpeed = V_MAX - K_VEL * abs_err;
    if(nowSpeed < V_MIN)
        nowSpeed = V_MIN;

    //位置偏差 → 目标角速度
    float omega_ref = Kp_angle * Track_Error;
    if(omega_ref > 1.2f) omega_ref = 1.2f;
    if(omega_ref < -1.2f) omega_ref = -1.2f;

	Mecanum_Calc(nowSpeed,0,omega_ref,wheel_speed);
	Motor_Set(wheel_speed[0],wheel_speed[1],wheel_speed[2],wheel_speed[3]);
}


