/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * ����   �������ƴ�
 * �ļ���  ��scheduler.c
 * ����    ���������
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
**********************************************************************************/
#include "scheduler.h"
#include "include.h"
#include "time.h"
#include "mpu6050.h"
#include "ak8975.h"
#include "led.h"
#include "rc.h"
#include "imu.h"
#include "pwm_in.h"
#include "ctrl.h"
#include "ms5611.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "dht11.h"
#include "adc.h"
#include "filter.h"

s16 loop_cnt;

loop_t loop;

void Loop_check()  //TIME INTTERRUPT
{
	loop.time++; //u16
	loop.cnt_2ms++;
	loop.cnt_5ms++;
	loop.cnt_10ms++;
	loop.cnt_20ms++;
	loop.cnt_50ms++;
	loop.cnt_100ms++;
	loop.cnt_200ms++;
	loop.cnt_500ms++;
	loop.cnt_950ms++;
	loop.cnt_1000ms++;	

	if( loop.check_flag == 1)
	{
		loop.err_flag ++;     //ÿ�ۼ�һ�Σ�֤��������Ԥ��������û�����ꡣ
	}
	else
	{	
		loop.check_flag = 1;	//�ñ�־λ��ѭ�����������
	}
}

void Duty_1ms()
{
	Get_Cycle_T(1);
	LED_Display( LED_Brightness );								//20��led������ʾ
	ANO_DT_Data_Exchange();												//����ͨ�Ŷ�ʱ����
}

float test[5];
void Duty_2ms()
{
	float inner_loop_time;
	
	inner_loop_time = Get_Cycle_T(0); 						//��ȡ�ڻ�׼ȷ��ִ������
	
	test[0] = GetSysTime_us()/1000000.0f;
	
	MPU6050_Read(); 															//��ȡmpu6�ᴫ����

	MPU6050_Data_Prepare( inner_loop_time );			//mpu6�ᴫ�������ݴ���

	CTRL_1( inner_loop_time ); 										//�ڻ����ٶȿ��ơ����룺ִ�����ڣ��������ٶȣ��������ٶȣ��Ƕ�ǰ������������PWMռ�ձȡ�<����δ��װ>
	
	RC_Duty( inner_loop_time , Rc_Pwm_In );				// ң����ͨ�����ݴ��� �����룺ִ�����ڣ����ջ�pwm��������ݡ�
	
	
	
	test[1] = GetSysTime_us()/1000000.0f;
}

void Duty_5ms()
{
	float outer_loop_time;
	
	outer_loop_time = Get_Cycle_T(2);								//��ȡ�⻷׼ȷ��ִ������
	
	test[2] = GetSysTime_us()/1000000.0f;
	
	/*IMU������̬�����룺���ִ�����ڣ��������������ݣ�ת������ÿ�룩��������ٶȼ����ݣ�4096--1G���������ROLPITYAW��̬��*/
 	IMUupdate(0.5f *outer_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);

 	CTRL_2( outer_loop_time ); 											// �⻷�Ƕȿ��ơ����룺ִ�����ڣ������Ƕȣ�ҡ����������̬�Ƕȣ�������������ٶȡ�<����δ��װ>
	
	test[3] = GetSysTime_us()/1000000.0f;
	deepth_adc=Get_Adc(2);
	deepth=((deepth_adc*V_REF/4096.0f)-0.5f)*100000.0f/4.0f;    //�������ֵ
//	d5=Get_Adc(2);
	deepth_send=deepth;
	deepth_send=Moving_Median(2,9,d5);
//		d5+= ( 1 / ( 1 + 1 / ( 0.2f *3.14f *5 ) ) ) *(0 - d5);	
}

void Duty_10ms()
{
 		if( MS5611_Update() ) 				//����ms5611��ѹ������
		{	
			baro_ctrl_start = 1;  //20ms
		}
		
	  ANO_AK8975_Read();			//��ȡ������������	
}

void Duty_20ms()
{
	Parameter_Save();
	
}

void Duty_50ms()
{
	Mode();
	LED_Duty();								//LED����
	Ultra_Duty();

}
void Duty_100ms()
{
	DHT11_Rst2();
}
void Duty_200ms()
{
	d6=DHT11_Read_Data(&temperature,&humidity);
	if(!d6)
	{
		temperature_send=temperature;   //d7=temperature+1;
		humidity_send=humidity;
	}
//	d5=Get_Adc(2);	
}
void Duty_500ms()
{


}
void Duty_1000ms()
{
//	d5=DHT11_Check();

}
void Duty_Loop()   					//�����������Ϊ1ms���ܵĴ���ִ��ʱ����ҪС��1ms��
{

	if( loop.check_flag == 1 )
	{
		loop_cnt = time_1ms;
		
		Duty_1ms();							//����1ms������
		
		if( loop.cnt_2ms >= 2 )
		{
			loop.cnt_2ms = 0;
			Duty_2ms();						//����2ms������
		}
		if( loop.cnt_5ms >= 5 )
		{
			loop.cnt_5ms = 0;
			Duty_5ms();						//����5ms������
		}
		if( loop.cnt_10ms >= 10 )
		{
			loop.cnt_10ms = 0;
			Duty_10ms();					//����10ms������
		}
		if( loop.cnt_20ms >= 20 )
		{
			loop.cnt_20ms = 0;
			Duty_20ms();					//����20ms������
		}
		if( loop.cnt_50ms >= 50 )
		{
			loop.cnt_50ms = 0;
			Duty_50ms();					//����50ms������
		}
		if( loop.cnt_100ms >= 100 )
		{
			loop.cnt_100ms = 0;
			Duty_100ms();					//����50ms������
		}		
		if( loop.cnt_200ms >= 200 )
		{
			loop.cnt_200ms = 0;
			Duty_200ms();					//����50ms������
		}			
		if( loop.cnt_950ms >= 950 )
		{
			loop.cnt_950ms = 0;
				DHT11_Rst2();					//����50ms������
		}		
		if( loop.cnt_1000ms >= 1000 )
		{
			loop.cnt_1000ms = 0;
			Duty_1000ms();					//����50ms������
		}		
		loop.check_flag = 0;		//ѭ��������ϱ�־
	}
}




	/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
	

