#ifndef __BSP_H
#define	__BSP_H

void SysTick_init(void);
void BSP_Init(void);
void delay_init(void)	 ;
void delay_us(u32 nus);
void delay_ms(u16 nms);


#endif // __BSP_H
