#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_Motor_SetCompare1(uint16_t Compare);
void PWM_Motor_SetCompare2(uint16_t Compare);
void PWM_Motor_SetCompare3(uint16_t Compare);
void PWM_Motor_SetCompare4(uint16_t Compare);
void PWM_Servo_SetCompare3(uint16_t Compare);

#endif
