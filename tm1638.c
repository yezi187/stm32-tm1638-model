#include "stm32f10x.h"                  

#define STB GPIO_Pin_1				//请替换为实际引脚
#define CLK GPIO_Pin_0				//Please replace this with the actual pin
#define DIO GPIO_Pin_2

/**

制作者:yezi187
制作时间: 20250607

author:yezi187
making time:20250607

*/
void TM1638_Write(uint8_t num);
uint8_t GetNum(uint8_t i);
/**
init function
初始化函数
*/
void TM1638_Init(void){					
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef G;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_Out_PP;
	G.GPIO_Pin=STB|CLK|DIO;
	GPIO_Init(GPIOA,&G);

	GPIO_ResetBits(GPIOA,STB);
	TM1638_Write(0x8b);   
	GPIO_SetBits(GPIOA,STB);
	GPIO_ResetBits(GPIOA,STB);
	TM1638_Write(0x40); 
	GPIO_SetBits(GPIOA,STB);
	
	GPIO_ResetBits(GPIOA,STB);		          
	TM1638_Write(0xc0);    
	unsigned char i;
	for(i=0;i<16;i++)	   
		TM1638_Write(0x00);
	GPIO_SetBits(GPIOA,STB);

	GPIO_ResetBits(GPIOA,STB);
	TM1638_Write(0x44); 
	GPIO_SetBits(GPIOA,STB);	
	return;
}

/*
data 0000 0000
id   1234 5678

 ****        8888
*	 *  	3	 7
*	 *  	3	 7
 ****		 2222
*	 *  	4	 6
*	 *  	4	 6
 **** *      5555 1

0: 0x3f
1: 0x06
2: 0x5b
3: 0x4f
4: 0x66
5: 0x6d
6: 0x7d
7: 0x07
8: 0x7f
9: 0x67

*/


/**
写数据函数
writing data function
*/
void TM1638_Write(uint8_t num){			
	unsigned char i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA,CLK);
		if(num&0X01)
			GPIO_SetBits(GPIOA,DIO);
		else
			GPIO_ResetBits(GPIOA,DIO);
		num>>=1;
		GPIO_SetBits(GPIOA,CLK);
	}
}

void TM1638_LEDdata(uint8_t i,uint8_t data){
	GPIO_ResetBits(GPIOA,STB);
	TM1638_Write(0xc0|(2*i));
	TM1638_Write(data);
	GPIO_SetBits(GPIOA,STB);
}

/**
点亮led数码管函数
*/
void TM1638_LED(uint8_t i,uint8_t data){TM1638_LEDdata(i,GetNum(data));}

uint8_t GetNum(uint8_t i){
	switch (i){
		case 0:
			return 0x3f;
		case 1:
			return 0x06;
		case 2:
			return 0x5b;
		case 3:
			return 0x4f;
		case 4:
			return 0x66;
		case 5:
			return 0x6d;
		case 6:
			return 0x7d;
		case 7:
			return 0x07;
		case 8:
			return 0x7f;
		case 9:
			return 0x67;
		case 10:
			return 0x00;
		
	}
	return 0;
}
/**
点亮单个led函数
*/
void TM1638_SLED(uint8_t i,uint8_t st){
	GPIO_ResetBits(GPIOA,STB);
	TM1638_Write(0xc0|(2*i+1));
	if (st==1){TM1638_Write(0x01);}
	if (st==0){TM1638_Write(0x00);}
	GPIO_SetBits(GPIOA,STB);
}
