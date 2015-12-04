#include "PWM.h"

//��ʼ��GPIO�Ͷ�ʱ��
//��ʱ��TIM3�ĸ��ù��ܣ����PWM

static void TIM3_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//��ʼ��GPIOʱ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOG, ENABLE); 
	
	
	//PB0 TIM3_CH3
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);     
  	
	//PB1 TIM3_CH4
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 


	//PA6 TIM3_CH1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;printf("ok\n");
 
  GPIO_Init(GPIOA, &GPIO_InitStructure);printf("lalala\n");       
	
			
	//PA7 TIM3_CH2
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		
		//�������Ŀ���IO�� PG0 / PG1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
		
		
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//GPIO_ResetBits(GPIOG, GPIO_Pin_1|GPIO_Pin_0);	
	GPIO_SetBits(GPIOG, GPIO_Pin_1|GPIO_Pin_0);	
  
}



// static void NVIC_Config_PWM(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
//   
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//   
//   /* ����TIM3_IRQ�ж�Ϊ�ж�Դ */
//   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);

// }


//����TIM3 Mode

static void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	/* ����TIM3CLK ʱ��Ϊ72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 		//ʹ��TIM3ʱ��
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
 
  /* ������ʱ������ */		 
  TIM_TimeBaseStructure.TIM_Period = 255;       							  //����ʱ����0������255����Ϊ266�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 1999;	    							//����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  //TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  /* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse =0;										  			//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ
	
	//ʹ��ͨ��1   PA6
	TIM_OCInitStructure.TIM_Pulse =155;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);						//ʹ��Ԥװ��		
	
	//ʹ��ͨ��2    PA7
	TIM_OCInitStructure.TIM_Pulse =155;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);						//ʹ��Ԥװ��	

  //ʹ��ͨ��3	  PB0 
	TIM_OCInitStructure.TIM_Pulse =110;										  				 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);						//ʹ��Ԥװ��	

  //ʹ��ͨ��4	  PB1
	TIM_OCInitStructure.TIM_Pulse =110;										  				 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);						//ʹ��Ԥװ��	


  TIM_ARRPreloadConfig(TIM3, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
  //TIM_ARRPreloadConfig(TIM2, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   										//ʹ�ܶ�ʱ��3	
	//TIM_Cmd(TIM2, ENABLE);
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);										//ʹ��update�ж�
	//TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
	//NVIC_Config_PWM();																					//�����ж����ȼ�		

}

void TIM3_Pwm_Init(void)
{
	TIM3_GPIO_Config();	 
	
	TIM3_Mode_Config();
}



