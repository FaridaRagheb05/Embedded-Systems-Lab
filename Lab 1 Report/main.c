/* This program blinks the red LED on the
* TI Tiva LaunchPad. The connections are:
* PF1 - red LED
* PF2 - blue LED
* PF3 - green LED
* They are high active (a '1' turns on the LED).
*/
#include "TM4C123GH6PM.h"
void delayMs(int n);


void speedController(void)
{
    int flag2 = 0;
    int speed = 1;   // 0 = 1000ms, 1 = 500ms, 2 = 250ms  (initialized to medium)
    int delays[3] = {1000, 500, 250};

    while (1)
    {
        int d = delays[speed];
        switch (flag2)
        {
            case 0:
                GPIOF->DATA = 0x02; // turn on blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn off blue LED
                delayMs(d);
                break;

            case 1:
                GPIOF->DATA = 0x08; // turn on blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn off blue LED
                delayMs(d);
                break;

            case 2:
                GPIOF->DATA = 0x04; // turn on blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn off blue LED
                delayMs(d);
                break;

            case 3:
                GPIOF->DATA = 0x02; // turn on blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn off blue LED
                delayMs(d);
                GPIOF->DATA = 0x08; // turn on blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn off blue LED
								delayMs(d);
                GPIOF->DATA = 0x04; // turn off blue LED
                delayMs(d);
                GPIOF->DATA = 0x00; // turn on blue LED
                delayMs(d);
                break;
        }

        
        if ((!(GPIOF->DATA & 0x10)))
        {
            while (!(GPIOF->DATA & 0x10))
						{}
						delayMs(20);
            flag2 = (flag2 + 1) % 4;
        }

        if ((!(GPIOF->DATA & 0x01)))
        {
            while (!(GPIOF->DATA & 0x01))
						{}
						delayMs(20);
            speed = (speed + 1) % 3;
        }
    }
}

int main(void)
{
	int count = 0;
	int flag = 1;
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


    speedController();

	while(1)
	{
		GPIOF->DATA = 0x02; // turn on blue LED
		delayMs(250);
		GPIOF->DATA = 0; // turn off blue LED
		delayMs(250);
		
		// data = GPIOF -> DATA;
		if ((GPIOF -> DATA | 0xef) == 0xff)
		{
				while (1)
				{
					while ((GPIOF -> DATA | 0xef) == 0xff)
					{
							if ((GPIOF -> DATA | 0xfe) == 0xfe)
							{
								flag = !flag;
							}
							if (flag)
							{
								GPIOF->DATA = 0x08; // turn on blue LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
							else 
							{
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
					}
					while ((GPIOF -> DATA | 0xef) == 0xff)
					{
							if ((GPIOF -> DATA | 0xfe) == 0xfe)
							{
								flag = !flag;
							}
							if (flag)
							{
								GPIOF->DATA = 0x04; // turn on blue LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
							else 
							{
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
					}
					while ((GPIOF -> DATA | 0xef) == 0xff)
					{
							if ((GPIOF -> DATA | 0xfe) == 0xfe)
							{
								flag = !flag;
							}
							if (flag)
							{
								GPIOF->DATA = 0x02; // turn on blue LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
							else 
							{
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
					}			
						while ((GPIOF -> DATA | 0xef) == 0xff)
					{
							if ((GPIOF -> DATA | 0xfe) == 0xfe)
							{
								flag = !flag;
							}
							if (flag)
							{
								GPIOF->DATA = 0x02; // turn on red LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off red LED
								delayMs(250);
								GPIOF->DATA = 0x08; // turn on green LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off green LED
								delayMs(250);
								GPIOF->DATA = 0x04; // turn on blue LED
								delayMs(250);
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
							else 
							{
								GPIOF->DATA = 0; // turn off blue LED
								delayMs(250);
							}
					}				
			}
		}

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