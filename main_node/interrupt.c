#include<lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "interrupt.h"

#define EINT0_SWITCH1  0x0000000C
#define EINT0_VIC_CHNO  14


#define EINT1_SWITCH2  0x000000C0
#define EINT1_VIC_CHNO  15

#define EINT2_SWITCH3  0x0000C000
#define EINT2_VIC_CHNO  16

extern int l_flag, r_flag, mode;

void enable_interrupts(void)
{
        //cfg P0.1, P0.3, P0.7 pin as EINT0, EINT1, EINT2 input pins
        //clear  bit 2&3, 6&7, 14&15 without affecting other bits
        PINSEL0&=((u32)~3<<2) | ((u32)~3<<6) | ((u32)~3<<14);
        //update bit 2&3, bit 6&7, 14&15 for EINT0, EINT1, EINT2 pin function
        PINSEL0|= EINT0_SWITCH1 | EINT1_SWITCH2 | EINT2_SWITCH3;

        //cfg VIC peripheral block 
        //allow EINT0, EINT1, EINT2 as irq type
        //VICIntSelect=0;    //default
        //enable EINT0, EINT1, EINT2 through channel
        VICIntEnable=1<<EINT0_VIC_CHNO | 1<<EINT1_VIC_CHNO | 1<<EINT2_VIC_CHNO;

        //cfg EINT0 as v.irq with highest priority(0)
        VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;

        //load eint0_isr address into LUT sfr
        VICVectAddr0=(u32)eint0_isr;

        //cfg EINT1 as v.irq with next highest priority(0)
        VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;

        //load eint1_isr address into LUT sfr
        VICVectAddr1=(u32)eint1_isr;

		 //cfg EINT2 as v.irq with next highest priority(0)
        VICVectCntl2=(1<<5)|EINT2_VIC_CHNO;

        //load eint1_isr address into LUT sfr
        VICVectAddr2=(u32)eint2_isr;

        //cfg EINT0, EINT1 via external interrupt peripheral
        //enable EINT0, EINT1, EINT2 
        //EXTINT=0;   //default

        //cfg EINT0, EINT1, EINT2 as edge triggered interrupt
        EXTMODE=((1<<2) | (1<<1) | (1<<0));

        //cfg EINT0, EINT1, EINT2 as falling edge triggered
        //EXTPOLAR=0;   //default

}

void eint0_isr(void) __irq
{
        l_flag++;
		r_flag=0;
        //clear EINT0 status in EXT INT peripheral
        EXTINT=1<<0;

        //clear EINT0 status in VIC peripheral
        VICVectAddr=0;
}

void eint1_isr(void) __irq
{ 
        r_flag++;
		l_flag=0;
        //clear EINT0 status in EXT INT peripheral
        EXTINT=1<<1;

        //clear EINT0 status in VIC peripheral
        VICVectAddr=0;
}

void eint2_isr(void) __irq
{
        if(mode==1)
			mode=0;
		else
			mode=1;
        //clear EINT0 status in EXT INT peripheral
        EXTINT=1<<2;

        //clear EINT0 status in VIC peripheral
        VICVectAddr=0;
}

