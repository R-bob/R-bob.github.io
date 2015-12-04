#include "includes.h"
#include <stdio.h>




OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //����ջ
OS_STK task_led3_stk[TASK_LED3_STK_SIZE];		  //����ջ
OS_STK task_led1_stk[TASK_LED1_STK_SIZE];
OS_STK task_ultrawaves_stk[TASK_ultrawaves_STK_SIZE];  //��������ջ
OS_STK task_OLED_stk[TASK_OLED_STK_SIZE];           //OLED��ջ
OS_STK task_Sensor_stk[TASK_Sensor_STK_SIZE];           //��������ջ
OS_STK task_key_stk[TASK_key_STK_SIZE]; 								//�����Ķ�ջ
OS_STK task_PWM_stk[TASK_PWM_STK_SIZE]; 



void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' ��û���õ�����ֹ��������ʾ����
	SysTick_init();

	OSTaskCreate(Task_LED2,(void *)0,		  																		//��������2
	   &task_led2_stk[TASK_LED2_STK_SIZE-1], TASK_LED2_PRIO);  								 //

	OSTaskCreate(Task_LED3,(void *)0,		   																			//��������3
	   &task_led3_stk[TASK_LED3_STK_SIZE-1], TASK_LED3_PRIO);
	
	OSTaskCreate(Task_LED1,(void *)0,
			&task_led1_stk[TASK_LED1_STK_SIZE-1],TASK_LED1_PRIO);
	
	OSTaskCreate(Task_ultrawaves,(void *)0,
			&task_ultrawaves_stk[TASK_ultrawaves_STK_SIZE-1],TASK_ultrawaves_PRIO);             //��������������
		
		OSTaskCreate(Task_OLED,(void *)0,
		 &task_OLED_stk[TASK_OLED_STK_SIZE-1],TASK_OLED_PRIO);                               //����OLED����
		 
	OSTaskCreate(Task_Sensor,(void *)0,
		 &task_Sensor_stk[TASK_Sensor_STK_SIZE-1],TASK_Sensor_PRIO);                        //��������������

	OSTaskCreate(Task_key,(void *)0,
		 &task_key_stk[TASK_key_STK_SIZE-1],TASK_key_PRIO); 																	//������������
		
	OSTaskCreate(Task_PWM,(void *)0,																												//�������PWM����
		 &task_PWM_stk[TASK_PWM_STK_SIZE-1],TASK_PWM_PRIO);  		 
	
		 
		 
		 

    while (1)
    {
		OSTimeDlyHMSM(0, 0,0,100);     
    }
}


void Task_LED1(void *p_arg)
{
	    (void)p_arg;                	
	SysTick_init();
	    while (1)
    {
			printf("����led1����\n\n");
        LED1( ON );
        OSTimeDlyHMSM(0, 0,0,500);
        LED1( OFF);
		OSTimeDlyHMSM(0, 0,0,500);	
			printf("�˳�led1����\n\n");
    }
}




//����2
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {
			printf("����led2����\n\n");
			  LED2( ON );
        OSTimeDlyHMSM(0, 0,0,999);
        LED2( OFF);
		OSTimeDlyHMSM(0, 0,0,999);	
			printf("�˳�led2����\n\n");
    }
}

//����3
void Task_LED3(void *p_arg)
{
    (void)p_arg;      
	SysTick_init();
	
    while (1)
    {
			   printf("����led3����\n\n");
        LED3( ON );
         OSTimeDlyHMSM(0, 0,0,300);
        LED3( OFF);
				OSTimeDlyHMSM(0, 0,0,300);    
				printf("�˳�led2����\n\n");			
    }
}


//����4  �ɼ����������źţ��ó�����
void Task_ultrawaves(void *p_arg)
{
	  (void)p_arg;      
		SysTick_init();
		for(;;)
	{
		printf("���볬��������\n\n");
	  UltrasonicWave_get();
		OSTimeDlyHMSM(0,0,0,400);
		printf("�˳�����������\n\n");			
	}
}


void Task_OLED(void *p_arg)
{
		(void)p_arg;
		SysTick_init();
		while(1)
		{
			printf("����OLED����\n\n");
			//LCD_Print(0,0,"     welcome"); 
			OSTimeDlyHMSM(0, 0,0,50);
			printf("�˳�OLED����\n\n");			
		}
}

void Task_Sensor(void *p_arg)
{
			(void)p_arg;
		SysTick_init();
		delay_init();
		while(1)
		{
			printf("ϵͳ���봫�����ɼ�����\n\n");
			Sensor_get();
			OSTimeDlyHMSM(0, 0,0,200);
			printf("ϵͳ�˳��������ɼ�����\n\n");			
		}
}



void Task_key(void *p_arg)
{
			(void)p_arg;
		SysTick_init();
		while(1)
		{
			OSTimeDlyHMSM(0, 0,0,200);
		}
}


void Task_PWM(void *p_arg)
{
			(void)p_arg;
		SysTick_init();
		while(1)
		{
			printf("����PWM�������\n\n");
			OSTimeDlyHMSM(0, 0,1,500);
			printf("�˳�PWM�������\n\n");			
		}
}


















