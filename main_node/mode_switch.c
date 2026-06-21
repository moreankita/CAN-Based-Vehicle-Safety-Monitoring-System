#include<lpc21xx.h>
#include"lcd.h"
#include"can.h"
#include"delay.h"
#include "lcd_defines.h"

#define BUZZER 17   //p1.17

void alert(void)
{
	IODIR1|=1<<BUZZER;
	IOCLR1=1<<BUZZER;
		
}
void alert_off(void)
{
	IOSET1=1<<BUZZER;	
}

void blink_left_cgram(void)
{
	CmdLCD(GOTO_LINE3_POS0+10);
	charLCD(0);	
	delay_ms(100);
	   
	CmdLCD(GOTO_LINE3_POS0+10);
	charLCD(' ');
	delay_ms(100);
}
void blink_right_cgram(void)
{
	CmdLCD(GOTO_LINE3_POS0+13);
	charLCD(1);	
	delay_ms(100);
	   
	CmdLCD(GOTO_LINE3_POS0+13);
	charLCD(' ');
	delay_ms(100);
}
