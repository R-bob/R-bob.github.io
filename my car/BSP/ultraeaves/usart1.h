#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#include "misc.h"

void USART1_Config(void);
void NVIC_Configuration(void);

void USART1_CONFIG(void);
int fputc(int ch, FILE *f);
void Usart_data_to_sbq(uint8_t data);

#endif /* __USART1_H */





