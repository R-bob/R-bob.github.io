#ifndef __SENSOR_H
#define	__SENSOR_H

#include "stm32f10x.h"
#include "OLED.h"   
#include "usart1.h"
#include  "ucos_ii.h"  		//uC/OS-II系统函数头文件
#include  	"BSP.h"
#include "UltrasonicWave.h"
#include "os_cpu.h"


/*******************************************************************************
*宏定义所有的红外的GPIO
*DATA  
 ******************************************************************************/
#define INFRARED1_port  GPIOG
#define INFRARED1_pin  GPIO_Pin_3
#define INFRARED1_RCC  RCC_APB2Periph_GPIOG
#define INFRA1_num		1

#define INFRARED2_port  GPIOE
#define INFRARED2_pin  GPIO_Pin_3
#define INFRARED2_RCC  RCC_APB2Periph_GPIOE
#define INFRA2_num		2

#define INFRARED3_port  GPIOE
#define INFRARED3_pin  GPIO_Pin_4
#define INFRARED3_RCC  RCC_APB2Periph_GPIOE
#define INFRA3_num		3

#define INFRARED4_port  GPIOE
#define INFRARED4_pin  GPIO_Pin_1
#define INFRARED4_RCC  RCC_APB2Periph_GPIOE
#define INFRA4_num		4

#define INFRARED5_port  GPIOG
#define INFRARED5_pin  GPIO_Pin_2
#define INFRARED5_RCC  RCC_APB2Periph_GPIOG
#define INFRA5_num		5

#define INFRARED6_port  GPIOG
#define INFRARED6_pin  GPIO_Pin_4
#define INFRARED6_RCC  RCC_APB2Periph_GPIOG
#define INFRA6_num	 6






#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOC
#define DHT11_PIN     GPIO_Pin_5                 
#define DHT11_PORT		GPIOC 

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)
 //读取引脚的电平
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)

typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);
void DHT11_get(void);

void Delay_us(int Time);






void INFRARED_Get(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,int INFRA_num);
void INFRARED_GPIO_Config(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,uint32_t RCC_INFRAREDPeriph) ;
void INFRARED_Config(void);
void INFRARED_ALL_Get(void);

void Sensor_get(void);
void sensor_Config(void);








#endif // __SENSOR_H
