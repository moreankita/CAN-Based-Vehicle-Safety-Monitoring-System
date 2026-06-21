#include <lpc21xx.h>
#include "lcd.h"
#include "can.h" 
#include "delay.h"
#include "lcd_defines.h"
#include "DS18B20_temp.h"
#include "types.h"
#include "interrupt.h"
#include "mode_switch.h"
#include"can_defines.h"
#include"defines.h"

u8 cgram[] = {0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02,0x00,0x10,0x18,0x1C,0x1E,0x1C,0x18,0x10,0x00};

int l_flag=0,r_flag=0, mode=0;

int main()
{ 
	int temp;
	u8 tp,tpd;
	CANF txFrame, rxFrame;
 
	InitLCD();//LCD initialization
	enable_interrupts();
	Init_CAN1();
       
	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);//selecting starting line and staring pos
		strLCD("-Vehicle Monitoring-");
		//delay_ms(100);
		BuildCGRAM(cgram,16);
		//CmdLCD(GOTO_LINE2_POS0);
		if(ResetDS18b20()==0)
		{
			temp=ReadTemp();           //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL
			tp  = temp>>4;	         //GETTING INTEGER PART
			tpd=temp&0x08?0x35:0x30;   //GETTING FRACTIONAL PART

			CmdLCD(GOTO_LINE2_POS0);
 			strLCD("Engine Temp:");
			u32LCD(tp);
			charLCD('.');
			charLCD(tpd);
			charLCD(223);
			strLCD("C ");
		}
		else
		{
			CmdLCD(GOTO_LINE2_POS0);
			strLCD("Error: sensor prbm");	
		}
		
		CmdLCD(GOTO_LINE3_POS0);
		strLCD("Indicator:");
		CmdLCD(GOTO_LINE3_POS0+10);
		charLCD(0);	   
		CmdLCD(GOTO_LINE3_POS0+13);
		charLCD(1);

		//CmdLCD(GOTO_LINE4_POS0);
		//strLCD("Mode: Forward");
		  
		if((l_flag==1)&&(r_flag==0))
		{
			txFrame.ID=1;
			txFrame.BFV.RTR=0; //data frame  
			txFrame.BFV.DLC=1; 

			txFrame.Data1='L';
			blink_left_cgram();
		}
		else if(l_flag==2)
		{
			l_flag=0;
			txFrame.ID=1;
			txFrame.BFV.RTR=0; //data frame  
			txFrame.BFV.DLC=1; 

			txFrame.Data1=0;
			
		}
		if((r_flag==1) && (l_flag==0))
		{
		    txFrame.ID=1;
			txFrame.BFV.RTR=0; //data frame
			txFrame.BFV.DLC=1;   

			txFrame.Data1='R';
			blink_right_cgram();
		
		}	
		else if(r_flag==2)
		{
			r_flag=0;
			txFrame.ID=1;
			txFrame.BFV.RTR=0; //data frame  
			txFrame.BFV.DLC=1; 

			txFrame.Data1=0;
			
		}
		if(mode==1)
		{
			//CmdLCD(CLEAR_LCD);
			if(RBIT(C1GSR, RBS_BIT))
			{
			CAN1_Rx(&rxFrame);
			}
			CmdLCD(GOTO_LINE4_POS0+6);
			strLCD("Reverse");
			CmdLCD(GOTO_LINE4_POS0+14);
			strLCD("dis:  ");
			CmdLCD(GOTO_LINE4_POS0+18);
			u32LCD(rxFrame.Data2);

			if(rxFrame.Data1==1)
			{
				alert();
			}
			else if(rxFrame.Data1==0)
			{
				alert_off();
			}
			
		} 
		else if(mode==0)
		{
			alert_off();
			CmdLCD(GOTO_LINE4_POS0);
			strLCD("Mode: Forward       ");	
		}
	    CAN1_Tx(txFrame);
    }
}
