#ifndef __ADC0832_H
#define __ADC0832_H
#include "stm32f4xx.h"

#define ACK GPIO_Pin_3
#define ADO GPIO_Pin_9
#define ACS GPIO_Pin_2

#define uchar unsigned char
#define uint unsigned int
typedef  char            int8;      //  -128~127
typedef  unsigned char  uint8;      //  0~255
typedef  int            int16;      //  -32768~32767
typedef  unsigned int   uint16;     //  0~65535
typedef  long           int32;      //  -2147483648~2147483647
typedef  unsigned long  uint32;     //  0~4294967295

void ADC0832_Init(void);
void DIN_Configuration(void);
void DOUT_Configuration(void);
uchar ADC0832_Read(uchar ch);

#endif
