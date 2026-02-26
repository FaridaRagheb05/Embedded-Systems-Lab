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
	int window = 0;
	int offset = 0;
	int count_blink = 0;
	int count_colour = 0;
	// enable clock to GPIOF at clock gating control register
	SYSCTL->RCGCGPIO |= 0x20;
	// enable the GPIO pins for the LED (PF3, 2 1) as output
	GPIOF->DIR |= 0x0e;
	// enable the GPIO pins for digital function
	GPIOF->DEN |= 0x0e;

	while(1)
	{
		count_blink++;
		if (window >= 10) 
		{
			offset = -1;
			count_colour++;
		}
		else if (window <=0)
		{ 
			offset = 1;
			count_colour++;
		}
		
		if ((count_colour % 3) != 0)
		{
			GPIOF->DATA = 0x02; // turn on red LED
			delayMs(10 - window); //on
			GPIOF->DATA = 0; // turn off red LED
			delayMs(window); //off
		}
		
		if ((count_colour % 3) != 1)
		{
			GPIOF->DATA = 0x08; // turn on red LED
			delayMs(window); //on
			GPIOF->DATA = 0; // turn off red LED
			delayMs(10 - window); //off
		}
		
		if ((count_colour % 3) != 2)
		{
			GPIOF->DATA = 0x04; // turn on red LED
			delayMs(10 - window); //on
			GPIOF->DATA = 0; // turn off red LED
			delayMs(window); //off
		}
		
		if (count_blink % 20 ==0)
			window += offset;
	}
}
// delay in milliseconds (16 MHz CPU clock)
void delayMs(int n)
{
	int i, j;
	for(i = 0 ; i < n; i++)
	for(j = 0; j < 1590; j++)
	{} // do nothing for 1 ms
}