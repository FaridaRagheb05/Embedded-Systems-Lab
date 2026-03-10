/* Receive characters from phone using UART1 and send it to PC using UART0 */
#include "TM4C123GH6PM.h"
void UART0Tx(char c);
int main(void)
{
	/* provide clock to UART0 */
		SYSCTL->RCGCUART |= 1;
	/* enable clock to PORTA */
	SYSCTL->RCGCGPIO |= 1;
	
	/* provide clock to UART1 */
	SYSCTL->RCGCUART |= 0x02;
	
	/* enable clock to PORTB */
		SYSCTL->RCGCGPIO |= 0x02;

	
	/* enable clock to PORTF */
	SYSCTL->RCGCGPIO |= 0x20;

	/* UART0 initialization */
	UART0->CTL = 0; /* disable UART0 */
	 UART0->IBRD = 104; /* 16MHz/(16*9600 baud rate) = 104.1666666666 */
	 UART0->FBRD = 11; /* fraction part= 0.1666666*64+0.5 = 11.1666666 */
	 UART0->CC = 0; /* use system clock */
	 UART0->LCRH = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
	 UART0->CTL = 0x301; /* enable UART0, TXE, RXE */
	 	  UART0->IM |= 0x0010; /* enable RX interrupt */


	/* UART0 TX0 and RX0 use PA1 and PA0. Set them up. */
	 GPIOA->DEN = 0x03; /* Make PA0 and PA1 as digital */
	 GPIOA->AFSEL = 0x03; /* Use PA0,PA1 alternate function */
	 GPIOA->PCTL = 0x11; /* configure PA0 and PA1 for UART */


	/* UART1 initialization, enabling RX interrupt */
	UART1->CTL = 0; /* disable UART0 */
	 UART1->IBRD = 104; /* 16MHz/(16*9600 baud rate) = 104.1666666666 */
	 UART1->FBRD = 11; /* fraction part= 0.1666666*64+0.5 = 11.1666666 */
	 UART1->CC = 0; /* use system clock */
	 UART1->LCRH = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
	 UART1->CTL = 0x301; /* enable UART0, TXE, RXE */
	 	  UART1->IM |= 0x0010; /* enable RX interrupt */

	 
	/* UART1 TX0 and RX0 use PB1 and PB0. Set them up. */
	GPIOB->DEN = 0x03; /* Make PA0 and PA1 as digital */
	 GPIOB->AFSEL = 0x03; /* Use PA0,PA1 alternate function */
	 GPIOB->PCTL = 0x11; /* configure PA0 and PA1 for UART */
	/* configure Port F pins 3,2,1 to control the LEDs */
	 GPIOF->DIR = 0x0E; /* configure PortF pins 3,2,1 to control LEDs */
	 GPIOF->DEN = 0x0E;
	 GPIOF->DATA = 0; /* turn LEDs off */

	/* enable UART1 interrupt in NVIC and set priority to 3 */
	 NVIC->IP[6] = 3 << 5; 
	 NVIC->ISER[0] |= (1 << 6); /* enable IRQ5 for UART1 */
 __enable_irq(); /* global enable IRQs */
	 while (1) {}
}
void UART1_Handler(void)
{
/* handle a receive interrupt and pass to UART0 and LEDs */
		 volatile int readback;
		 char c;
		 if (UART1->MIS & 0x0010) /* if a receive interrupt has occurred */
		 {
		 c = UART1->DR; /* read the received data */
			 UART0Tx(c);
		if(c == 'r' || c == 'R')
		{
			GPIOF->DATA = 0x02;
		}
		else if(c == 'g' || c == 'G')
		{
			GPIOF->DATA = 0x08;
		}
		else if(c == 'b' || c == 'B')
		{
			GPIOF->DATA = 0x04;
		}
	
		 UART1->ICR = 0x0010; /* clear Rx interrupt flag */
		 readback = UART1->ICR; /* a read to force clearing of interrupt flag */
		 }
		 else
		 {
		 /* should not get here. But if it does, */
		 UART1->ICR = UART1->MIS; /* clear all interrupt flags */
		 readback = UART1->ICR; /* a read to force clearing of interrupt flag */
		 }

}
void UART0Tx(char c)
{
	while((UART0->FR & 0x20)!= 0){} // Wait until Tx buffer is not full
	UART0->DR = c; // Write byte

}