#include "includes.h"
#include <stdio.h>




OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //定义栈
OS_STK task_led3_stk[TASK_LED3_STK_SIZE];		  //定义栈
OS_STK task_led1_stk[TASK_LED1_STK_SIZE];
OS_STK task_ultrawaves_stk[TASK_ultrawaves_STK_SIZE];  //超声波堆栈
OS_STK task_OLED_stk[TASK_OLED_STK_SIZE];           //OLED堆栈
OS_STK task_Sensor_stk[TASK_Sensor_STK_SIZE];           //传感器堆栈
OS_STK task_key_stk[TASK_key_STK_SIZE]; 								//按键的堆栈
OS_STK task_PWM_stk[TASK_PWM_STK_SIZE]; 



OS_EVENT *sem;
INT8U error;


void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
	SysTick_init();

	OSTaskCreate(Task_LED2,(void *)0,		  																		//创建任务2
	   &task_led2_stk[TASK_LED2_STK_SIZE-1], TASK_LED2_PRIO);  								 //

	OSTaskCreate(Task_LED3,(void *)0,		   																			//创建任务3
	   &task_led3_stk[TASK_LED3_STK_SIZE-1], TASK_LED3_PRIO);
	
	OSTaskCreate(Task_LED1,(void *)0,
			&task_led1_stk[TASK_LED1_STK_SIZE-1],TASK_LED1_PRIO);
	
	OSTaskCreate(Task_ultrawaves,(void *)0,
			&task_ultrawaves_stk[TASK_ultrawaves_STK_SIZE-1],TASK_ultrawaves_PRIO);             //创建超声波任务
		
		OSTaskCreate(Task_OLED,(void *)0,
		 &task_OLED_stk[TASK_OLED_STK_SIZE-1],TASK_OLED_PRIO);                               //创建OLED任务
		 
	OSTaskCreate(Task_Sensor,(void *)0,
		 &task_Sensor_stk[TASK_Sensor_STK_SIZE-1],TASK_Sensor_PRIO);                        //创建传感器任务

	OSTaskCreate(Task_key,(void *)0,
		 &task_key_stk[TASK_key_STK_SIZE-1],TASK_key_PRIO); 																	//创建按键任务
		
	OSTaskCreate(Task_PWM,(void *)0,																												//创建输出PWM任务
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
			
			printf("进入led1任务\n\n");
      LED1( ON );
      OSTimeDlyHMSM(0, 0,0,500);
      LED1( OFF);
			
			printf("退出led1任务\n\n");
			
    }
}




//任务2
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
	SysTick_init();
	
    while (1)
    {			
			printf("进入led2任务\n\n");
			LED2( ON );
      OSTimeDlyHMSM(0, 0,0,999);
      LED2( OFF); 
			printf("退出led2任务\n\n");
    }
}

//任务3
void Task_LED3(void *p_arg)
{
    (void)p_arg;      
	SysTick_init();
	
    while (1)
    {
			  printf("进入led3任务\n\n");
        LED3( ON );
        OSTimeDlyHMSM(0, 0,0,300);
        LED3( OFF);
				OSTimeDlyHMSM(0, 0,0,300);    
				printf("退出led2任务\n\n");			
    }
}


//任务4  采集超声波的信号，得出距离
void Task_ultrawaves(void *p_arg)
{
	  (void)p_arg;      
		SysTick_init();
		for(;;)
	{
		OSSemPend( sem, 0, &error ); 
		printf("进入超声波任务\n\n");
	  UltrasonicWave_get();
		OSTimeDlyHMSM(0,0,0,50);
		OSSemPost( sem );
		printf("退出超声波任务\n\n");			
	}
}


void Task_OLED(void *p_arg)
{
		(void)p_arg;
		SysTick_init();
		while(1)
		{
			OSSemPend( sem, 0, &error ); 
			printf("进入OLED任务\n\n");
			OSTimeDlyHMSM(0, 0,0,50);
			OSSemPost( sem );
			printf("退出OLED任务\n\n");			
		}
}

void Task_Sensor(void *p_arg)
{
			(void)p_arg;
		SysTick_init();
		delay_init();
		while(1)
		{
			OSSemPend( sem, 0, &error ); 
			printf("进入传感器采集任务\n\n");
			Sensor_get();
			OSTimeDlyHMSM(0, 0,0,200);
			printf("退出传感器采集任务\n\n");		
			OSSemPost( sem );			
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
			OSSemPend( sem, 0, &error ); 
			printf("进入PWM输出任务\n\n");
			PWM_output(0, 70, 0,70);
			OSTimeDlyHMSM(0, 0,0,200);
			printf("退出PWM输出任务\n\n");	
			OSSemPost( sem );			
		}
}


















