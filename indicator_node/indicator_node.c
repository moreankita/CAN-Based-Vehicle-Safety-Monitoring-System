#include<lpc21xx.h>
#include "delay.h" 
#include "types.h"
#include "indicator_node.h" 

#define LED_PINS 0   //p0.0-p0.7

void Init_LED(void)
{
	IODIR0|=0xFF<<LED_PINS;
	IOPIN0|=0xFF<<LED_PINS; 
}
void indicator_off(void)
{
	IOSET0=0xFF<<LED_PINS;
}
void left_indicator_on(void)
{
	s32 i;
	indicator_off();
	delay_ms(100);

	for(i=7;i>=0;i--)
	{
		IOCLR0=1<<(LED_PINS+i);
		delay_ms(100);
	}
}

void right_indicator_on(void)
{
	s32 i;
	indicator_off();
	delay_ms(100);
	for(i=0;i<=7;i++)
	{
		IOCLR0=1<<(LED_PINS+i);
		delay_ms(100);
	}
}

