
#include "UltrasonicWave.h"


/*******************************************************************************
*�궨�����еĳ�������GPIO
*TRIG  EHCO  RCC  ����
 ******************************************************************************/

#define	TRIG1_PORT      GPIOD							//TRIG_1       
#define	ECHO1_PORT      GPIOD							//ECHO_1 
#define	TRIG1_PIN       GPIO_Pin_13         
#define	ECHO1_PIN       GPIO_Pin_12
#define RCC_TE1Periph   RCC_APB2Periph_GPIOD
#define TE1_NUM		1

#define	TRIG2_PORT      GPIOG							//TRIG_2       
#define	ECHO2_PORT      GPIOG							//ECHO_2 
#define	TRIG2_PIN       GPIO_Pin_7  	  	        
#define	ECHO2_PIN       GPIO_Pin_6	
#define RCC_TE2Periph   RCC_APB2Periph_GPIOG
#define TE2_NUM		2

#define	TRIG3_PORT      GPIOF							//TRIG_3       
#define	ECHO3_PORT      GPIOF							//ECHO_3 
#define	TRIG3_PIN       GPIO_Pin_13        
#define	ECHO3_PIN       GPIO_Pin_12	
#define RCC_TE3Periph   RCC_APB2Periph_GPIOF
#define TE3_NUM		3

#define	TRIG4_PORT      GPIOF							//TRIG_4       
#define	ECHO4_PORT      GPIOF							//ECHO_4
#define	TRIG4_PIN       GPIO_Pin_15        
#define	ECHO4_PIN       GPIO_Pin_14
#define RCC_TE4Periph   RCC_APB2Periph_GPIOF
#define TE4_NUM		4

#define	TRIG5_PORT      GPIOD							//TRIG_5       
#define	ECHO5_PORT      GPIOG							//ECHO_5 
#define	TRIG5_PIN       GPIO_Pin_11        
#define	ECHO5_PIN       GPIO_Pin_14
#define RCC_TE5Periph   RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG
#define TE5_NUM		5

#define	TRIG6_PORT      GPIOG							//TRIG_6       
#define	ECHO6_PORT      GPIOG							//ECHO_6 
#define	TRIG6_PIN       GPIO_Pin_13       
#define	ECHO6_PIN       GPIO_Pin_5
#define RCC_TE6Periph   RCC_APB2Periph_GPIOG
#define TE6_NUM		6

/*
 * ��������DelayTime_us
 * ����  ��1us��ʱ����
 * ����  ��Time   	��ʱ��ʱ�� US
 * ���  ����	
 */
void DelayTime_us(int Time)    
{
   unsigned char i;
   for ( ; Time>0; Time--)
     for ( i = 0; i < 72; i++ );
}

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ��������������GPIO��ʱ��
 * ���  ����	
 */
void UltrasonicWave_Configuration(GPIO_TypeDef* TRIG_PORT , uint16_t TRIG_PIN,\
																	GPIO_TypeDef* ECHO_PORT , uint16_t ECHO_PIN,\
																	uint32_t RCC_XXXPeriph)     
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_XXXPeriph, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     	//��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	               //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 		//��Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 			//��ʼ��GPIOA
}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  �������������ʱ��time���������Ĵ���num
 * ���  ����	
 */
void UltrasonicWave_CalculateTime(int time,int num)
{

	int UltrasonicWave_Distance=0;                        //��ʼ���������ľ������
	UltrasonicWave_Distance=time*5*34/2000;								//�������ľ���ת����ʽ
	UltrasonicWave_Distance=UltrasonicWave_Distance/256*100+UltrasonicWave_Distance%256;

 	switch(num)
	{
		case 1 :  LED_PrintValueFP_my(10, 4,UltrasonicWave_Distance,3);break;			//OLED��ʾ���
		case 2 :  LED_PrintValueFP_my(80, 4,UltrasonicWave_Distance,3);break;
		case 3 :  LED_PrintValueFP_my(80, 5,UltrasonicWave_Distance,3);break;
		case 4 :  LED_PrintValueFP_my(80, 6,UltrasonicWave_Distance,3);break;
		case 5 :  LED_PrintValueFP_my(10, 6,UltrasonicWave_Distance,3);break;
		case 6 :  LED_PrintValueFP_my(10, 5,UltrasonicWave_Distance,3);break;
	}
	//printf("%d ok  distance: %d\n",num,UltrasonicWave_Distance);
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����������GPIO
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(GPIO_TypeDef* TRIG_PORT , uint16_t TRIG_PIN,\
																	GPIO_TypeDef* ECHO_PORT , uint16_t ECHO_PIN,int TE_NUM)
{
	
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  DelayTime_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	
	
  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ
  TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
	
	
  UltrasonicWave_CalculateTime(TIM_GetCounter(TIM2),TE_NUM);									 //�������
  TIM_SetCounter(TIM2,0);
	DelayTime_us(1000);		
}

/*
 * ��������UltrasonicWave_Config
 * ����  ����ʼ�����еĳ�������GPIO
 * ����  ����
 * ���  ����	
 */

void UltrasonicWave_Config(void)																							
{
	UltrasonicWave_Configuration(TRIG1_PORT , TRIG1_PIN, ECHO1_PORT , ECHO1_PIN,RCC_TE1Periph) ;  //��ʼ��6��������
	UltrasonicWave_Configuration(TRIG2_PORT , TRIG2_PIN, ECHO2_PORT , ECHO2_PIN,RCC_TE2Periph) ;
	UltrasonicWave_Configuration(TRIG3_PORT , TRIG3_PIN, ECHO3_PORT , ECHO3_PIN,RCC_TE3Periph) ;
	UltrasonicWave_Configuration(TRIG4_PORT , TRIG4_PIN, ECHO4_PORT , ECHO4_PIN,RCC_TE4Periph) ;
	UltrasonicWave_Configuration(TRIG5_PORT , TRIG5_PIN, ECHO5_PORT , ECHO5_PIN,RCC_TE5Periph) ;
 	UltrasonicWave_Configuration(TRIG6_PORT , TRIG6_PIN, ECHO6_PORT , ECHO6_PIN,RCC_TE6Periph) ;
}

/*
 * ��������UltrasonicWave_Config
 * ����  ����ʼ�����еĳ�������GPIO
 * ����  ����
 * ���  ����	
 */

void UltrasonicWave_get(void)
{
 	UltrasonicWave_StartMeasure(TRIG1_PORT , TRIG1_PIN, ECHO1_PORT , ECHO1_PIN, TE1_NUM);   //��ѯ��ⳬ�����ľ���
 	UltrasonicWave_StartMeasure(TRIG2_PORT , TRIG2_PIN, ECHO2_PORT , ECHO2_PIN, TE2_NUM);
 	UltrasonicWave_StartMeasure(TRIG3_PORT , TRIG3_PIN, ECHO3_PORT , ECHO3_PIN, TE3_NUM);
 	UltrasonicWave_StartMeasure(TRIG4_PORT , TRIG4_PIN, ECHO4_PORT , ECHO4_PIN, TE4_NUM);
  UltrasonicWave_StartMeasure(TRIG5_PORT , TRIG5_PIN, ECHO5_PORT , ECHO5_PIN, TE5_NUM);
  UltrasonicWave_StartMeasure(TRIG6_PORT , TRIG6_PIN, ECHO6_PORT , ECHO6_PIN, TE6_NUM);
	printf("��������ȡ����ɹ�\n");
}




/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
