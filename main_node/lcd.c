#include<lpc21xx.h>
#include"LCD_defines.h"
#include"types.h"
#include"defines.h"
#include"delay.h"
void WriteLCD(u8 data)
{
	//SCLRBIT(IOCLR0,RW); 
	WBYTE(IOPIN1,LCD_DATA,data);
	SSETBIT(IOSET0,EN);
	delay_us(1);
	SCLRBIT(IOCLR0,EN);
	delay_ms(2); //internal process
}
void CmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,RS);
	WriteLCD(cmd);
}
void charLCD(u8 ascii)
{
	SSETBIT(IOSET0,RS);
	WriteLCD(ascii);
}
void InitLCD(void)
{
	WBYTE(IODIR1,LCD_DATA,255); //P0.8-P0.15
	SETBIT(IODIR0,RS);
	SETBIT(IODIR0,RW);
	SETBIT(IODIR0,EN);
	delay_ms(15);
	CmdLCD(MODE_8BIT_1LINE);
	delay_ms(5);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(0x02);
	//CmdLCD(DISP_ON);
	CmdLCD(0x0c);
	//CmdLCD(SHIFT_DISP_LEFT);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
	//CmdLCD(DISP_ON);
}
void strLCD(s8 *p)
{
	while(*p)
		 charLCD(*p++);
}
void u32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		  charLCD('0');
    }
	else
	{
		while(n)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
	}
	for(--i;i>=0;i--)
	{
		 charLCD(a[i]);
	}
}
void s32LCD(s32 n)
{
	if(n<0)
	{
		charLCD('-');
		n=-n;
		u32LCD(n);
	}
}
void f32LCD(f32 fnum, u8 nDP)
{
	u32 n;
	s32 i;
	if(fnum<0)
	{
		charLCD('-');
	}
	else
	{
		n=fnum;
		u32LCD(n);
		charLCD('.');
		for(i=0; i<nDP; i++)
		{
			fnum=(fnum-n)*10;
			n=fnum;
			charLCD(n+48);
		}
	}
}
void HexLCD(u32 n)
{
	u8 a[8], rem;
	s32 i=0;
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n)
		{
			rem=n%16;
			(rem<10)?(rem+=48):(rem+=55);
			a[i++]=rem;
			n/=16;
		}
		for(--i; i>=0; i--)
			charLCD(a[i]);
	}
}

void OctLCD(u32 n)
{
	u8 a[8], rem=0;
	s32 i=0;
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n)
		{
			rem=n%8;
			rem+=48;
			a[i++]=rem;
			n/=8;
		}
		for(--i; i>=0; i--)
			charLCD(a[i]);
	}
}
void BinLCD(u32 n, u8 nbd)
{
	s32 i;
	for(i=(nbd-1); i>=0; i--)
	{
		charLCD(((n>>i)&1)+48);
	}
}
void BuildCGRAM(u8 *p, u8 nb)
{
	s32 i;
	CmdLCD(GOTO_CGRAM);
	for(i=0; i<nb; i++)
	{
		charLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0);
}

