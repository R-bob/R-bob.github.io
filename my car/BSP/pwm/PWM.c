#include "PWM.h"


void Delay_us(int Time)    
{
   unsigned char i;
   for ( ; Time>0; Time--)
     for ( i = 0; i < 72; i++ );
}


//初始化GPIO和定时器
//定时器TIM3的复用功能，输出PWM

static void TIM3_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//初始化GPIO时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOG, ENABLE); 
	
	
	//PB0 TIM3_CH3
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);     
  	
	//PB1 TIM3_CH4
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 


	//PA6 TIM3_CH1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;printf("ok\n");
 
  GPIO_Init(GPIOA, &GPIO_InitStructure);printf("lalala\n");       
	
			
	//PA7 TIM3_CH2
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		
		//定义电机的控制IO口 PG0 / PG1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
		
		
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOG, GPIO_Pin_1|GPIO_Pin_0);	
	//GPIO_SetBits(GPIOG, GPIO_Pin_1|GPIO_Pin_0);	
  
}



// static void NVIC_Config_PWM(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
//   
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//   
//   /* 配置TIM3_IRQ中断为中断源 */
//   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// }


//配置TIM3 Mode

static void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	/* 设置TIM3CLK 时钟为72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 		//使能TIM3时钟
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
 
  /* 基本定时器配置 */		 
  TIM_TimeBaseStructure.TIM_Period = 255;       							  //当定时器从0计数到255，即为266次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 1999;	    							//设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  //TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  /* PWM模式配置 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
  TIM_OCInitStructure.TIM_Pulse =0;										  			//设置初始PWM脉冲宽度为0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //当定时器计数值小于CCR1_Val时为低电平
	
	//使能通道1   PA6
	TIM_OCInitStructure.TIM_Pulse =0;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);						//使能预装载		
	
	//使能通道2    PA7
	TIM_OCInitStructure.TIM_Pulse =0;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);						//使能预装载	

  //使能通道3	  PB0 
	TIM_OCInitStructure.TIM_Pulse =0;										  				 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);						//使能预装载	

  //使能通道4	  PB1
	TIM_OCInitStructure.TIM_Pulse =0;										  				 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);						//使能预装载	


  TIM_ARRPreloadConfig(TIM3, ENABLE);			 										//使能TIM3重载寄存器ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   										//使能定时器3	
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);										//使能update中断
	
	//NVIC_Config_PWM();																					//配置中断优先级		

}

void PWM_output(int MotoL_1, int MotoL_2, int MotoR_1, int MotoR_2)
{
	GPIO_SetBits(GPIOG, GPIO_Pin_0);	
	GPIO_SetBits(GPIOG, GPIO_Pin_1);	
	TIM3->CCR1=MotoL_1;
	TIM3->CCR2=MotoL_2;
	TIM3->CCR3=MotoR_1;
	TIM3->CCR4=MotoR_2;
	Delay_us(1000);

}

void UltraDataAnaly_To_Pwm(int UltraDistance1,int UltraDistance2,int UltraDistance3,int UltraDistance4,int UltraDistance5,int UltraDistance6)
{
	int MotoL_1, MotoL_2, MotoR_1, MotoR_2;
	
}



void TIM3_Pwm_Init(void)
{
	TIM3_GPIO_Config();	 
	
	TIM3_Mode_Config();
}



