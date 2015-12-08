#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO       4	   
#define	TASK_LED2_PRIO					10
#define	TASK_LED3_PRIO					12 
#define	TASK_LED1_PRIO					11
#define	TASK_ultrawaves_PRIO		6      //超声波优先级
#define TASK_OLED_PRIO     		  8			 //OLED优先级
#define  TASK_Sensor_PRIO  		  7      //传感器
#define TASK_key_PRIO     		  5       //按键
#define TASK_TIM_PRIO    				9       //定时器（计时用）
#define TASK_PWM_PRIO           13      //PWM输出



/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   		80   				//启动任务的堆栈大小
#define	TASK_LED2_STK_SIZE					80					//LED2的堆栈大小
#define	TASK_LED3_STK_SIZE					80					//LED3的堆栈大小
#define	TASK_LED1_STK_SIZE					80					//LED1的堆栈大小
#define TASK_ultrawaves_STK_SIZE    80					//超声波的堆栈大小
#define TASK_OLED_STK_SIZE      		150					//OLED的堆栈大小
#define  TASK_Sensor_STK_SIZE   		500					//传感器的堆栈大小	
#define  TASK_key_STK_SIZE   				50					//按键的堆栈大小
#define  TASK_PWM_STK_SIZE 					300					//定时器（PWM）的堆栈大小



#endif

