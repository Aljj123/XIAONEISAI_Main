#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor_SetSpeed( uint8_t motor,float Speed);
void Motor_Set(float w1,float w2,float w3,float w4);
#endif
