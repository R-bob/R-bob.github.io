#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

#include "stm32f10x.h"
#include "usart1.h"
#include "TIM2.h"
#include "OLED.h"    

void UltrasonicWave_Configuration(GPIO_TypeDef* TRIG_PORT , uint16_t TRIG_PIN,
																	GPIO_TypeDef* ECHO_PORT , uint16_t ECHO_PIN,
																	uint32_t RCC_XXXPeriph);                //对超声波模块初始化
																	
void UltrasonicWave_StartMeasure(GPIO_TypeDef* TRIG_PORT , uint16_t TRIG_PIN,\
																	GPIO_TypeDef* ECHO_PORT , uint16_t ECHO_PIN,int TE_NUM);               //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间

void UltrasonicWave_CalculateTime(int time,int num);
void UltrasonicWave_Config(void);
void UltrasonicWave_get(void);

#define CMD_WARE     3

#endif /* __UltrasonicWave_H */

