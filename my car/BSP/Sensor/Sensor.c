#include "sensor.h"

/*
 * ��������INFRARED_GPI O_Config(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,uint32_t RCC_INFRAREDPeriph)
 * ����  �������GPIO��ʼ������
 * ����  ��INFRARED_PORT ,INFRARED_PIN, RCC_INFRAREDPeriph  //IO�ں�ʱ��
 * ���  ����	
 */
void INFRARED_GPIO_Config(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,uint32_t RCC_INFRAREDPeriph)   //������ infrared
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_INFRAREDPeriph, ENABLE);

	GPIO_InitStructure.GPIO_Pin = INFRARED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(INFRARED_PORT, &GPIO_InitStructure);    

	GPIO_SetBits(INFRARED_PORT, INFRARED_PIN);

}
/*
 * ��������INFRARED_Config(void)
 * ����  ������ȫ������
 * ����  ����
 * ���  ����	
 */

void INFRARED_Config(void)
{
	INFRARED_GPIO_Config(INFRARED1_port,INFRARED1_pin,INFRARED1_RCC);   //��ʼ�����еĺ���
	INFRARED_GPIO_Config(INFRARED2_port,INFRARED2_pin,INFRARED2_RCC);		//INFRARED1��2��3��4��5��6; ����ͬ�ĺ���
	INFRARED_GPIO_Config(INFRARED3_port,INFRARED3_pin,INFRARED3_RCC);
	INFRARED_GPIO_Config(INFRARED4_port,INFRARED4_pin,INFRARED4_RCC);
	INFRARED_GPIO_Config(INFRARED5_port,INFRARED5_pin,INFRARED5_RCC);
	INFRARED_GPIO_Config(INFRARED6_port,INFRARED6_pin,INFRARED6_RCC);
}


/*
 * ��������INFRARED_Get(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,INFRA_num)
 * ����  �������û�ж�������
 * ����  �����⴫��������D0��IO�ڣ��������Ĵ���
 * ���  ����	
 */
void INFRARED_Get(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,int INFRA_num)
{		
	 //printf("�����ȡ�ɹ�");
	 if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED_PIN)==1)
	 {
			switch(INFRA_num)
			{
				case 1 :  LED_P6x8Char(0,4,'0');break;			//OLED��ʾ���
				case 2 :  LED_P6x8Char(70,4,'0');break;
				case 3 :  LED_P6x8Char(70,5,'0');break;
				case 4 :  LED_P6x8Char(70,6,'0');break;
				case 5 :  LED_P6x8Char(0,6,'0');break;
				case 6 :  LED_P6x8Char(0,5,'0');break;
			}
		 //printf("                      hongwai ok\n ");
		}
		else
		{
					switch(INFRA_num)
			{
				case 1 :  LED_P6x8Char(0,4,'1');break;			//OLED��ʾ���
				case 2 :  LED_P6x8Char(70,4,'1');break;
				case 3 :  LED_P6x8Char(70,5,'1');break;
				case 4 :  LED_P6x8Char(70,6,'1');break;
				case 5 :  LED_P6x8Char(0,6,'1');break;
				case 6 :  LED_P6x8Char(0,5,'1');break;
			}
			 //printf("                      hongwai ok\n ");
		}
}

/*
 * ��������INFRARED_ALL_Get(void)
 * ����  ������ɼ�
 * ����  ����
 * ���  ����	
 */
void INFRARED_ALL_Get(void)
{
	INFRARED_Get(INFRARED1_port,INFRARED1_pin,INFRA1_num);
	INFRARED_Get(INFRARED2_port,INFRARED2_pin,INFRA2_num);
	INFRARED_Get(INFRARED3_port,INFRARED3_pin,INFRA3_num);
	INFRARED_Get(INFRARED4_port,INFRARED4_pin,INFRA4_num);
	INFRARED_Get(INFRARED5_port,INFRARED5_pin,INFRA5_num);
	INFRARED_Get(INFRARED6_port,INFRARED6_pin,INFRA6_num);
}



/*
 * ��������DHT11_GPIO_Config(void)
 * ����  ����ʪ��ģ������
 * ����  ����
 * ���  ����	
 */
void DHT11_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE); 														   
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);		  
	GPIO_SetBits(DHT11_PORT, GPIO_Pin_6);	 
}

/*
 * ��������DHT11_Mode_IPU
 * ����  ��ʹDHT11-DATA���ű�Ϊ��������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	  GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

/*
 * ��������DHT11_Mode_Out_PP
 * ����  ��ʹDHT11-DATA���ű�Ϊ�������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
												 
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 	 
}

/* 
 * ��DHT11��ȡһ���ֽڣ�MSB����
 */
static uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
				while(DHT11_DATA_IN()==Bit_RESET);				/*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
	

		/*DHT11 ��26~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
		 *ͨ����� x us��ĵ�ƽ��������������״ ��x ���������ʱ 
		 */
		delay_us(40); //��ʱx us �����ʱ��Ҫ��������0������ʱ�伴��	   	  

		if(DHT11_DATA_IN()==Bit_SET)														/* x us����Ϊ�ߵ�ƽ��ʾ���ݡ�1�� */
		{
			while(DHT11_DATA_IN()==Bit_SET);											/* �ȴ�����1�ĸߵ�ƽ���� */
			temp|=(uint8_t)(0x01<<(7-i));  												//�ѵ�7-iλ��1��MSB���� 
		}
		else	 																										// x us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); 												//�ѵ�7-iλ��0��MSB����
		}
	}
	return temp;
}
/*
 * һ�����������ݴ���Ϊ40bit����λ�ȳ�
 * 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
 */
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	DHT11_Mode_Out_PP();	/*���ģʽ*/
	DHT11_DATA_OUT(LOW);	/*��������*/
	delay_ms(18);					/*��ʱ18ms*/
	DHT11_DATA_OUT(HIGH); /*�������� ������ʱ30us*/
	delay_us(30);   //��ʱ30us
	DHT11_Mode_IPU();/*������Ϊ���� �жϴӻ���Ӧ�ź�*/ 
	if(DHT11_DATA_IN()==Bit_RESET)     /*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
	{
		while(DHT11_DATA_IN()==Bit_RESET);					/*��ѯֱ���ӻ����� ��80us �͵�ƽ ��Ӧ�źŽ���*/  
		while(DHT11_DATA_IN()==Bit_SET);						/*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/												
		DHT11_Data->humi_int= Read_Byte();					/*��ʼ��������*/   
		DHT11_Data->humi_deci= Read_Byte();
		DHT11_Data->temp_int= Read_Byte();
		DHT11_Data->temp_deci= Read_Byte();
		DHT11_Data->check_sum= Read_Byte();
		DHT11_Mode_Out_PP();													/*��ȡ���������Ÿ�Ϊ���ģʽ*/
		DHT11_DATA_OUT(HIGH);													/*��������*/
		/*����ȡ�������Ƿ���ȷ*/
		if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
			return SUCCESS;
		else 
			return ERROR;
	}
	else
	{		
		return ERROR;
	}   
}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  �������������ʱ��time���������Ĵ���num
 * ���  ����	
 */
DHT11_Data_TypeDef DHT11_Data;
void DHT11_get(void)
{

	//OSTimeDlyHMSM(0, 0,10,0);
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
		//printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		//printf("\r\n ʪ��:%d,�¶�:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
		LCD_P8x16Str(0,2,"tem:");
		LCD_P8x16Str(70,2,"sid:");
		LED_PrintValueFP_my(30,3, DHT11_Data.humi_int, 3);
		LED_PrintValueFP_my(100,3, DHT11_Data.temp_int, 3);
		
		
	}
	else
	{
		//printf("Read DHT11 ERROR!\r\n");
		LCD_CLS_LINE(2) ;
		//LCD_P8x16Str(0,2,"dht11 error     ");
	}

}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  �������������ʱ��time���������Ĵ���num
 * ���  ����	
 */
void Sensor_get(void)
{
	//OS_CPU_SR cpu_sr;
	INFRARED_ALL_Get();
	//printf("ok");
	//OSSchedLock();	
// 	OS_ENTER_CRITICAL();	
// 	OS_EXIT_CRITICAL();
//DHT11_get();
//	OSSchedUnlock();
}


/*
 * ��������sensor_Config(void)
 * ����  �������������ú���
 * ����  ����
 * ���  ����	
 */
void sensor_Config(void)
{
	INFRARED_Config();
	//DHT11_GPIO_Config();

}

