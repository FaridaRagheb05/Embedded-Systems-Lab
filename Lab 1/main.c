/* This program blinks the red LED on the
* TI Tiva LaunchPad. The connections are:
* PF1 - red LED
* PF2 - blue LED
* PF3 - green LED
* They are high active (a '1' turns on the LED).
*/
#include "TM4C123GH6PM.h"
void delayMs(int n);
int main(void)
{
	// enable clock to GPIOF at clock gating control register
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF-> LOCK  =  0x4C4F434B;
	GPIOF->CR |= 0x1;
	//GPIOF -> AFSEL |= 0x0;
	GPIOF -> DEN |= 0x11;
	GPIOF -> DIR &= 0xee; // 11101110
	GPIOF -> PUR |= 0x11; //active low
	
	// enable the GPIO pins for the LED (PF3, 2 1) as output
	GPIOF->DIR |= 0x0e;
	// enable the GPIO pins for digital function
	GPIOF->DEN |= 0x0e;

	
	while(1)
	{
		if(GPIOF->DATA == 0x01)
		{
			 if(GPIOF->DATA == 0x04)
			 {
				 	GPIOF->DATA = 0x08;
			 }
			 else if(GPIOF->DATA == 0x08)
			 {
				 GPIOF->DATA = 0x02;
			 }
			 else
			 {
				 GPIOF->DATA = 0x04;
			 }
}

void delayMs(int n)
{
	int ticks = n * 16000;
	if (n > 1000)
	{
		n = 1000;
	}
	
	SysTick->LOAD = ticks - 1;
	SysTick->CTRL = 0x5; /*Enable the timer and choose sysclk */
	while((SysTick->CTRL & 0x10000) == 0) /*wait until the Count flag is set */
	{ }
	SysTick->CTRL = 0; /*Stop the timer (Enable = 0) */
}
