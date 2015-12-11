#ifndef	_APP_H_
#define	_APP_H_

/**************** 用户任务声明 *******************/
void Task_Start(void *p_arg);
void Task_LED1(void *p_arg);
void Task_LED2(void *p_arg);
void Task_LED3(void *p_arg);
void Task_ultrawaves(void *p_arg);
void Task_OLED(void *p_arg);
void Task_Sensor(void *p_arg);
void Task_key(void *p_arg);
void Task_PWM(void *p_arg);
#endif	//_APP_H_
