#ifndef _OLED_H
#define _OLED_H

#include <stm32f10x.h>

#define byte unsigned char  
#define word unsigned int   

 void LCD_Init(void);
 void LCD_CLS(void);
 void LCD_CLS_LINE(byte y);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);  
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);     // y 6~0     
 void LCD_PutPixel(byte x,byte y);//»­µã
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
 
 void LED_P6x8Char(int8_t x,int8_t y,int8_t ch);                         
 void LED_PrintValueC(uint8_t x, uint8_t y, int8_t data);
 void LED_PrintValueI(uint8_t x, uint8_t y, int16_t data);
 void LED_PrintValueFP(uint8_t x, uint8_t y, uint16_t data, uint8_t num);
 void LED_PrintValueFP_my(uint8_t x, uint8_t y, uint16_t data, uint8_t num);
 void LED_PrintValueF(uint8_t x, uint8_t y, float data, uint8_t num);
 void LCD_show_Data(u8 x,u8 line,u16 var);
 void LCD_signal_num(uint8_t x,uint8_t line,uint8_t var);
 
 
 void OLED_Config(void);
 
#endif

