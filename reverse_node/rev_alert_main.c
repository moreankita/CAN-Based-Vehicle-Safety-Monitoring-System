#include<lpc21xx.h>
#include "lcd.h"
#include "can.h"
#include "ultrasonic.h"
#include "delay.h"
#include "types.h"
#include"can_defines.h"
#include"defines.h"


u32 limit=10;

int main()
{
	u32 dist;
	CANF txFrame;
	Init_CAN1();
	INIT_Ultrasonic();

	T0PR=12000000/1000000-1;
	InitLCD();

	while(1)
	{
		
		dist=dist_cal();
		if(dist<=9)
		{	
			dist=dist-2;
		}
		else if(dist>9 && dist<=11)
		{
			dist=dist-3;
		}
		else if(dist>11 && dist<=18)
		{
			dist=dist-4;
		}
		else if(dist>18 && dist<=30)
		{
			dist=dist-5;
		}
		
		if(dist<limit)
		{
			txFrame.ID=2;
			txFrame.BFV.RTR=0; //data frame  
			txFrame.BFV.DLC=5; 

			txFrame.Data1=1;
			txFrame.Data2=dist;
			CAN1_Tx(txFrame);
		}
		else
		{
			txFrame.ID=2;
			txFrame.BFV.RTR=0; //data frame  
			txFrame.BFV.DLC=5; 

			txFrame.Data1=0;
			txFrame.Data2=dist;
			CAN1_Tx(txFrame);
		}
			
 	}
}
