#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void Motor_SetPWM1(uint16_t pwm);
void Motor_SetPWM2(uint16_t pwm);
void Motor_SetPWM3(uint16_t pwm);
void Motor_SetPWM4(uint16_t pwm);



void Servo_Set1(uint16_t val);
void Servo_Set2(uint16_t val);
void Servo_Set3(uint16_t val);
void Servo_Set4(uint16_t val);
void Servo_Set5(uint16_t val);
#endif
