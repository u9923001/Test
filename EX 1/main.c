#include "stm32f10x.h"
#include <stdbool.h>

// B0 Green 
// B1 Blue
// B5 Red

void LedInit(void){
	GPIO_InitTypeDef tmp;
	
	// Remember RCC Enable
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

__STATIC_INLINE uint32_t SysTick_Config2(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

void SysTickInit(void){
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	if (SysTick_Config2(SystemCoreClock / 1000000))
	{ 
		/* Capture error */ 
		while (1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

}

static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void SysTick_Handler(void)
{
    if (usTicks != 0)
    {
        usTicks--;
    }
}

void DelayUs(uint32_t us)
{
    // Reload us value
    usTicks = us;
	
	  SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	
    // Wait until usTick reach zero
    while (usTicks != 0);
}

void DelayMs(uint32_t ms)
{
    // Wait until ms reach zero
    while (ms--)
    {
        // Delay 1ms
        DelayUs(1000);
    }
}

int main(void){
	LedInit();
	SysTickInit();
	
	LedGreen(true);
	
	while(1){
		LedGreen(true);
		DelayMs(1000);
		LedGreen(false);
		DelayMs(1000);
	}
	
	return 0;
}
