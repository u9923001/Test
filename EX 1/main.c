#include "stm32f10x.h"
#include <stdbool.h>

// B0 Green 
// B1 Blue
// B5 Red

void LedInit(void){
	GPIO_InitTypeDef tmp;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// Green LED 
	tmp.GPIO_Pin   = GPIO_Pin_0;
	tmp.GPIO_Speed = GPIO_Speed_50MHz;
	tmp.GPIO_Mode  = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &tmp);
	
	// Blue LED 
	tmp.GPIO_Pin   = GPIO_Pin_1;
	GPIO_Init(GPIOB, &tmp);
	
	// Red LED 
	tmp.GPIO_Pin   = GPIO_Pin_5;
	GPIO_Init(GPIOB, &tmp);
	
	GPIO_Write(GPIOB, 0xFF);
}

void LedGreen(bool enable){
	if(enable){
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	}else{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	}
}

void LedBlue(bool enable){
	if(enable){
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	}else{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}
}
void LedRed(bool enable){
	if(enable){
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	}else{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
	}
}

int main(void){
	LedInit();
	
	LedGreen(true);
	
	while(1){
	}
	
	return 0;
}
