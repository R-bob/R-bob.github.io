#include "sensor.h"

/*
 * 函数名：INFRARED_GPI O_Config(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,uint32_t RCC_INFRAREDPeriph)
 * 描述  ：红外的GPIO初始化函数
 * 输入  ：INFRARED_PORT ,INFRARED_PIN, RCC_INFRAREDPeriph  //IO口和时钟
 * 输出  ：无	
 */
void INFRARED_GPIO_Config(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,uint32_t RCC_INFRAREDPeriph)   //红外线 infrared
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
 * 函数名：INFRARED_Config(void)
 * 描述  ：配置全部红外
 * 输入  ：无
 * 输出  ：无	
 */

void INFRARED_Config(void)
{
	INFRARED_GPIO_Config(INFRARED1_port,INFRARED1_pin,INFRARED1_RCC);   //初始化所有的红外
	INFRARED_GPIO_Config(INFRARED2_port,INFRARED2_pin,INFRARED2_RCC);		//INFRARED1，2，3，4，5，6; 代表不同的红外
	INFRARED_GPIO_Config(INFRARED3_port,INFRARED3_pin,INFRARED3_RCC);
	INFRARED_GPIO_Config(INFRARED4_port,INFRARED4_pin,INFRARED4_RCC);
	INFRARED_GPIO_Config(INFRARED5_port,INFRARED5_pin,INFRARED5_RCC);
	INFRARED_GPIO_Config(INFRARED6_port,INFRARED6_pin,INFRARED6_RCC);
}


/*
 * 函数名：INFRARED_Get(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,INFRA_num)
 * 描述  ：检测有没有东西靠近
 * 输入  ：红外传感器检测的D0的IO口，传感器的代号
 * 输出  ：无	
 */
void INFRARED_Get(GPIO_TypeDef* INFRARED_PORT , uint16_t INFRARED_PIN,int INFRA_num)
{		
	 //printf("红外读取成功");
	 if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED_PIN)==1)
	 {
			switch(INFRA_num)
			{
				case 1 :  LED_P6x8Char(0,4,'0');break;			//OLED显示结果
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
				case 1 :  LED_P6x8Char(0,4,'1');break;			//OLED显示结果
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
 * 函数名：INFRARED_ALL_Get(void)
 * 描述  ：红外采集
 * 输入  ：无
 * 输出  ：无	
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
 * 函数名：DHT11_GPIO_Config(void)
 * 描述  ：温湿度模块配置
 * 输入  ：无
 * 输出  ：无	
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
 * 函数名：DHT11_Mode_IPU
 * 描述  ：使DHT11-DATA引脚变为上拉输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	  GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

/*
 * 函数名：DHT11_Mode_Out_PP
 * 描述  ：使DHT11-DATA引脚变为推挽输出模式
 * 输入  ：无
 * 输出  ：无
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
 * 从DHT11读取一个字节，MSB先行
 */
static uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
				while(DHT11_DATA_IN()==Bit_RESET);				/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
	

		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 *通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
		 */
		delay_us(40); //延时x us 这个延时需要大于数据0持续的时间即可	   	  

		if(DHT11_DATA_IN()==Bit_SET)														/* x us后仍为高电平表示数据“1” */
		{
			while(DHT11_DATA_IN()==Bit_SET);											/* 等待数据1的高电平结束 */
			temp|=(uint8_t)(0x01<<(7-i));  												//把第7-i位置1，MSB先行 
		}
		else	 																										// x us后为低电平表示数据“0”
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); 												//把第7-i位置0，MSB先行
		}
	}
	return temp;
}
/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	DHT11_Mode_Out_PP();	/*输出模式*/
	DHT11_DATA_OUT(LOW);	/*主机拉低*/
	delay_ms(18);					/*延时18ms*/
	DHT11_DATA_OUT(HIGH); /*总线拉高 主机延时30us*/
	delay_us(30);   //延时30us
	DHT11_Mode_IPU();/*主机设为输入 判断从机响应信号*/ 
	if(DHT11_DATA_IN()==Bit_RESET)     /*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
	{
		while(DHT11_DATA_IN()==Bit_RESET);					/*轮询直到从机发出 的80us 低电平 响应信号结束*/  
		while(DHT11_DATA_IN()==Bit_SET);						/*轮询直到从机发出的 80us 高电平 标置信号结束*/												
		DHT11_Data->humi_int= Read_Byte();					/*开始接收数据*/   
		DHT11_Data->humi_deci= Read_Byte();
		DHT11_Data->temp_int= Read_Byte();
		DHT11_Data->temp_deci= Read_Byte();
		DHT11_Data->check_sum= Read_Byte();
		DHT11_Mode_Out_PP();													/*读取结束，引脚改为输出模式*/
		DHT11_DATA_OUT(HIGH);													/*主机拉高*/
		/*检查读取的数据是否正确*/
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
 * 函数名：UltrasonicWave_CalculateTime
 * 描述  ：计算距离
 * 输入  ：超声波测出的时间time，超声波的代号num
 * 输出  ：无	
 */
DHT11_Data_TypeDef DHT11_Data;
void DHT11_get(void)
{

	//OSTimeDlyHMSM(0, 0,10,0);
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
		//printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		//printf("\r\n 湿度:%d,温度:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
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
 * 函数名：UltrasonicWave_CalculateTime
 * 描述  ：计算距离
 * 输入  ：超声波测出的时间time，超声波的代号num
 * 输出  ：无	
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
 * 函数名：sensor_Config(void)
 * 描述  ：传感器总配置函数
 * 输入  ：无
 * 输出  ：无	
 */
void sensor_Config(void)
{
	INFRARED_Config();
	//DHT11_GPIO_Config();

}

