#include <LPC21xx.h>   
#include "can.h" 
#include "delay.h" 
#include "indicator_node.h" 
#include"can_defines.h"
#include"defines.h"

int main()  
{
	CANF rxFrame;   
	Init_CAN1(); 
	Init_LED(); 

	while(1)   
	{
		if(RBIT(C1GSR, RBS_BIT))
		{
		CAN1_Rx(&rxFrame);
		}
	  	if(rxFrame.Data1=='L') 
	  	{ 
			
			left_indicator_on();
				
	  	}  
		else if(rxFrame.Data1=='R') 
	  	{
	  		right_indicator_on();
		}
		else if(rxFrame.Data1==0) 
		{
			indicator_off();
	  	}
			
	}    				
}

