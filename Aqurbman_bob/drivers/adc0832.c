#include "adc0832.h" 
#include "time.h"


void ADC0832_Init(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	
  GPIO_InitStructure.GPIO_Pin = ACK  | ACS ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DIN_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = ADO  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void DOUT_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = ADO  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uchar ADC0832_Read(uchar ch)
{
	/*??ADC? CH ?????,ADC??2???????*/
	uchar i;
	uchar ADC_buff=0;
	uchar temp=0;
        DOUT_Configuration();
	GPIO_SetBits(GPIOA , ACS);
	GPIO_SetBits(GPIOC , ADO);   /*???*/
	GPIO_ResetBits(GPIOA , ACK);
	GPIO_ResetBits(GPIOA , ACS);
	Delay_us(1);
	GPIO_SetBits(GPIOA , ACK); 
	Delay_us(1);
	GPIO_ResetBits(GPIOA , ACK);
	GPIO_SetBits(GPIOC , ADO);  /*? SGL/DIF ? */
	Delay_us(1);
	GPIO_SetBits(GPIOA , ACK);
	Delay_us(1);
	GPIO_ResetBits(GPIOA , ACK);
	if(ch==0) 
          GPIO_ResetBits(GPIOC , ADO);  /*??????*/
	else 
          GPIO_SetBits(GPIOC , ADO);
	GPIO_SetBits(GPIOA , ACK);
	Delay_us(1);
	GPIO_ResetBits(GPIOA , ACK);
	Delay_us(1);  
	GPIO_SetBits(GPIOC , ADO); /*??DIO??,??ADC??*/
	Delay_us(1);
	GPIO_SetBits(GPIOA , ACK);
	Delay_us(1);
        DIN_Configuration();
	for(i=0;i<8;i++)
        { /*????8???*/		
		Delay_us(3);
		GPIO_ResetBits(GPIOA , ACK);
		Delay_us(1);
		Delay_us(1);
		ADC_buff=ADC_buff<<1;
		if(GPIO_ReadInputDataBit(GPIOC , ADO)==1) 
                  ADC_buff=ADC_buff+1;  /*????*/
		GPIO_SetBits(GPIOA , ACK);			
	}
	for(i=0;i<8;i++)
  {
		temp = temp>>1;
		if(GPIO_ReadInputDataBit(GPIOC , ADO)==1) 
                  temp = temp | 0x80; /*??????*/
		GPIO_SetBits(GPIOA , ACK);
		Delay_us(1);
		GPIO_ResetBits(GPIOA , ACK);
		Delay_us(1);
	}
	GPIO_SetBits(GPIOA , ACS);
	GPIO_SetBits(GPIOA , ACK);
	if(temp != ADC_buff) ADC_buff=0;
	return ADC_buff;  /*?????*/	
}
