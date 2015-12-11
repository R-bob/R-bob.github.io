#ifndef __PWM_H
#define __PWM_H


#include "stm32f10x.h"
#include "usart1.h"



void Delay_us(int Time) ;
void TIM3_GPIO_Config(void);
void TIM3_Mode_Config(void);
void TIM3_Pwm_Init(void);
void PWM_output(int MotoL_1, int MotoL_2, int MotoR_1, int MotoR_2);
void UltraDataAnaly_To_Pwm(int UltraDistance1,int UltraDistance2,int UltraDistance3,int UltraDistance4,int UltraDistance5,int UltraDistance6);


#endif
