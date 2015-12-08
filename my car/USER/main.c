/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：建立3个任务，每个任务控制一个LED，以固定的频率轮流闪烁（频率可调）。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.0.0
 *
 * 作者    ：fire  QQ: 313303034 
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/	

#include "includes.h"

OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //定义栈

  
int main(void)
{
	OS_EVENT *sem;
	sem=OSSemCreate(1);
  BSP_Init(); 
	OSInit();
	
	printf("*************系统初始化完成*****************\n\n");
	OSTaskCreate(Task_Start,(void *)0, //第二个是*Pdata                                  //Task Start为任务指针   *Pdata是当任务开始执行时传递给任务的参数的指针   
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);      // &startup_task_stk[STARTUP_TASK_STK_SIZE-1]分配给任务的堆栈的堆栈顶指针     STARTUP_TASK_PRIO分配给任务的优先级
	printf("*************系统准备进入状态*****************\n\n");
	OSStart();
  return 0;
 }

/******************* (C) COPYRIGHT 2011 野火嵌入式开发工作室 *****END OF FILE****/
