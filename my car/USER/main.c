/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    ������3������ÿ���������һ��LED���Թ̶���Ƶ��������˸��Ƶ�ʿɵ�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/	

#include "includes.h"

OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //����ջ

  
int main(void)
{
  BSP_Init(); 
	OSInit();
	printf("*************ϵͳ��ʼ�����*****************\n\n");
	OSTaskCreate(Task_Start,(void *)0, //�ڶ�����*Pdata                                  //Task StartΪ����ָ��   *Pdata�ǵ�����ʼִ��ʱ���ݸ�����Ĳ�����ָ��   
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);      // &startup_task_stk[STARTUP_TASK_STK_SIZE-1]���������Ķ�ջ�Ķ�ջ��ָ��     STARTUP_TASK_PRIO�������������ȼ�
	printf("*************ϵͳ׼������״̬*****************\n\n");
	OSStart();
  return 0;
 }

/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
