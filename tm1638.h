#ifndef __TM1638_H
#define __TM1638_H

#define STB GPIO_Pin_1
#define CLK GPIO_Pin_0
#define DIO GPIO_Pin_2

void TM1638_Init(void);
void TM1638_Write(uint8_t num);	
void TM1638_LED(uint8_t i,uint8_t data);
void TM1638_LEDdata(uint8_t i,uint8_t data);
void TM1638_SLED(uint8_t i,uint8_t st);
void TM1638_AllSLED(uint8_t i);
uint16_t TM1638_Read(void);
void TM1638_AllLED(uint8_t i);
void TM1638_WriteCOM(uint8_t i);
#endif
