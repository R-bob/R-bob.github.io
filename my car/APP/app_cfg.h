#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************�����������ȼ�*******************/
#define STARTUP_TASK_PRIO       4	   
#define	TASK_LED2_PRIO					10
#define	TASK_LED3_PRIO					12 
#define	TASK_LED1_PRIO					11
#define	TASK_ultrawaves_PRIO		6      //���������ȼ�
#define TASK_OLED_PRIO     		  8			 //OLED���ȼ�
#define  TASK_Sensor_PRIO  		  7      //������
#define TASK_key_PRIO     		  5       //����
#define TASK_TIM_PRIO    				9       //��ʱ������ʱ�ã�
#define TASK_PWM_PRIO           13      //PWM���



/************����ջ��С����λΪ OS_STK ��************/
#define STARTUP_TASK_STK_SIZE   		80   				//��������Ķ�ջ��С
#define	TASK_LED2_STK_SIZE					80					//LED2�Ķ�ջ��С
#define	TASK_LED3_STK_SIZE					80					//LED3�Ķ�ջ��С
#define	TASK_LED1_STK_SIZE					80					//LED1�Ķ�ջ��С
#define TASK_ultrawaves_STK_SIZE    80					//�������Ķ�ջ��С
#define TASK_OLED_STK_SIZE      		150					//OLED�Ķ�ջ��С
#define  TASK_Sensor_STK_SIZE   		500					//�������Ķ�ջ��С	
#define  TASK_key_STK_SIZE   				50					//�����Ķ�ջ��С
#define  TASK_PWM_STK_SIZE 					300					//��ʱ����PWM���Ķ�ջ��С



#endif

