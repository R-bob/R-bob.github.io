#ifndef __PWM_H
#define __PWM_H


#include "stm32f10x.h"
#include "usart1.h"
void TIM3_GPIO_Config(void);
void TIM3_Mode_Config(void);
void TIM3_Pwm_Init(void);

#endif
